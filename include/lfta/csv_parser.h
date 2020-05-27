#ifndef __CSV_PARSER__
#define __CSV_PARSER__

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

#include "packet.h"

 // maximum number of fields to be parsed in CSV record
static gs_uint32_t max_field = CSVELEMENTS;


static gs_uint8_t delim;


static inline void csv_set_delim(gs_uint8_t del) {
    delim = del;
}

static inline void csv_set_maxfield(gs_uint32_t max) {
    max_field = max;
}

static inline void csv_parse_line(gs_sp_t line, ssize_t len) {

    cur_packet.systemTime=time(0);

    gs_uint32_t i=0;
    gs_uint32_t p=0;
    gs_uint32_t last_field_start=0;

    while(i<len){
		last_field_start=i;
        cur_packet.record.csv.fields[p]=&line[i];
        while((i<len)&&(line[i] != delim)) {
            i++;
        }
        cur_packet.record.csv.field_lens[p]=i-last_field_start;
        i++;
  	    p++;	
    }
    cur_packet.record.csv.numberfields=p;

}


#endif

