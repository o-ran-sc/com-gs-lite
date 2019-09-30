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
#include <schemaparser.h>
#include "gsconfig.h"
#include "gstypes.h"
#include <math.h>


FILE * ifd;
FILE * ofd;
FILE * sfd;

#define MAX_GDAT_HEADER 10000

gs_int8_t buf[2*MAXTUPLESZ];
gs_int8_t schema_buf[MAX_GDAT_HEADER];
gs_int8_t header_buf[MAX_GDAT_HEADER];


gs_retval_t read_tuple(gs_uint32_t * sz, gs_sp_t data, gs_int32_t maxlen) {
    gs_uint32_t nsz;
    static gs_uint32_t read=0;
again:
    if (fread(&nsz,sizeof(gs_uint32_t),1,ifd)!=1) {
        
        exit(0);
    }
    read=read+sizeof(gs_uint32_t);
    *sz=ntohl(nsz);
    if ((*sz)>maxlen) {
        fprintf(stderr,"INTERNAL ERROR tuple to long for fixed buffer. Tuple sz %u\n",
                (*sz));
        *sz=0;
        return 0;
    }
    if (*sz==0) goto again;
    if (fread(data,(*sz),1,ifd)!=1) {
        fprintf(stderr,"UNEXPECTED END OF FILE. Tried to read tuple of size %u\n",
                (*sz));
        exit(0);
    }
    read=read+*sz;
    return 0;
}

