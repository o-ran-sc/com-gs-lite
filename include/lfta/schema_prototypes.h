#ifndef __SCHEMA_PROTOTYPES__
#define __SCHEMA_PROTOTYPES__

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


#define PRECOMP
#include "gsconfig.h"
#include "gstypes.h"

#include "fta.h"
#include "rts_external.h"
#include "packet.h"
#include "md_stdlib.h"
#include "schemaparser.h"

// parser sanity checks
// #define PARSER_SANITY_CHECKS


// *** SAMPLING RELATED CONSTANTS
// ******************************

// Make sure the hash table sizes are powers of 2-1 since they are used to compute the module with an and.
// collions on the flow hash are handled properly so they are not that bad
#define MAX_FLOWRECORD_HASH 0x1fffff
// keep the collision rate low on denies
#define MAX_DENY_HASH 0x7fffff
// one out of SAMPLING_RATE+1 sampling
#define SAMPLING_RATE 19
// sampling probability
#define FLOWSAMPPROB (((gs_float_t)1)/((gs_float_t)SAMPLING_RATE+1))
// wait for SAMPLED_FLOW_TIMEOUT  seconds idle time to time a flow out
#define SAMPLED_FLOW_TIMEOUT 30
// check if we haven't seen that flow in SAMPLED_FLOW_IDLE_TIME seconds to make sure we don't catch it in the midle
#define SAMPLED_FLOW_IDLE_TIME 30

// PACKET SAMPLING RATE one in SAMPLED_PACKETS will be sampled
#define SAMPLED_PACKETS 200
// SAMPLING probability
#define PACKETSAMPPROB (((gs_float_t)1)/((gs_float_t)SAMPLED_PACKETS))

// COMBINE probability
#define COMBINEDPROB (((gs_float_t)1)-(((gs_float_t)1)-FLOWSAMPPROB)*(((gs_float_t)1)-PACKETSAMPPROB))

/* General packet access functions */

static inline gs_retval_t get_system_time(struct packet * p, gs_uint32_t * t)
{
	*t=(gs_uint32_t) p->systemTime;
	return 0;
}
static inline gs_retval_t get_schemaId(struct packet * p, gs_uint32_t * t)
{
	*t=(gs_uint32_t) p->schema;
	return 0;
}

// fast unsigned integer parsing functions
static inline __attribute__((always_inline)) unsigned long gs_strtoul (const char *str, size_t len) {
        unsigned long value = 0;

        switch (len) { // handle up to 10 digits, assume we're 32-bit
            case 10:    value += (str[len-10] - '0') * 1000000000;
            case  9:    value += (str[len- 9] - '0') * 100000000;
            case  8:    value += (str[len- 8] - '0') * 10000000;
            case  7:    value += (str[len- 7] - '0') * 1000000;
            case  6:    value += (str[len- 6] - '0') * 100000;
            case  5:    value += (str[len- 5] - '0') * 10000;
            case  4:    value += (str[len- 4] - '0') * 1000;
            case  3:    value += (str[len- 3] - '0') * 100;
            case  2:    value += (str[len- 2] - '0') * 10;
            case  1:    value += (str[len- 1] - '0');
                return value;
            default:
                return 0;
        }
}

static inline __attribute__((always_inline)) unsigned long long gs_strtoull (const char *str, size_t len) {
        unsigned long long value = 0;

        switch (len) { // handle up to 10 digits, assume we're 32-bit
            case 20:    value += (str[len-20] - '0') * 10000000000000000000UL;
            case 19:    value += (str[len-19] - '0') * 1000000000000000000UL;
            case 18:    value += (str[len-18] - '0') * 100000000000000000UL;
            case 17:    value += (str[len-17] - '0') * 10000000000000000UL;
            case 16:    value += (str[len-16] - '0') * 1000000000000000UL;
            case 15:    value += (str[len-15] - '0') * 100000000000000UL;
            case 14:    value += (str[len-14] - '0') * 10000000000000UL;
            case 13:    value += (str[len-13] - '0') * 1000000000000UL;
            case 12:    value += (str[len-12] - '0') * 100000000000UL;
            case 11:    value += (str[len-11] - '0') * 10000000000UL;
            case 10:    value += (str[len-10] - '0') * 1000000000UL;
            case  9:    value += (str[len- 9] - '0') * 100000000UL;
            case  8:    value += (str[len- 8] - '0') * 10000000UL;
            case  7:    value += (str[len- 7] - '0') * 1000000UL;
            case  6:    value += (str[len- 6] - '0') * 100000UL;
            case  5:    value += (str[len- 5] - '0') * 10000UL;
            case  4:    value += (str[len- 4] - '0') * 1000UL;
            case  3:    value += (str[len- 3] - '0') * 100UL;
            case  2:    value += (str[len- 2] - '0') * 10UL;
            case  1:    value += (str[len- 1] - '0');
                return value;
            default:
                return 0;
        }
}

