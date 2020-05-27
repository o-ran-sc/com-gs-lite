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


extern "C" {
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
}

time_t st_time;

#define CSVMAXLINE 1000000

#define CHUNK 262144
static gs_uint8_t in[CHUNK + CSVMAXLINE];
static gs_uint8_t out[CHUNK + CSVMAXLINE];

#define FILEWAIT_TIMEOUT 10000		// timeout value for getting next file (in microseconds)

gs_uint32_t max_field_csv = CSVELEMENTS;

z_stream strm;

#ifdef BSA_ENABLED
#include "bsa_stream.hpp"
#include "bsa_util.hpp"
BSA::FileStream::ISubStream* stream;
BSA::FileStream::IFileHandle* ifh;
BSA::FileStream::Reader* reader;
#endif

gs_sp_t dev;

static int listensockfd=-1;
static int fd=-1;
static struct packet cur_packet;
static gs_sp_t name;
static gs_sp_t line;
static ssize_t len;
static size_t line_len;
static gs_uint32_t lineend=0;
static gs_uint8_t csvdel = ',';
static gs_uint32_t verbose=0;
static gs_uint32_t startupdelay=0;
static gs_uint32_t singlefile=0;
static gs_uint32_t use_gzip=0;
static gs_uint32_t use_bsa=0;
static gs_uint32_t gshub=0;
static int socket_desc=0;

#include "lfta/csv_parser.h"

// leftover bytes not consumed at the end of the data chunk
 gs_uint32_t leftover = 0;

 uint64_t get_posix_clock_time ()
{
    struct timespec ts;

    if (clock_gettime (CLOCK_MONOTONIC, &ts) == 0)
        return (uint64_t) (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    else
        return 0;
}


static void init_inflate() {
	gs_int32_t ret;

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, 15 /* window bits */ | 32 /* use gzip */);
    if (ret != Z_OK) {
		print_error((gs_sp_t)"csv::inflateInit2");
		exit(10);
    }
}

static void csv_replay_check_messages() {
  if (fta_start_service(0)<0) {
		print_error((gs_sp_t)"Error:in processing the msg queue for a replay file");
		exit(9);
  }
}

static gs_int32_t read_chunk_socket(gs_sp_t buffer, gs_uint32_t length){
	gs_uint32_t r;
	fd_set socket_rset;
	fd_set socket_eset;
	struct timeval socket_timeout;
	gs_int32_t retval;

	FD_ZERO(&socket_rset);
	FD_SET(socket_desc,&socket_rset);
	FD_ZERO(&socket_eset);
	FD_SET(socket_desc,&socket_eset);
	// timeout in one millisecond
	socket_timeout.tv_sec = 0;
	socket_timeout.tv_usec = 1000;

	if ((retval = select(socket_desc+1,&socket_rset,0,&socket_eset,&socket_timeout))<=0) {
		if (retval==0) {
			// caught a timeout
			return -1;
		}
		return -2;
	}

	if ((r=read(socket_desc, buffer + leftover, length)) <= 0) {
		print_error((gs_sp_t)"ERROR:could not read data from csv stream");
		return -2;
	}

	return r;
}

static void init_socket() {
	endpoint gshub;
	endpoint srcinfo;
 	struct sockaddr_in server;
	gs_int32_t parserversion;
	gs_uint32_t schemalen;
	static gs_sp_t asciischema=0;
	gs_int8_t buf[1024];

	if (get_hub(&gshub)!=0) {
		print_error((gs_sp_t)"ERROR:could not find gshub for data source");
		exit(0);
	}

	if (get_streamsource(gshub,name,&srcinfo,1) !=0) {
		print_error((gs_sp_t)"ERROR:could not find data source for stream\n");
		exit(0);
	}

	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		print_error((gs_sp_t)"ERROR:could not create socket for data stream");
		exit(0);
	}
	server.sin_addr.s_addr = srcinfo.ip;
	server.sin_family = AF_INET;
	server.sin_port = srcinfo.port;

	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)  {
		print_error((gs_sp_t)"ERROR: could not open connection to data source");
		exit(0);
	}
}

static void next_file() {
	struct stat s;
	if (verbose) {
		fprintf(stderr,"Opening %s\n",name);
	}
	if (singlefile == 0) {
		while (lstat(name, &s) != 0) {
			if (errno != ENOENT) {
				print_error((gs_sp_t)"csv::lstat unexpected return value");
				exit(10);
			}
			csv_replay_check_messages();
			usleep(FILEWAIT_TIMEOUT);
		}
		if	(fd > 0) {
			close(fd);
		}
	}
	if ((fd = open(name, O_RDONLY)) < 0) {
		print_error((gs_sp_t)"csv::open failed ");
		exit(10);
	}
	posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
	if (singlefile == 0) {
		unlink(name);
	}
	if (use_gzip) {
		init_inflate();
	}
}

