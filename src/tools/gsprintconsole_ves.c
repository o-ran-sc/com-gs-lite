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


/*
 * Print ves formatted records to the console.
 * Each line is a json record.
 * Based on gsprintconsole.c, just differences in formatting.
*/


#include <app.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "gsconfig.h"
#include "gstypes.h"
#include "gshub.h"
#include "simple_http.h"

#include <schemaparser.h>

#define MAXLINE 100000
static unsigned tcpport=0;
static char linebuf[MAXLINE];
int listensockfd=0;
int fd=0;


// Not all systems have timersub defined so make sure its ther
#ifndef timersub

#define timersub(tvp, uvp, vvp)                                         \
do {                                                            \
(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;          \
(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;       \
if ((vvp)->tv_usec < 0) {                               \
(vvp)->tv_sec--;                                \
(vvp)->tv_usec += 1000000;                      \
}                                                       \
} while (0)

#endif

void hand(int iv) {
    ftaapp_exit();
    fprintf(stderr, "exiting via signal handler %d...\n", iv);
    exit(1);
}

static void wait_for_client() {
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t clilen;
    if (listensockfd==0) {
		gs_int32_t on = 1;
		listensockfd=socket(AF_INET, SOCK_STREAM, 0);
        if (listensockfd < 0) {
			gslog(LOG_EMERG,"Error:Could not create socket for tcp data stream");
			exit(1);
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(tcpport);
#ifndef __linux__
        /* make sure we can reuse the common port rapidly */
        if (setsockopt(listensockfd, SOL_SOCKET, SO_REUSEPORT,
                       (gs_sp_t )&on, sizeof(on)) != 0) {
            gslog(LOG_EMERG,"Error::could not set socket option\n");
            exit(1);
        }
#endif
        if (setsockopt(listensockfd, SOL_SOCKET, SO_REUSEADDR,
                       (gs_sp_t )&on, sizeof(on)) != 0) {
            gslog(LOG_EMERG,"Error::could not set socket option\n");
            exit(1);
		}
        
		if (bind(listensockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0) {
			gslog(LOG_EMERG,"Error:Could not bind socket for tcp data stream");
            exit(1);
        }
	}
    
	do {
		listen(listensockfd,5);
		clilen = sizeof(cli_addr);
		fd=accept(listensockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (fd<0) {
            gslog(LOG_EMERG,"Error:Could not accept connection on tcp socket");
		}
	} while (fd==0);
}


static void emit_socket() {
	unsigned o,w,l;
	o=0;
	w=0;
	l=strlen(linebuf);
	do {
		if((w=write(fd,&linebuf[o],l))==0) {
			close(fd);
			wait_for_client();
		}
		o=o+w;
	} while (o<l);
}

static void emit_line() {
    
    if (tcpport==0) {
        printf("%s",linebuf);
    } else {
        emit_socket();
    }
    
}

int main(int argc, char* argv[]) {
    gs_sp_t me = argv[0];
    FTAID fta_id;
    gs_int32_t schema, ch;
    
    FTAID rfta_id;
    gs_uint32_t rsize;
    gs_uint32_t bufsz=8*1024*1024;
    gs_int8_t rbuf[2*MAXTUPLESZ];
    
    gs_int32_t numberoffields;
    gs_int32_t verbose=0;
    gs_int32_t y, lcv;
    
    void *pblk;
    gs_int32_t pblklen;
	gs_int32_t n_actual_param;
	gs_int32_t n_expected_param;
    gs_int32_t xit = 0;
    gs_int32_t dump = 0;
    struct timeval tvs, tve, tvd;
    gs_retval_t code;
    endpoint gshub;
    endpoint dummyep;
    gs_uint32_t tip1,tip2,tip3,tip4;
    gs_sp_t instance_name;

	gs_sp_t curl_address = NULL;
	endpoint curl_endpoint;
	gs_sp_t curl_url = NULL;
	gs_sp_t curl_auth = NULL;
	gs_uint32_t http_code;

	gs_uint32_t ves_version=5;


    gs_uint32_t tlimit = 0;     // time limit in seconds
    time_t start_time, curr_time;
    
	gsopenlog(argv[0]);
    
    
    while ((ch = getopt(argc, argv, "l:p:r:vXDC:U:A:V:")) != -1) {
        switch (ch) {
            case 'r':
                bufsz=atoi(optarg);
                break;
            case 'p':
                tcpport=atoi(optarg);
                break;
            case 'v':
                verbose++;
                break;
            case 'X':
                xit++;
                break;
            case 'D':
                dump++;
                break;
            case 'l':
                tlimit = atoi(optarg);
                break;
            case 'V':
                ves_version = atoi(optarg);
                break;
			case 'C':
				curl_address = strdup(optarg);
    			if (sscanf(curl_address,"%u.%u.%u.%u:%hu",&tip1,&tip2,&tip3,&tip4,&(curl_endpoint.port))!= 5 ) {
        			gslog(LOG_EMERG,"Curl IP NOT DEFINED");
        			exit(1);
    			}
    			curl_endpoint.ip=htonl(tip1<<24|tip2<<16|tip3<<8|tip4);
    			curl_endpoint.port=htons(curl_endpoint.port);
				break;
            case 'U':
				curl_url = strdup(optarg);
                break;
            case 'A':
				curl_auth = strdup(optarg);
                break;
            default:
            usage:
                fprintf(stderr, "usage: %s [-r <bufsz>] [-p <port>] [-l <time_limit>] [-v] [-X] [-D] [-C <curl_dest>:<curl_port>] [-U <curl_url>] [-A <authentication_string>] [-V <ves_version>] <gshub-hostname>:<gshub-port> <gsinstance_name>  query param1 param2...\n",
                        *argv);
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;
    if (argc<3) goto usage;
    
    if (sscanf(argv[0],"%u.%u.%u.%u:%hu",&tip1,&tip2,&tip3,&tip4,&(gshub.port))!= 5 ) {
        gslog(LOG_EMERG,"HUB IP NOT DEFINED");
        exit(1);
    }
    gshub.ip=htonl(tip1<<24|tip2<<16|tip3<<8|tip4);
    gshub.port=htons(gshub.port);
    instance_name=strdup(argv[1]);
    if (set_hub(gshub)!=0) {
        gslog(LOG_EMERG,"Could not set hub");
        exit(1);
    }
    if (set_instance_name(instance_name)!=0) {
        gslog(LOG_EMERG,"Could not set instance name");
        exit(1);
    }
    
    if (get_initinstance(gshub,instance_name,&dummyep,1)!=0) {
        gslog(LOG_EMERG,"Did not receive signal that GS is initiated\n");
    }


//	If this uses curl output, ensure consistency in the curl args
	if(curl_address != NULL){
		if(curl_url == NULL){
			gslog(LOG_EMERG,"Curl IP defined, but there is no url (e.g. /foo/bar");
			exit(1);
		}
		if(curl_auth==NULL){
			curl_auth = "";
		} 
	}
    
    gettimeofday(&tvs, 0);
    argc -=2;
    argv +=2;
    if (argc < 1)
        goto usage;
    
    /* initialize host library and the sgroup  */
    
    if (verbose>=2) fprintf(stderr,"Initializing gscp\n");
    
    if (ftaapp_init(bufsz)!=0) {
        fprintf(stderr,"%s::error:could not initialize gscp\n", me);
        exit(1);
    }
    
    signal(SIGTERM, hand);
    signal(SIGINT, hand);
    
    schema = ftaapp_get_fta_schema_by_name(argv[0]);
    if (schema < 0) {
        fprintf(stderr,"%s::error:could not get fta '%s' schema\n",
                me ,argv[0]);
        exit(1);
    }
	n_expected_param = ftaschema_parameter_len(schema);
    if (n_expected_param == 0) {
        pblk = 0;
        pblklen = 0;
    } else {
		n_actual_param = argc-1;
		if(n_actual_param < n_expected_param){
			fprintf(stderr,"Error, %d query parameters expected, %d provided.\n",n_expected_param, n_actual_param);
			exit(1);
		}
        /* parse the params */
        for (lcv = 1 ; lcv < argc ; lcv++) {
            char *k, *e;
            int rv;
            k = argv[lcv];
            e = k;
            while (*e && *e != '=') e++;
            if (*e == 0) {
                fprintf(stderr,"param parse error '%s' (fmt 'key=val')\n",
                        argv[lcv]);
                exit(1);
            }
            *e = 0;
            rv = ftaschema_setparam_by_name(schema, k, e+1, strlen(e+1));
            *e = '=';
            if (rv < 0) {
                fprintf(stderr,"param setparam error '%s' (fmt 'key=val')\n",
                        argv[lcv]);
                exit(1);
            }
        }
        if (ftaschema_create_param_block(schema, &pblk, &pblklen) < 0) {
            fprintf(stderr, "ftaschema_create_param_block failed!\n");
            exit(1);
        }
    }
//    ftaschema_free(schema); /* XXXCDC */ // the schema continues to be used
    
    
    if (verbose>=2) fprintf(stderr,"Initalized FTA\n");
    
    fta_id=ftaapp_add_fta(argv[0],0,0,0,pblklen,pblk);
    if (fta_id.streamid==0) {
        fprintf(stderr,"%s::error:could not initialize fta %s\n",
                me, argv[0]);
        exit(1);
    }
    /* XXXCDC: pblk is malloc'd, should we free it? */
    
    if (verbose>=2) fprintf(stderr,"Get schema handle\n");
    
    if ((schema=ftaapp_get_fta_schema(fta_id))<0) {
        fprintf(stderr,"%s::error:could not get schema\n", me);
        exit(1);
    }
    
    if ((numberoffields=ftaschema_tuple_len(schema))<0) {
        fprintf(stderr,"%s::error:could not get number of fields in schema\n",
                me);
        exit(1);
    }
    
    if (verbose>=1) {
        for(y=0; y<numberoffields;y++) {
            printf("%s",ftaschema_field_name(schema,y));
            if (y<numberoffields-1) printf("|");
        }
        printf("\n");
    }
    if (xit) {	// -X in command line
        gettimeofday(&tve, 0);
        timersub(&tve, &tvs, &tvd);
        printf("TIME= %ld%06d sec\n", tvd.tv_sec, tvd.tv_usec);
        hand(0);	// effectively an exit
    }
    if (tcpport!=0) {
    	wait_for_client();
    }

    start_time = time(NULL);

	int measurement_interval_pos = -1; // extract measurementInterval if present
	char *field_names[numberoffields];
    for(y=0; y<numberoffields;y++) {
		field_names[y] = strdup(ftaschema_field_name(schema,y));
		if(strcmp(field_names[y], "measurementInterval")==0)
			measurement_interval_pos = y;
	}


	struct timeval tsample;
	gettimeofday(&tsample, 0);
	char start_ts[100], curr_ts[100];
	sprintf(start_ts,"%ld%06d", tsample.tv_sec, tsample.tv_usec);

	long unsigned int lineno=0;
	long unsigned int seqno=0;
	unsigned int measurement_interval;
    while((code=ftaapp_get_tuple(&rfta_id,&rsize,rbuf,2*MAXTUPLESZ,0))>=0) {
		lineno++;
        if (dump)	// -D in command line
            continue;
        if (ftaschema_is_eof_tuple(schema, rbuf)) {
            /* initiate shutdown or something of that nature */
            printf("#All data proccessed\n");
            exit(0);
        }
        if (!rsize)
            continue;
        if (verbose >=2) {
            snprintf(linebuf,MAXLINE,"RESULT CODE => %u\n",code);
            emit_line();
        }
        if ((code==0)&&(rfta_id.streamid == fta_id.streamid)) {
			seqno++;
			gettimeofday(&tsample, 0);
			sprintf(curr_ts,"%ld%06d", tsample.tv_sec, tsample.tv_usec);
			int pos;
			if(ves_version < 7){
				pos = snprintf(linebuf, MAXLINE,
  "{\"event\": { \"commonEventHeader\": { "
        "\"domain\": \"measurementsForVfScaling\", "
        "\"eventId\": \"%s%u\", "
        "\"eventType\": \"%s\", "
        "\"eventName\": \"Measurement_MC_%s\", "
        "\"lastEpochMicrosec\": %s, "
        "\"priority\": \"Normal\", "
        "\"reportingEntityName\": \"gs-lite MC\", "
        "\"sequence\": %u, "
        "\"sourceName\": \"meas_cmpgn_xapp\", "
        "\"startEpochMicrosec\": %s, "
        "\"version\": 5 "
      "}, "
      "\"measurementsForVfScalingFields\": { "
	  	"\"additionalFields\": ["
				,argv[0],lineno, argv[0], argv[0], curr_ts, seqno, start_ts
				);
			}else{
				pos = snprintf(linebuf, MAXLINE,
  "{\"event\": { \"commonEventHeader\": { "
        "\"domain\": \"measurement\", "
        "\"eventId\": \"%s%u\", "
        "\"eventType\": \"%s\", "
        "\"eventName\": \"Measurement_MC_%s\", "
        "\"lastEpochMicrosec\": %s, "
        "\"priority\": \"Normal\", "
        "\"reportingEntityName\": \"gs-lite MC\", "
        "\"sequence\": %u, "
        "\"sourceName\": \"meas_cmpgn_xapp\", "
        "\"startEpochMicrosec\": %s, "
        "\"version\": \"4.0.1\", "
        "\"vesEventListenerVersion\": \"7.0.1\" "
      "}, "
      "\"measurementFields\": { "
	  	"\"additionalFields\": {"
				,argv[0],lineno, argv[0], argv[0], curr_ts, seqno, start_ts
				);
			}

			measurement_interval = 0;
            for(y=0; y<numberoffields;y++) {
                struct access_result ar;
//                if (verbose>=2)
//                    printf("%s->",ftaschema_field_name(schema,y));
              	if(y>0){
					linebuf[pos]=',';
					pos++;
				}
                ar=ftaschema_get_field_by_index(schema,y,rbuf,rsize);
                switch (ar.field_data_type) {
                    case INT_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%d\"}",field_names[y], ar.r.i);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos," \"%s\": \"%d\"",field_names[y], ar.r.i);
						if(y==measurement_interval_pos)
							measurement_interval = (unsigned int)ar.r.i;
                        break;
                    case UINT_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%u\"}",field_names[y], ar.r.ui);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos," \"%s\": \"%u\"",field_names[y], ar.r.ui);
						if(y==measurement_interval_pos)
							measurement_interval = (unsigned int)ar.r.ui;
                        break;
                    case IP_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%u.%u.%u.%u\"}",field_names[y], ar.r.ui>>24&0xff,
                                 ar.r.ui>>16&0xff,
                                 ar.r.ui>>8&0xff,
                                 ar.r.ui&0xff);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"%u.%u.%u.%u\"",field_names[y], ar.r.ui>>24&0xff,
                                 ar.r.ui>>16&0xff,
                                 ar.r.ui>>8&0xff,
                                 ar.r.ui&0xff);
                        break;
                    case IPV6_TYPE:
                    {
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"",field_names[y]);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos," \"%s\": \"",field_names[y]);
                        unsigned x;
                        unsigned zc=0;
                        for(x=0;x<4;x++) { if (ar.r.ip6.v[x]==0) zc++;}
                        if (zc!=4) {
                            snprintf(linebuf,MAXLINE,"");
                            for(x=0;x<8;x++) {
                                unsigned char * a = (unsigned char *)  &(ar.r.ip6.v[0]);
                                unsigned y;
                                y=((unsigned)a[2*x])<<8|((unsigned) a[2*x+1]);
                                pos += snprintf(linebuf+pos,MAXLINE-pos,"%04x",y);
                                if (x<7){
									pos += snprintf(linebuf+pos,MAXLINE-pos,":");
								}
                            }
                        } else {
                            pos+=snprintf(linebuf+pos,MAXLINE-pos,"::");
                        }
						if(ves_version < 7)
							pos += snprintf(linebuf+pos, MAXLINE-pos,"\"}");
						else
							pos += snprintf(linebuf+pos, MAXLINE-pos,"\"");
                    }
                        break;
                        
                    case USHORT_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%u\"}",field_names[y], ar.r.ui);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\":  \"%u\"}",field_names[y], ar.r.ui);
						if(y==measurement_interval_pos)
							measurement_interval = (unsigned int)ar.r.ui;
                        break;
                    case BOOL_TYPE:
						if(ves_version < 7){
	                        if (ar.r.ui==0) {
   		                     	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"FALSE\"}",field_names[y]);
   		                     } else {
   		                     	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"TRUE\"}",field_names[y]);
   	                     	}
						}else{
	                        if (ar.r.ui==0) {
   		                     	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"FALSE\"",field_names[y]);
   		                     } else {
   		                     	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"TRUE\"",field_names[y]);
   	                     	}
						}
                        break;
                    case ULLONG_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%llu\"}",field_names[y], ar.r.ul);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"%llu\"",field_names[y], ar.r.ul);
						if(y==measurement_interval_pos)
							measurement_interval = (unsigned int)ar.r.ul;
                        break;
                    case LLONG_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%lld\"}",field_names[y], ar.r.l);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"%lld\"",field_names[y], ar.r.l);
						if(y==measurement_interval_pos)
							measurement_interval = (unsigned int)ar.r.l;
                        break;
                    case FLOAT_TYPE:
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%f\"}",field_names[y], ar.r.f);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"%f\"",field_names[y], ar.r.f);
                        break;
                    case TIMEVAL_TYPE:
                    {
                        gs_float_t t;
                        t= ar.r.t.tv_usec;
                        t=t/1000000;
                        t=t+ar.r.t.tv_sec;
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"%f\"}",field_names[y], t);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"%f\"",field_names[y], t);
                    }
                        break;
                    case VSTR_TYPE:
                    {
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"{\"name\": \"%s\", \"value\": \"",field_names[y]);
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"%s\": \"",field_names[y]);
                        int x;
                        int c;
                        char * src;
                        src=(char*)ar.r.vs.offset;
						for(x=0;x<ar.r.vs.length;x++){
                            c=src[x];
                            if ((c<='~') && (c>=' ')) {
                                if (pos<MAXLINE-1) {
                                    linebuf[pos]=c;
                                    pos++;
                                }
                            } else {
                                if (pos<MAXLINE-1) {
                                    linebuf[pos]='.';
                                    pos++;
                                }
                            }
						}
						if(ves_version < 7)
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"}");
						else
                        	pos += snprintf(linebuf+pos,MAXLINE-pos,"\"");
                    }
                        break;
                    default:
                        linebuf[0]=0;
                        break;
                }
			}
			if(ves_version < 7){
				snprintf(linebuf+pos, MAXLINE-pos,
	  	"], \"measurementInterval\": %u, \"measurementsForVfScalingVersion\": 1"
		"}}}\n", measurement_interval
				);
			}else{
				snprintf(linebuf+pos, MAXLINE-pos,
	  	"}, \"measurementInterval\": %u, \"measurementFieldsVersion\": \"4.0\""
		"}}}\n", measurement_interval
				);
			}
			if(curl_address==NULL){
            	emit_line();
			}else{
				http_post_request_hdr(curl_endpoint, curl_url, linebuf, &http_code, curl_auth);
				if(http_code != 200 && http_code != 202){
					gslog(LOG_WARNING, "http return code is %d\n",http_code);
				}
			}
            if (verbose!=0) fflush(stdout);
        } else {
            if (rfta_id.streamid != fta_id.streamid)
                fprintf(stderr,"Got unkown streamid %llu \n",rfta_id.streamid);
        }

        // whenever we receive a temp tuple check if we reached time limit
        if ((code==2)  && tlimit && (time(NULL)-start_time)>=tlimit) {
            fprintf(stderr,"Reached time limit of %d seconds\n",tlimit);    
            ftaapp_exit();
            exit(0);
        }        
    }
}