static inline __attribute__((always_inline)) long gs_strtol (const char *str, size_t len) {
    long sign = 1;
    if (str[0] == '-') { 
        sign = -1;
        ++str;
        --len;
    }
    return sign * gs_strtoul(str, len);
}

static inline __attribute__((always_inline)) long gs_strtoll (const char *str, size_t len) {
    long long sign = 1;
    if (str[0] == '-') { 
        sign = -1;
        ++str;
        --len;
    }
    return sign * gs_strtoull(str, len);
}

/* CSV access function using position as 3rd argument */

static inline gs_retval_t get_csv_uint(struct packet * p, gs_uint32_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif
//    *t = strtoul((const char*)p->record.csv.fields[pos-1], NULL, 10);
    *t = gs_strtoul((const char*)p->record.csv.fields[pos-1], p->record.csv.field_lens[pos-1]);
	return 0;
}

static inline gs_retval_t get_csv_ullong(struct packet * p, gs_uint64_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif
//    *t = strtoull((const char*)p->record.csv.fields[pos-1], NULL, 10);
    *t = gs_strtoull((const char*)p->record.csv.fields[pos-1], p->record.csv.field_lens[pos-1]);
    return 0;
}

static inline gs_retval_t get_csv_ip(struct packet * p, gs_uint32_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif
    // parsed data is not NULL temrinated, we can terminate it to be able to use standard C functions
    // exception is the last field than needs to be copied
    gs_int8_t buffer[256];
    gs_sp_t data=(gs_sp_t)p->record.csv.fields[pos-1];
    gs_uint32_t data_len = p->record.csv.field_lens[pos-1];
    if (pos == p->record.csv.numberfields) {
        memcpy(buffer, data, data_len);
        data = buffer;
    }
    data[data_len] = '\0';

	unsigned ip1,ip2,ip3,ip4;
    sscanf((const char*)data,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4);
	*t=(ip1<<24)|(ip2<<16)|(ip3<<8)|ip4;
    return 0;
}
static inline gs_retval_t get_csv_ipv6(struct packet * p, struct ipv6_str * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif 
    // parsed data is not NULL temrinated, we can terminate it to be able to use standard C functions
    // exception is the last field than needs to be copied before we can terminate it
    gs_int8_t buffer[256];
    gs_sp_t data=(gs_sp_t)p->record.csv.fields[pos-1];
    gs_uint32_t data_len = p->record.csv.field_lens[pos-1];
    if (pos == p->record.csv.numberfields) {
        memcpy(buffer, data, data_len);
        data = buffer;
    }
    data[data_len] = '\0';

    gs_uint32_t v[8];
    sscanf((const char*)data,"%x:%x:%x:%x:%x:%x:%x:%x",&v[0],&v[1],&v[2],&v[3],&v[4],&v[5],&v[6],&v[7]);
	t->v[0]=htonl(v[0]<<16|v[1]);
	t->v[1]=htonl(v[2]<<16|v[3]);
	t->v[2]=htonl(v[4]<<16|v[5]);
	t->v[3]=htonl(v[6]<<16|v[7]);
	
    return 0;
}
static inline gs_retval_t get_csv_string(struct packet * p, struct gs_string * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif 
	t->data=(gs_sp_t)p->record.csv.fields[pos-1];
    t->length=p->record.csv.field_lens[pos-1];
	t->owner=0;
    return 0;
}
static inline gs_retval_t get_csv_bool(struct packet * p, gs_uint32_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif 
	*t=0;
	if ((p->record.csv.field_lens[pos-1]==4) &&
		(strncasecmp("TRUE",(const char*)p->record.csv.fields[pos-1],4) ==0) ) {
		*t=1;
	}
    return 0;
}
static inline gs_retval_t get_csv_int(struct packet * p, gs_int32_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif
    //*t = strtol((const char*)p->record.csv.fields[pos-1], NULL, 10);
    *t = gs_strtol((const char*)p->record.csv.fields[pos-1], p->record.csv.field_lens[pos-1]);
    return 0;
}
static inline gs_retval_t get_csv_llong(struct packet * p, gs_int64_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif
    //*t = strtoll((const char*)p->record.csv.fields[pos-1], NULL, 10);
    *t = gs_strtoll((const char*)p->record.csv.fields[pos-1], p->record.csv.field_lens[pos-1]);    
    return 0;
}
static inline gs_retval_t get_csv_float(struct packet * p, gs_float_t * t,gs_uint32_t pos)
{
#ifdef PARSER_SANITY_CHECKS    
	if (p->ptype != PTYPE_CSV) return -1;
	if (p->record.csv.numberfields < pos) return -1;
#endif
    // parsed data is not NULL temrinated, we can terminate it to be able to use standard C functions
    // exception is the last field than needs to be copied before we can terminate it
    gs_int8_t buffer[256];
    gs_sp_t data=(gs_sp_t)p->record.csv.fields[pos-1];
    gs_uint32_t data_len = p->record.csv.field_lens[pos-1];
    if (pos == p->record.csv.numberfields) {
        memcpy(buffer, data, data_len);
        data = buffer;
    }
    data[data_len] = '\0';

    *t = strtod((const char*)data, NULL);
    return 0;
}