#ifdef BSA_ENABLED

uint64_t bsa_file_start_time = 0;
uint64_t bsa_total_elapsed_time = 0;

static void next_file_bsa() {
    int ret;

	if (bsa_file_start_time) {
		bsa_total_elapsed_time += (get_posix_clock_time()- bsa_file_start_time);
		bsa_file_start_time = 0;
	}

    ifh = stream->getNextFileHandle(FILEWAIT_TIMEOUT / 1000);
    if (!ifh) {
        return;
	}
	if (verbose) {
		fprintf(stderr,"%s: Opening %s %s\n", dev, ifh->getHandle().c_str(), stream->getPositionHandle().c_str());
	}
	bsa_file_start_time = get_posix_clock_time();
    reader = ifh->openFile();

	if (use_gzip) {
		init_inflate();
	}
}

static void close_file_bsa() {

	if (reader) {
		reader->close();
		delete reader;
	}
	reader = NULL;

	if (ifh) {
    	ifh->finished();
		delete ifh;
	}
	ifh = NULL;
}

#endif

static gs_retval_t csv_replay_init(gs_sp_t device)
{
	gs_sp_t	verbosetmp;
	gs_sp_t	delaytmp;
	gs_sp_t	gshubtmp;
	gs_sp_t	tempdel;
	gs_sp_t	singlefiletmp;
	gs_sp_t compressortmp;
	gs_sp_t bsatmp;    

	if ((verbosetmp=get_iface_properties(device,(gs_sp_t)"verbose"))!=0) {
		if (strncmp(verbosetmp,"TRUE",4)==0) {
			verbose=1;
			fprintf(stderr,"VERBOSE ENABLED\n");
		} else {
			fprintf(stderr,"VERBOSE DISABLED\n");
		}
	}

	if ((name=get_iface_properties(device,(gs_sp_t)"filename"))==0) {
		print_error((gs_sp_t)"csv_replay_init::No CSV \"Filename\" defined");
		exit(0);
	}
	tempdel=get_iface_properties(device,(gs_sp_t)"csvseparator");
	if (tempdel != 0 ) {
		csvdel = tempdel[0];
		csv_set_delim(csvdel);
	}

	if ((singlefiletmp=get_iface_properties(device,(gs_sp_t)"singlefile"))!=0) {
		if (strncmp(singlefiletmp,"TRUE",4)==0) {
			singlefile=1;
			if (verbose)
				fprintf(stderr,"SINGLEFILE ENABLED\n");
		} else {
			if (verbose)
				fprintf(stderr,"SINGLEFILE DISABLED\n");
		}
	}

	if ((compressortmp=get_iface_properties(device,(gs_sp_t)"compressor"))!=0) {
		if (strncmp(compressortmp,"GZIP",4)==0) {
			use_gzip=1;
			if (verbose)
				fprintf(stderr,"USING ZLIP COMPRESSOR ENABLED\n");
		} else {
			print_error((gs_sp_t)"csv_replay_init::Unknown value for interface property \"Compressor\"");
			exit(0);
		}
	}

	if ((bsatmp=get_iface_properties(device,(gs_sp_t)"bsa"))!=0) {
		if (strncmp(bsatmp,"TRUE",4)==0) {
			#ifndef BSA_ENABLED
				print_error((gs_sp_t)"csv_replay_init::runtime not built with BSA support to use BSA interfaces");		
				exit(0);						
			#endif

			use_bsa=1;
			if (verbose)
				fprintf(stderr,"USING BSA STREAMS\n");
		} 
	}    

	if ((delaytmp=get_iface_properties(device,(gs_sp_t)"startupdelay"))!=0) {
		if (verbose) {
				fprintf(stderr,"Startup delay of %u seconds\n",atoi(get_iface_properties(device,(gs_sp_t)"startupdelay")));
		}
		startupdelay=atoi(get_iface_properties(device,(gs_sp_t)"startupdelay"));
	}
	if ((gshubtmp=get_iface_properties(device,(gs_sp_t)"gshub"))!=0) {
		if (verbose) {
				fprintf(stderr,"CSV format using gshub\n");
		}
		gshub=1;
	}

	cur_packet.ptype=PTYPE_CSV;
	return 0;
}

static inline int consume_chunk(gs_sp_t chunk, gs_uint32_t chunk_size) {
    int tuple_consumed = 0;	
	gs_sp_t linepos = chunk;
	gs_sp_t new_linepos = (gs_sp_t)memchr(linepos + leftover, '\n', chunk_size);
	gs_sp_t end_pos = chunk + chunk_size + leftover;
	leftover = chunk_size;

	while (new_linepos) {
		// *new_linepos = 0;				// terminate the line
		csv_parse_line(linepos, new_linepos - linepos);
		rts_fta_process_packet(&cur_packet);
        tuple_consumed++;		
		linepos = new_linepos + 1;
		leftover = end_pos - linepos;
		new_linepos = (gs_sp_t)memchr(linepos, '\n', leftover);
	}
	memcpy(chunk, linepos, leftover);

    return tuple_consumed;	
}

