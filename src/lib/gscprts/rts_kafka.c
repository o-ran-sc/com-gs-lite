/* ------------------------------------------------
 Copyright 2014 AT&T Intellectual Property
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 ------------------------------------------- */

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zlib.h>
#include "errno.h"
#include "stdio.h"
#include "stdlib.h"


#include "gsconfig.h"
#include "gshub.h"
#include "gstypes.h"
#include "lapp.h"
#include "fta.h"
#include "packet.h"
#include "schemaparser.h"
#include "lfta/rts.h"

void fta_init(gs_sp_t device);
void rts_fta_process_packet(struct packet * p);
void rts_fta_done();


#ifdef KAFKA_ENABLED

#include <librdkafka/rdkafka.h>

time_t st_time;

gs_uint32_t max_field_kafka = CSVELEMENTS;

#define KAFKA_TIMEOUT 1000		// timeout value for getting next batach of records (in ms)

gs_sp_t dev;

static int fd=-1;
static struct packet cur_packet;
static gs_sp_t config_fname;
static gs_sp_t topics_fname;
static gs_sp_t line;
static ssize_t len;
static size_t line_len;
static gs_uint32_t lineend=0;
static gs_uint8_t csvdel = ',';
static gs_uint32_t verbose=0;
static gs_uint32_t startupdelay=0;

#define MAX_KAFKA_TOPICS 256

static rd_kafka_t *rk;
static rd_kafka_conf_t *conf;
static rd_kafka_queue_t *rkqu = NULL;
static rd_kafka_topic_t *topic_list[MAX_KAFKA_TOPICS];
gs_uint32_t num_topics;

#include "lfta/csv_parser.h"

static int read_topic_list (rd_kafka_t * rk, rd_kafka_queue_t *kqueue, rd_kafka_topic_t **topic_list, int max_topics, const char *fname) {
	FILE *fp;
	int line = 0;	
	char buf[512];

	if (!(fp = fopen(fname, "r"))) {
		fprintf(stderr, "Unable to open kafka topic list file %s\n", fname);
		return -1;
	}

	while (line < max_topics && fgets(buf, sizeof(buf), fp)) {
		strtok(buf, " \t\r\n");		// truncate the whitespace and end of line
		topic_list[line] = rd_kafka_topic_new(rk, buf, NULL);
		int r = rd_kafka_consume_start_queue(topic_list[line], 0, RD_KAFKA_OFFSET_END, kqueue);
		if (r == -1) {
			fprintf(stderr, "Unable to add topic %s to queue: %s\n", buf, rd_kafka_err2str(rd_kafka_last_error()));
			exit(1);
		}
		line++;
	}
	fclose(fp);

	return line;
}


static int read_conf_file (rd_kafka_conf_t *conf, const char *fname) {
	FILE *fp;
	int line = 0;	
	char buf[10240];
	char errstr[512];

	if (!(fp = fopen(fname, "r"))) {
		fprintf(stderr, "Unable to open kafka configuration file %s\n", fname);
		return -1;
	}

	while (fgets(buf, sizeof(buf), fp)) {
		char *s = buf;
		char *t;
		rd_kafka_conf_res_t r = RD_KAFKA_CONF_UNKNOWN;
		line++;

		while (isspace((int)*s))
			s++;
			if (!*s || *s == '#')
				continue;

			if ((t = strchr(buf, '\n')))
				*t = '\0';
			t = strchr(buf, '=');
			if (!t || t == s || !*(t+1)) {
				fprintf(stderr, "Error reading kafka config file %s:%d: expected key=value\n", fname, line);
				fclose(fp);
				return -1;
			}
			*(t++) = '\0';

			// set config property
			r = rd_kafka_conf_set(conf, s, t, errstr, sizeof(errstr));
			if (r == RD_KAFKA_CONF_OK)
					continue;

			fprintf(stderr, "Unable set to set kafka configuration property %s:%d: %s=%s: %s\n", fname, line, s, t, errstr);
			fclose(fp);
			return -1;
	}
	fclose(fp);

	return 0;
}

static void msg_consume (rd_kafka_message_t *rkmessage, void *opaque) {

	if (rkmessage->err) {
		if (rkmessage->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) {
			// caught up with the data
			return;
		}
		return;
	}
	csv_parse_line(rkmessage->payload, rkmessage->len);
	rts_fta_process_packet(&cur_packet);
}

