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

#include <schemaparser.h>
#include "gsconfig.h"
#include "gstypes.h"
#include "gshub.h"

#define MAXLINE 100000
static unsigned tcpport=0;
static char linebuf[MAXLINE];
int listensockfd=0;
int fd=0;
gs_int32_t verbose=0;
endpoint hub;
endpoint ds;
gs_sp_t sink_name;


static void wait_for_feed() {
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t clilen;
    struct sockaddr_in sin;
    socklen_t sin_sz;
    if (listensockfd==0) {
		gs_int32_t on = 1;
        
        if (verbose==2) {
            fprintf(stderr,"Create listen socket for port %u\n",tcpport);
        }
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
    
    if (verbose==2) {
        fprintf(stderr,"Socket created waiting for data producer\n");
    }
    if (listen(listensockfd,5)< 0) {
        fprintf(stderr,"Error::could not listen to socket for port %u \n",ntohs(serv_addr.sin_port));
        close(listensockfd);
        exit(1);
    }
    sin_sz=sizeof(sin);
    if (getsockname(listensockfd, (struct sockaddr *) &sin, &sin_sz) < 0) {
        fprintf(stderr,"Error::could not get local port number of listen socket\n");
        exit(1);
    }
    ds.ip=htonl(127<<24|1);
    ds.port=sin.sin_port;
    if (set_streamsink(hub,sink_name,ds)!=0) {
        fprintf(stderr,"Error::could not set sink in GSHUB for %s source name\n",sink_name);
        exit(1);
    }
    
	do {
		clilen = sizeof(cli_addr);
		fd=accept(listensockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (fd<0) {
            gslog(LOG_EMERG,"Error:Could not accept connection on tcp socket");
		}
	} while (fd==0);
    if (verbose) {
        fprintf(stderr,"Producer found ready to rock!\n");
    }
    
}


static void gs_read(gs_sp_t buffer, gs_uint32_t length){
	gs_uint32_t used=0;
	gs_uint32_t cur;
    
	while(used < length) {
        if (verbose==2) {
            fprintf(stderr,"\tread %u out of %u\n",used,length);
        }
		if ((cur=read(fd,&(buffer[used]),length-used))<=0) {
			gslog(LOG_EMERG,"ERROR:could not read data from gdat stream");
			exit(0);
		}
		used+=cur;
	}
}

static void gs_read_line(gs_sp_t buffer, gs_uint32_t length){
    gs_uint32_t used=0;
    gs_uint32_t cur;
    
    while((used < (length-1)) && ((used==0)|| (buffer[used-1]!='\n'))) {
        if ((cur=read(fd,&(buffer[used]),1))<=0) {
            gslog(LOG_EMERG,"ERROR:could not read data from gdat stream");
            exit(0);
        }
        used+=cur;
    }
	buffer[used]=0;
}

static gs_uint32_t get_stream_tuple(gs_uint32_t * rsize,gs_sp_t rbuf,gs_uint32_t bufsz){
    
    gs_uint32_t nsz,sz;
    gs_read((gs_sp_t)&nsz,sizeof(gs_uint32_t));
    sz=ntohl(nsz);
    if (sz>MAXTUPLESZ) {
        gslog(LOG_EMERG,"Error::Illegal tuple received");
        exit(0);
    }
    
    if (sz>bufsz) {
        gslog(LOG_EMERG,"Error::Illegal tuple size received -- to long");
        exit(0);
    }
    *rsize=sz;
    
    gs_read(rbuf,(sz));
    return 0;
}

int main(int argc, char** argv) {
    gs_uint32_t streamid;
    gs_schemahandle_t schema;
    
    gs_uint32_t rstreamid;
    gs_uint32_t rsize;
    gs_int8_t rbuf[2*MAXTUPLESZ];
    
    gs_int32_t numberoffields;
    gs_int32_t y;
    gs_int32_t parserversion;
    gs_uint32_t schemalen;
    gs_sp_t asciischema;
    gs_sp_t me;
    gs_int32_t ch;
    
    gs_int8_t buf[1024];
    gs_uint32_t tip1,tip2,tip3,tip4;
    
    /* initialize host library and the sgroup  */
    
    me=argv[0];
    
    while ((ch = getopt(argc, argv, "hvxp:")) != -1) {
        switch(ch) {
            case 'h':
                fprintf(stderr,"%s::usage: %s -v -x -p <port>  <IP>:<port> <source_name> \n",argv[0],argv[0]);
                exit(0);
                break;
            case 'p':
                tcpport=atoi(optarg);;
                break;
            case 'v':
                verbose=1;
                break;
            case 'x':
                verbose=2;
                break;
            default:
                break;
        }
    }
    if (optind+2>argc) {
        fprintf(stderr,"Could not find hub and stream source name on command line\n");
        exit(1);
    }
    if (sscanf(argv[optind],"%u.%u.%u.%u:%hu",&tip1,&tip2,&tip3,&tip4,&(hub.port))!= 5 ) {
        fprintf(stderr,"Could not parse hub endpoint\n");
        exit(1);
    }
    hub.ip=htonl(tip1<<24|tip2<<16|tip3<<8|tip4);
    hub.port=htons(hub.port);
    sink_name=strdup(argv[optind+1]);
    
    wait_for_feed();
    
    gs_read_line(buf,1024);
    if (strncmp(buf,"GDAT",4)!=0) {
        gslog(LOG_EMERG,"ERROR: not a GDAT stream\n");
        exit(0);
    }
    gs_read_line(buf,1024);
    if (sscanf(buf,"VERSION:%u\n",&parserversion)!=1) {
        gslog(LOG_EMERG,"ERROR: no GDAT VERSION given\n");
        exit(0);
    }
    gs_read_line(buf,1024);
    if (sscanf(buf,"SCHEMALENGTH:%u\n",&schemalen)!=1) {
        gslog(LOG_EMERG,"ERROR: no GDAT SCHEMALENGTH given\n");
        exit(0);
    }
    
    if(verbose==2) {
        fprintf (stderr,"GDAT version %u schemalength %u\n",parserversion,schemalen);
    }
	
    if (schemaparser_accepts_version(parserversion)!=1) {
        fprintf(stderr,"%s::error: wrong parser version %u for file %s\n",
                me,parserversion,argv[0]);
        exit(1);
    }
    
    if ((asciischema=malloc(schemalen))==0) {
        fprintf(stderr,"%s::error: could not allocate schema buffer of sz %u "
                "for file %s\n",
                me,schemalen,argv[0]);
        exit(1);
    }
    
    if(verbose==2) {
        fprintf (stderr,"Reading schema from scocket\n");
    }
    
    gs_read(asciischema,schemalen);
    
    if(verbose==2) {
        fprintf (stderr,"Received schema\n");
    }
    
    if (verbose==2) {
        fprintf(stderr,"%s\n",asciischema);
    }
    if ((schema=ftaschema_parse_string(asciischema))<0) {
        fprintf(stderr,"%s::error: could not parse schema  \n",
                me);
        exit(1);
    }
    
    if ((numberoffields=ftaschema_tuple_len(schema))<0) {
        fprintf(stderr,"%s::error:could not get number of fields in schema\n",
                me);
        exit(1);
    }
    if (verbose==1) {
        for(y=0; y<numberoffields;y++) {
            printf("%s",ftaschema_field_name(schema,y));
            if (y<numberoffields-1) printf("|");
        }
        printf("\n");
    }
    while(get_stream_tuple(&rsize,rbuf,2*MAXTUPLESZ)==0) {
        if (verbose) {
            if (ftaschema_is_eof_tuple(schema, rbuf)) {
                /* initiate shutdown or something of that nature */
                fprintf(stderr,"%s::All data proccessed\n",me);
            } else {
                if (ftaschema_is_temporal_tuple(schema, rbuf)) {
                    /* initiate shutdown or something of that nature */
                    fprintf(stderr,"%s:: temporal tuple\n",me);
                } else {
                    fprintf(stderr,"%s:: regular tuple\n",me);
                }
            }
        }
        
        if ((!rsize) )
            continue;
        for(y=0; y<numberoffields;y++) {
            struct access_result ar;
            if (verbose==2)
                printf("%s->",ftaschema_field_name(schema,y));
            ar=ftaschema_get_field_by_index(schema,y,rbuf,rsize);
            switch (ar.field_data_type) {
                case INT_TYPE:
                    printf("%d",ar.r.i);
                    break;
                case UINT_TYPE:
                    printf("%u",ar.r.ui);
                    break;
                case IP_TYPE:
                    printf("%u.%u.%u.%u",ar.r.ui>>24&0xff,
                           ar.r.ui>>16&0xff,
                           ar.r.ui>>8&0xff,
                           ar.r.ui&0xff);
                    break;
                case IPV6_TYPE:
                {
                    unsigned x;
                    unsigned zc=0;
                    for(x=0;x<4;x++) { if (ar.r.ip6.v[x]==0) zc++;}
                    if (zc!=4) {
                        for(x=0;x<8;x++) {
                            unsigned char * a = (unsigned char *)  &(ar.r.ip6.v[0]);
                            unsigned y;
                            y=((unsigned)a[2*x])<<8|((unsigned) a[2*x+1]);
                            printf("%04x",y);
                            if (x<7) printf(":");
                        }
                    } else {
                        printf("::");
                    }
                }
                    break;
                case USHORT_TYPE:
                    printf("%hu",(unsigned short)ar.r.ui);
                    break;
                case BOOL_TYPE:
                    if (ar.r.ui==0) {
                        printf("FALSE");
                    } else {
                        printf("TRUE");
                    }
                    break;
                case ULLONG_TYPE:
                {
                    gs_uint64_t ul;
                    gs_uint64_t t1;
                    gs_uint64_t t2;
                    ul=ar.r.ul;
                    printf("%llu",ul);
                }
                    break;
                case LLONG_TYPE:
                    printf("%lld",ar.r.l);
                    break;
                case FLOAT_TYPE:
                    printf("%f",ar.r.f);
                    break;
                case TIMEVAL_TYPE:
                { 
                    gs_float_t t;
                    t= ar.r.t.tv_usec;
                    t=t/1000000;
                    t=t+ar.r.t.tv_sec;
                    printf("%lf sec",t);
                }
                    break;
                case VSTR_TYPE:
                {
                    int x;
                    int c;
                    char * src;
                    src=(gs_sp_t)ar.r.vs.offset;
                    if ((ar.r.vs.length>0) && (src[ar.r.vs.length-1]==0)) {
                        ar.r.vs.length = ar.r.vs.length-1;
                    }
                    for(x=0;x<ar.r.vs.length;x++) {
                        c=src[x];
                        if (((c<='~') && (c>=' '))&&(c!='|')) {
                            printf("%c",c);
                        } else {
                            printf("(0x%x)",(gs_uint8_t)c);
                        }
                    }
                }
                    break;
                default:
                    break;
            }
            if (y<numberoffields-1) printf("|");
        }
        printf("\n");
        if (verbose!=0) fflush(stdout);
    }
    exit(0);
}