static int csv_process_chunk(gs_uint32_t chunk_size)
{
    gs_int32_t ret;
    gs_uint32_t have = chunk_size;
    gs_uint32_t tuple_consumed = 0;

	if (use_gzip) {
		strm.avail_in = have;
		strm.next_in = in;
		/* run inflate() on input until output buffer not full */
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out + leftover;
			ret = inflate(&strm, Z_NO_FLUSH);
			/* assert(ret != Z_STREAM_ERROR);  state not clobbered */
			switch (ret) {
				case Z_NEED_DICT:
					ret = Z_DATA_ERROR;     /* and fall through */
				case Z_DATA_ERROR:
				case Z_MEM_ERROR:
					(void)inflateEnd(&strm);
#ifdef BSA_ENABLED	
					close_file_bsa();
#endif
					fprintf(stderr,"Error inflating data chunk\n");
					return 0;
			}
			have = CHUNK - strm.avail_out;
			tuple_consumed += consume_chunk((gs_sp_t)out, have);
		} while (strm.avail_out == 0);
		/* done when inflate() says it's done */

		if (ret == Z_STREAM_END) {
			inflateEnd(&strm);
#ifdef BSA_ENABLED	
			close_file_bsa();
#endif			       
    	}
	} else {
		tuple_consumed += consume_chunk((gs_sp_t)out, have);
	}
    
    return tuple_consumed;
}

static gs_int32_t csv_read_chunk() {

	gs_int32_t have;

	if (gshub!=0) {
		return read_chunk_socket((gs_sp_t)out, CHUNK);
	} else {
		gs_sp_t read_pos = (gs_sp_t)(use_gzip ? in : (out + leftover));

#ifdef BSA_ENABLED
		if (use_bsa) {
			if (ifh == 0) next_file_bsa();
			if (ifh == 0) 		// if no new files available return
				return -1;		// -1 indicates a timeout

    		while ((have = reader->read(read_pos, CHUNK)) == 0) {
				close_file_bsa();

        		next_file_bsa();
    
        		if (ifh == 0) {	// if no new files available return
            		return -1;	// -1 indicates a timeout
				}
    		}
		} else {
#endif
			if (fd <= 0) next_file();
			while ((have = read(fd, read_pos, CHUNK)) == 0) {
				if (singlefile==1) {
					if(verbose) {
						fprintf(stderr,"SINGLEFILE PROCESSING DONE! RTS SAYS BYE\n");
					}
					return -2;

				} else {
					next_file();
				}
			}
#ifdef BSA_ENABLED		
		}
#endif
	}
	return have;
}

static gs_retval_t csv_process_input()
{
	unsigned cnt = 0;
	static unsigned totalcnt = 0;

	gs_int32_t retval;
	while(cnt < 50000) {			// process up to 50000 tuples at a time
		retval = csv_read_chunk();
		if (retval == -1) return 0; // got a timeout so service message queue
		if (retval == -2) {
			// we signal that everything is done
			if (verbose)
				fprintf(stderr,"Done processing, waiting for things to shut down\n");
			rts_fta_done();
			// now just service message queue until we get killed or loose connectivity
			while (true) {
				fta_start_service(0); // service all waiting messages
				usleep(1000); // sleep a millisecond
			}
		}
		cnt += csv_process_chunk((gs_uint32_t)retval);
	}
	totalcnt = totalcnt + cnt;
	if (verbose) {
#ifdef BSA_ENABLED		
		fprintf(stderr,"%s: Processed %u tuples, rate = %lf tup/sec\n", dev, totalcnt, 1000.0 * (double)totalcnt / (double)bsa_total_elapsed_time);
#else
		fprintf(stderr,"Processed %u tuples, rate = %lf tup/sec\n", totalcnt, (double)totalcnt / (double)(time(NULL) - st_time));
#endif
	}
	return 0;
}

extern "C" gs_retval_t main_csv(gs_int32_t devicenum, gs_sp_t device, gs_int32_t mapcnt, gs_sp_t map[]) {
	gs_uint32_t cont;
	endpoint mygshub;

    dev = device;

	csv_replay_init(device);

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
	csv_set_maxfield(max_field_csv);

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

	// open the connection to the data source
	if (gshub != 0) { init_socket();}

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

#ifdef BSA_ENABLED
    if (use_bsa) {
	    stream = BSA::FileStream::ISubStream::construct(std::string(name));
	    stream->init ();
    }

#endif
	st_time = time(NULL);
	while (true) {
		if (csv_process_input() < 0) {
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
