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
#ifndef PACKET_H
#define PACKET_H

#include "gsconfig.h"
#include "gstypes.h"

#ifndef IPV6_STR
#define IPV6_STR
struct ipv6_str{
    gs_uint32_t v[4];
};
#endif

#define PTYPE_CSV 1
#define PTYPE_GDAT 2
#define PTYPE_STRUCT 3

#define CSVELEMENTS 1000
#define GDATELEMENTS 1000

struct csv {
    gs_uint32_t numberfields;
    gs_sp_t fields[CSVELEMENTS];
};

struct csv2 {       // SSE accelerated CSV processor
    gs_uint32_t numberfields;
    gs_sp_t fields[CSVELEMENTS];
    gs_uint32_t field_lens[CSVELEMENTS];
    gs_uint8_t parsed[CSVELEMENTS];
};

struct gdat {
    gs_schemahandle_t schema;
    gs_uint32_t numfields;
    gs_uint32_t datasz;
    gs_uint8_t data[MAXTUPLESZ];
};

struct packed {
	void *values;
	gs_sp_t *existence_bitmap;
};

struct packet {
    gs_uint32_t systemTime;
    gs_uint32_t ptype; /* type of record e.g. PTYPE_CSV */
	gs_schemahandle_t schema;
    union {
        struct csv csv; /* content of CSV record being processed */
        struct csv2 csv2;     
        struct gdat gdat;
		struct packed packed;
	} record;
    
};


#endif