int main(int argc, char** argv) {
    gs_schemahandle_t schema;
    
    gs_uint32_t rsize;
    gs_int8_t rbuf[2*MAXTUPLESZ];
    gs_int8_t wbuf[2*MAXTUPLESZ];
    
    gs_int32_t numberoffields;
    gs_int32_t verbose=0;
    gs_int32_t y;
    gs_int32_t parserversion;
    gs_uint32_t schemalen;
    gs_sp_t me;
    gs_int32_t ch;
    
    me=argv[0];
    
    if (argc<2) {
        fprintf(stderr,
                "%s::usage: %s -v -x <schema_file_name> <input_file_name> <output_file_name>\n",
                me,me);
        exit(1);
    }
    
    while ((ch = getopt(argc, argv, "vx")) != -1) {
        switch(ch) {
            case 'v':
                verbose=1;
                break;
            case 'x':
                verbose=2;
        }
    }
    argc -= optind;
    if (argc < 1) {
        fprintf(stderr,"%s::usage: %s -v -x <schema_file_name> <input_file_name> <output_file_name>\n",
                me,me);
        exit(1);
    }
    argv += optind;

    if ((sfd=fopen(argv[0],"r"))==0) {
        fprintf(stderr,"%s::error:could not open schema file %s\n",
                me,argv[0]);
        exit(1);
    }

    schemalen = fread(schema_buf, 1, MAX_GDAT_HEADER, sfd);
    schema_buf[schemalen] = 0;
    schema = ftaschema_parse_string_prot(schema_buf);
    if (schema < 0) {
        fprintf(stderr,"%s::error:unable to parse schema file %s\n",
                me,argv[0]);
        exit(1);        
    }
    fclose(sfd);
    
    argv++;
    
    if ((strcmp(argv[0],"-")!=0)&&(strcmp(argv[0],"stdin")!=0)) {
        if ((ifd=fopen(argv[0],"r"))==0) {
            fprintf(stderr,"%s::error:could not open input file %s\n",
                    me,argv[0]);
            exit(1);
        }
    } else {
        ifd = stdin;
    }

    argv++;

    if ((ofd=fopen(argv[0],"wb"))==0) {
        fprintf(stderr,"%s::error:could not open output file %s\n",
                me,argv[0]);
        exit(1);
    }
    
    parserversion = get_schemaparser_version();

    // write GDAT header
	sprintf(header_buf,"GDAT\nVERSION:%u\nSCHEMALENGTH:%lu\n",
			parserversion,schemalen+1);
    // need to get ASCII version of schema
	fwrite(header_buf,strlen(header_buf),1,ofd);
	fwrite(schema_buf,schemalen+1,1,ofd);

    /////////////////////////////////////////////

    
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

    unsigned long long tup_cnt = 0;

    while(!feof(ifd)) {
        fgets(rbuf,2*MAXTUPLESZ,ifd);
        
        gs_uint32_t tuple_pos = ftaschema_get_tuple_metadata_offset(schema) + 1;     // position to copy string payload

        char* field = strtok(rbuf, ","); 
        y = 0;
        do {
            gs_int32_t field_type = ftaschema_get_field_type_by_index(schema, y);
            gs_int32_t field_offset = ftaschema_get_field_offset_by_index(schema, y);

            gs_int32_t i;
            gs_uint32_t ui;      
            gs_uint64_t ul;   
            gs_uint64_t l; 
            gs_float_t f,intpart,fractpart;     
            struct timeval t;  
            struct vstring32 vs;           
            struct hfta_ipv6_str ip6;       
            gs_uint32_t v[8];     
	        unsigned ip1,ip2,ip3,ip4;

            switch (field_type) {
                case BOOL_TYPE:    
                    ui=(strncasecmp("TRUE",field,4)==0);
                    memcpy(wbuf+field_offset,&ui,sizeof(ui));                                    
                    break;
                case INT_TYPE:
                    sscanf(field,"%d",&i);
                    memcpy(wbuf+field_offset,&i,sizeof(i));
                    break;
                case UINT_TYPE:
                case USHORT_TYPE:                            
                    sscanf(field,"%u",&ui);
                    memcpy(wbuf+field_offset,&ui,sizeof(ui));                                    
                    break;
                case ULLONG_TYPE:
                    sscanf(field,"%llu",&ul);
                    memcpy(wbuf+field_offset,&ul,sizeof(ul));                    
                    break;
                case LLONG_TYPE:
                    sscanf(field,"%ldu",&l);
                    memcpy(wbuf+field_offset,&l,sizeof(l));                        
                    break;
                case FLOAT_TYPE:
                    sscanf(field,"%f",&f);
                    memcpy(wbuf+field_offset,&f,sizeof(f));                        
                    break;
                case VSTR_TYPE:
                {
                    if (!strcmp(field, " "))
                        field[0] = 0;
                    vs.length = strlen(field);
                    vs.offset = tuple_pos;
                    vs.reserved = 0;      
                    memcpy(wbuf+vs.offset, field, vs.length);
                    memcpy(wbuf+field_offset,&vs,sizeof(vs));  
                    tuple_pos += vs.length;
                }
                    break;   
                case IP_TYPE:
                    sscanf(field,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4);
	                ui=(ip1<<24)|(ip2<<16)|(ip3<<8)|ip4;
                    memcpy(wbuf+field_offset,&ui,sizeof(ui));                        
                    break;  
                case IPV6_TYPE:
                    sscanf(field,"%x:%x:%x:%x:%x:%x:%x:%x",&v[0],&v[1],&v[2],&v[3],&v[4],&v[5],&v[6],&v[7]);
	                ip6.v[0]=htonl(v[0]<<16|v[1]);
	                ip6.v[1]=htonl(v[2]<<16|v[3]);
	                ip6.v[2]=htonl(v[4]<<16|v[5]);
	                ip6.v[3]=htonl(v[6]<<16|v[7]);
                    memcpy(wbuf+field_offset,&ip6,sizeof(ip6));                        
                    break;                                                        
                case TIMEVAL_TYPE:
                    sscanf(field,"%lf sec",&f);  
                    fractpart=modf(f,&intpart);                  
                    t.tv_sec = intpart;
                    t.tv_usec = fractpart * 1000000;
                    memcpy(wbuf+field_offset,&t,sizeof(t));                        
                    break; 
                default:
                    break;
            }
            y++;
            field = strtok(NULL, ",");            
        } while (y < numberoffields);
        gs_uint32_t tup_len = htonl(tuple_pos);
        fwrite(&tup_len,sizeof(gs_uint32_t),1,ofd);
        fwrite(wbuf,tuple_pos,1,ofd);
        tup_cnt++;

        if (tup_cnt % 1000000 == 0)
            printf("dumped %llu tuples\n", tup_cnt);
    }

    fclose(ifd);
    fclose(ofd);
    if (verbose!=0) fflush(stdout);

    exit(0);
}