#include <lfta/csv_macro.h>


/* GDAT access function using position as 3rd argument */

//#define GDATDEBUG

static inline gs_retval_t get_gdat_uint(struct packet * p, gs_uint32_t * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
	fprintf(stderr,"Decode uint");
#endif
	if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
	if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
	ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
	if (ar.field_data_type!=UINT_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
	*t=ar.r.ui;
    return 0;
}

static inline gs_retval_t get_gdat_ullong(struct packet * p, gs_uint64_t * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode ullong");
#endif
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=ULLONG_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    *t=ar.r.ul;
    return 0;
}

static inline gs_retval_t get_gdat_ip(struct packet * p, gs_uint32_t * t,gs_uint32_t pos)
{
    struct access_result ar;
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode ip");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=IP_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    *t=ar.r.ui;
    return 0;
}
static inline gs_retval_t get_gdat_ipv6(struct packet * p, struct ipv6_str * t,gs_uint32_t pos)
{
    struct access_result ar;
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode ipv6");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=IPV6_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    t->v[0]=ar.r.ip6.v[0];
    t->v[1]=ar.r.ip6.v[1];
    t->v[2]=ar.r.ip6.v[2];
    t->v[3]=ar.r.ip6.v[3];
    return 0;
}
static inline gs_retval_t get_gdat_string(struct packet * p, struct gs_string * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode string");
#endif
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=VSTR_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    t->data=(gs_sp_t)ar.r.vs.offset;
	t->length=ar.r.vs.length;
    return 0;
}
static inline gs_retval_t get_gdat_bool(struct packet * p, gs_uint32_t * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode bool");
#endif
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=BOOL_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    *t=ar.r.ui;
    return 0;
}
static inline gs_retval_t get_gdat_int(struct packet * p, gs_int32_t * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode int");
#endif
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=INT_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    *t=ar.r.i;
    return 0;
}
static inline gs_retval_t get_gdat_llong(struct packet * p, gs_int64_t * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode llong");
#endif
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=LLONG_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    *t=ar.r.l;
    return 0;
}
static inline gs_retval_t get_gdat_float(struct packet * p, gs_float_t * t,gs_uint32_t pos)
{
    struct access_result ar;
#ifdef GDATDEBUG
    fprintf(stderr,"Decode float");
#endif
    if (p->ptype != PTYPE_GDAT) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (p->record.gdat.numfields<pos) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    ar=ftaschema_get_field_by_index(p->record.gdat.schema,pos-1,p->record.gdat.data,p->record.gdat.datasz);
#ifdef GDATDEBUG
    fprintf(stderr,".");
#endif
    if (ar.field_data_type!=FLOAT_TYPE) return -1;
#ifdef GDATDEBUG
    fprintf(stderr,"DONE\n");
#endif
    *t=ar.r.f;
    return 0;
}

#include <lfta/gdat_macro.h>

// External functions




#endif