static gs_retval_t kafka_replay_init(gs_sp_t device)
{
	gs_sp_t	verbosetmp;
	gs_sp_t	delaytmp;
	gs_sp_t	tempdel;

	if ((verbosetmp=get_iface_properties(device,(gs_sp_t)"verbose"))!=0) {
		if (strncmp(verbosetmp,"TRUE",4)==0) {
			verbose=1;
			fprintf(stderr,"VERBOSE ENABLED\n");
		} else {
			fprintf(stderr,"VERBOSE DISABLED\n");
		}
	}

	if ((config_fname=get_iface_properties(device,(gs_sp_t)"kafkaconfig"))==0) {
		print_error((gs_sp_t)"kafka_replay_init::No \"kafkaconfig\" defined");
		exit(0);
	}

	if ((topics_fname=get_iface_properties(device,(gs_sp_t)"kafkatopics"))==0) {
		print_error((gs_sp_t)"kafka_replay_init::No \"kafkatopics\" defined");
		exit(0);
	}	

	tempdel=get_iface_properties(device,(gs_sp_t)"csvseparator");
	if (tempdel != 0 ) {
		csvdel = tempdel[0];
		csv_set_delim(csvdel);
	}

	if ((delaytmp=get_iface_properties(device,(gs_sp_t)"startupdelay"))!=0) {
		if (verbose) {
				fprintf(stderr,"Startup delay of %u seconds\n",atoi(get_iface_properties(device,(gs_sp_t)"startupdelay")));
		}
		startupdelay=atoi(get_iface_properties(device,(gs_sp_t)"startupdelay"));
	}

	// set maximum field nubmer to be extracted by csv parser
	csv_set_maxfield(max_field_kafka);

	cur_packet.ptype=PTYPE_CSV;

	char errstr[512];

	// load Kafka configuration from config file
	conf = rd_kafka_conf_new();
	read_conf_file(conf, config_fname);

	// create new Kafka handle using configuration settings
	if (!(rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr)))) {
		fprintf(stderr, "Unable to create new Kafka consumer: %s\n", errstr);
		exit(1);
	}	

	// load topic list fromt he file and setup a kafka queue to consume them
	rkqu = rd_kafka_queue_new(rk);
	num_topics = read_topic_list(rk, rkqu, topic_list, MAX_KAFKA_TOPICS, topics_fname);
	if (!num_topics) {
		fprintf(stderr, "Empty list of Kafka topics\n");		
	}

	return 0;
}


static gs_retval_t kafka_process_input()
{
	unsigned cnt = 0;
	static unsigned totalcnt = 0;

	gs_int32_t retval;
	while(cnt < 50000) {			// process up to 50000 tuples at a time
		retval = rd_kafka_consume_callback_queue(rkqu, KAFKA_TIMEOUT, msg_consume, NULL);
		if (retval == 0) return 0; // got a timeout so service message queue
		if (retval < 0) {
			// tear down kafka
			size_t i = 0;
			// stop consuming from topics
			for (i=0 ; i<num_topics ; ++i) {
				int r = rd_kafka_consume_stop(topic_list[i], 0);
				if (r == -1) {
					fprintf(stderr, "Enable to stop consuming from topic %s\n", rd_kafka_err2str(rd_kafka_last_error()));
				}
			}

			// destoy queue
			rd_kafka_queue_destroy(rkqu);

			// Destroy topics
			for (i=0 ; i<num_topics ; ++i) {
				rd_kafka_topic_destroy(topic_list[i]);
			}

			// destroy Kafka handle
			rd_kafka_destroy(rk);

			// we signal that everything is done
			if (verbose)
				fprintf(stderr,"Done processing, waiting for things to shut down\n");
			rts_fta_done();
			// now just service message queue until we get killed or loose connectivity
			while (1) {
				fta_start_service(0); // service all waiting messages
				usleep(1000); // sleep a millisecond
			}
		}
		cnt += retval;
	}
	totalcnt = totalcnt + cnt;
	if (verbose) {
		fprintf(stderr,"Processed %u tuples, rate = %lf tup/sec\n", totalcnt, (double)totalcnt / (double)(time(NULL) - st_time));
	}
	return 0;
}

gs_retval_t main_kafka(gs_int32_t devicenum, gs_sp_t device, gs_int32_t mapcnt, gs_sp_t map[]) {
	gs_uint32_t cont;
	endpoint mygshub;

    dev = device;

	kafka_replay_init(device);

	/* initalize host_lib */
	if (verbose) {
		fprintf(stderr,"Init LFTAs for %s\n",device);
	}

	if (hostlib_init(LFTA,0,devicenum,mapcnt,map) < 0) {
		fprintf(stderr,"%s::error:could not initiate host lib for clearinghouse\n",
			device);
		exit(7);
	}

	fta_init(device); /*xxx probably should get error code back put Ted doesn't give me one*/

	// set maximum field nubmer to be extracted by csv parser
	csv_set_maxfield(max_field_kafka);

	cont = startupdelay + time(0);

	if (verbose) { fprintf(stderr,"Start startup delay"); }

	while (cont > time(NULL)) {
		if (fta_start_service(0) < 0) {
			fprintf(stderr,"%s::error:in processing the msg queue\n", device);
			exit(9);
		}
		usleep(1000); /* sleep for one millisecond */
	}

	if (verbose) { fprintf(stderr,"... Done\n"); }

	// wait to process till we get the signal from GSHUB
	if (get_hub(&mygshub) != 0) {
		print_error((gs_sp_t)"ERROR:could not find gshub for data source");
		exit(0);
	}
	while(get_startprocessing(mygshub,get_instance_name(),0) != 0) {
		usleep(100);
		if (fta_start_service(0) < 0) {
			fprintf(stderr,"%s::error:in processing the msg queue\n", device);
			exit(9);
		}
	}

	/* now we enter an endless loop to process data */
	if (verbose) {
		fprintf(stderr,"Start processing %s\n",device);
	}

	st_time = time(NULL);
	while (1) {
		if (kafka_process_input() < 0) {
			fprintf(stderr,"%s::error:in processing records\n", device);
			exit(8);
		}
		/* process all messages on the message queue*/
		if (fta_start_service(0) < 0) {
			fprintf(stderr,"%s::error:in processing the msg queue\n", device);
			exit(9);
		}
	}

	return 0;
}

#else			
//		This is a stub entry point to ensure proper linking when Kafka support is not enabled
gs_retval_t main_kafka(gs_int32_t devicenum, gs_sp_t device, gs_int32_t mapcnt, gs_sp_t map[]) {
	fprintf(stderr,"ERROR: runtime built without Kafka support.\n");
	exit(1);

	return 0;
}

#endif 			// KAFKA_ENABLED

