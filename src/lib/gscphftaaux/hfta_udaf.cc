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


#include "gsconfig.h"
#include "gstypes.h"
#include "hfta_udaf.h"
#include "rts_udaf.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>
//#include <memory.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>

#include "hfta_runtime_library.h"


#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define lg(x)    (log(x) / log(2))

using namespace std;


// -------------------------------------------------------------------
//              moving sum over N intervals

struct moving_sum_udaf_str{
	gs_uint32_t N;
	gs_uint32_t pos;
	gs_uint32_t *sums;
};

void moving_sum_udaf_HFTA_AGGR_INIT_(gs_sp_t buf){
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) buf;
  u->N=0; u->pos=0; u->sums=NULL;
}

void moving_sum_udaf_HFTA_AGGR_UPDATE_(gs_sp_t buf, gs_uint32_t s, gs_uint32_t N) {
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) buf;
  if(u->sums == NULL){
	u->sums = (gs_uint32_t *)malloc(N*sizeof(gs_uint32_t));
	for(gs_int32_t i=0;i<N;i++)
		u->sums[i] = 0;
    u->N = N;
  }
  u->sums[u->pos] += s;
}

void super_moving_sum_udaf_HFTA_AGGR_UPDATE_(gs_sp_t  buf, gs_uint64_t sub_sum) {
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) buf;
  gs_uint32_t s = (gs_uint32_t)(sub_sum & 0xffffffff);
  if(u->sums == NULL){
    gs_uint32_t N = (gs_uint32_t)((sub_sum & 0xffffffff00000000ull) >> 32);
	u->sums = (gs_uint32_t *)malloc(N*sizeof(gs_uint32_t));
	for(gs_int32_t i=0;i<N;i++)
		u->sums[i] = 0;
    u->N = N;
  }
  u->sums[u->pos] += s;
}

void moving_sum_udaf_HFTA_AGGR_OUTPUT_(gs_p_t *result, gs_sp_t  buf){
	*result = (gs_p_t)(buf);
}

void moving_sum_udaf_HFTA_AGGR_DESTROY_(gs_sp_t  buf){
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) buf;
  if(u->sums != NULL)
	free(u->sums);
}

void moving_sum_udaf_HFTA_AGGR_REINIT_( gs_sp_t  buf){
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) buf;
  u->pos++;
  if(u->pos >= u->N)
	u->pos = 0;
  u->sums[u->pos] = 0;
}

gs_uint32_t moving_sum_extract(gs_p_t result){
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) result;
  gs_uint32_t s=0, i=0;
  for(i=0; i<u->N;i++){
    s += u->sums[i];
  }
  return s;
}

gs_float_t moving_sum_extract_exp(gs_p_t result, gs_float_t alpha){
  struct moving_sum_udaf_str * u = (struct moving_sum_udaf_str *) result;
  gs_uint32_t p=0, i=0;
  gs_float_t s=0.0, m=1.0;
  p=u->pos;
  for(i=0; i<u->N;i++){
    s += u->sums[i]*m;
    if(p==0)
		p=u->N - 1;
    else
		p--;
	m *= alpha;
  }
  return s;
}


// -------------------------------------------------------------------
//              sum over 3 intervals : test rUDAF

struct sum3_udaf_str{
  gs_uint32_t s_2;
  gs_uint32_t s_1;
  gs_uint32_t s_0;
};

void sum3_HFTA_AGGR_INIT_(gs_sp_t  buf) {
  struct sum3_udaf_str * u = (struct sum3_udaf_str *) buf;
  u->s_0 = 0; u->s_1 = 0; u->s_2 = 0;
  return;
}          

void sum3_HFTA_AGGR_UPDATE_(gs_sp_t  buf, gs_uint32_t s) {
  struct sum3_udaf_str * u = (struct sum3_udaf_str *) buf;
  u->s_0 += s;
  return;
}

void sum3_HFTA_AGGR_OUTPUT_(gs_uint32_t *result, gs_sp_t  buf) {
  struct sum3_udaf_str * u = (struct sum3_udaf_str *) buf;
  *result = u->s_0 + u->s_1 + u->s_2;
  return; 
}

void sum3_HFTA_AGGR_DESTROY_(gs_sp_t  buf) {
  return;
}

void sum3_HFTA_AGGR_REINIT_( gs_sp_t  buf) {
  struct sum3_udaf_str * u = (struct sum3_udaf_str *) buf;
  u->s_2 = u->s_1;
  u->s_1 = u->s_0;
  u->s_0 = 0;
  return;
}


#define HISTORY_LENGTH 1024

/////////////////////////////////////////////////////////////////////////
/////   Calculate the average of all positive gs_float_t numbers

struct posavg_struct{
  gs_float_t sum;
  gs_float_t cnt;
};

void POSAVG_HFTA_AGGR_INIT_(gs_sp_t  buf) {
  struct posavg_struct * a = (struct posavg_struct *) buf;
  a->sum=0;
  a->cnt=0;
  return;
}

void POSAVG_HFTA_AGGR_UPDATE_(gs_sp_t  buf, gs_float_t v) {
  struct posavg_struct * a = (struct posavg_struct *) buf;
  if (v>=0) {
    a->sum=a->sum+v;
    a->cnt=a->cnt+1;
  }
  return;
}

void POSAVG_HFTA_AGGR_OUTPUT_(gs_float_t * v, gs_sp_t  buf) {
  struct posavg_struct * a = (struct posavg_struct *) buf;
  if (a->cnt>0) {
    *v=(a->sum/a->cnt);
  } else {
    *v=-1;
  }
  return;
}

void POSAVG_HFTA_AGGR_DESTROY_(gs_sp_t  buf) {
  return;
}

/////////////////////////////////////////////////////////////////////////
/////                   avg_udaf (simple example)

//              struct received from subaggregate
struct avg_udaf_lfta_struct_t{
        gs_int64_t  sum;
        gs_uint32_t cnt;
};

//              sctarchpad struct
struct avg_udaf_hfta_struct_t{
        gs_int64_t sum;
        gs_uint32_t cnt;
};

//                      avg_udaf functions
void avg_udaf_HFTA_AGGR_INIT_(gs_sp_t b){
        avg_udaf_hfta_struct_t *s = (avg_udaf_hfta_struct_t *) b;
        s->sum = 0;
        s->cnt = 0;
}

void avg_udaf_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v){
        avg_udaf_hfta_struct_t *s = (avg_udaf_hfta_struct_t *) b;
        s->sum += v;
        s->cnt ++;
}

void avg_udaf_HFTA_AGGR_OUTPUT_(vstring *r,gs_sp_t b){
        r->length = 12;
        r->offset = (gs_p_t)(b);
        r->reserved = SHALLOW_COPY;
}

void avg_udaf_HFTA_AGGR_DESTROY_(gs_sp_t b){
        return;
}


//                      avg_udaf superaggregate functions
void avg_udaf_hfta_HFTA_AGGR_INIT_(gs_sp_t b){
        avg_udaf_hfta_struct_t *s = (avg_udaf_hfta_struct_t *) b;
        s->sum = 0;
        s->cnt = 0;
}

void avg_udaf_hfta_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v){
        if(v->length != 12) return;
        avg_udaf_hfta_struct_t *s = (avg_udaf_hfta_struct_t *) b;
        avg_udaf_lfta_struct_t *vs = (avg_udaf_lfta_struct_t *)(v->offset);
        s->sum += vs->sum;
        s->cnt += vs->cnt;
}

void avg_udaf_hfta_HFTA_AGGR_OUTPUT_(vstring *r,gs_sp_t b){
        r->length = 12;
        r->offset = (gs_p_t)(b);
        r->reserved = SHALLOW_COPY;
}

void avg_udaf_hfta_HFTA_AGGR_DESTROY_(gs_sp_t b){
        return;
}

//              Extraction function
gs_float_t extr_avg_fcn(vstring *v){
        if(v->length != 12) return 0;
        avg_udaf_hfta_struct_t *vs = (avg_udaf_hfta_struct_t *)(v->offset);
        gs_float_t r = (gs_float_t)(vs->sum) / vs->cnt;
    return r;
}

/////////////////////////////////////////////////////////
//		FIRST aggregate
// hfta only

void FIRST_HFTA_AGGR_INIT_(gs_uint32_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}
void FIRST_HFTA_AGGR_REINIT_(gs_uint32_t* scratch) { }
void FIRST_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}
void FIRST_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}
void FIRST_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { }

void FIRST_HFTA_AGGR_INIT_(gs_uint64_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}
void FIRST_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }
void FIRST_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}
void FIRST_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}
void FIRST_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }



void FIRST_ULL_HFTA_AGGR_INIT_(gs_uint64_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}

void FIRST_ULL_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }

void FIRST_ULL_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}

void FIRST_ULL_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}

void FIRST_ULL_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }


void FIRST_STR_HFTA_AGGR_INIT_(vstring* scratch) {
	scratch->offset= 0;
}

void FIRST_STR_HFTA_AGGR_REINIT_(vstring* scratch) { }

void FIRST_STR_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
	if (!scratch->offset) {
    scratch->length = val->length;
    scratch->offset = val->offset;
    scratch->reserved = SHALLOW_COPY;
	}
}

void FIRST_STR_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
}

void FIRST_STR_HFTA_AGGR_DESTROY_(vstring* scratch) { }

// hfta/lfta split

void FIRST_hfta_HFTA_AGGR_INIT_(gs_uint32_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}

void FIRST_hfta_HFTA_AGGR_REINIT_(gs_uint32_t* scratch) { }

void FIRST_hfta_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}

void FIRST_hfta_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}

void FIRST_hfta_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { }

void FIRST_ULL_hfta_HFTA_AGGR_INIT_(gs_uint64_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}

void FIRST_ULL_hfta_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }

void FIRST_ULL_hfta_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}

void FIRST_ULL_hfta_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}

void FIRST_ULL_hfta_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }


void FIRST_STR_hfta_HFTA_AGGR_INIT_(vstring* scratch) {
	scratch->offset= 0;
}

void FIRST_STR_hfta_HFTA_AGGR_REINIT_(vstring* scratch) { }

void FIRST_STR_hfta_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
	if (!scratch->offset) {
    scratch->length = val->length;
    scratch->offset = val->offset;
    scratch->reserved = SHALLOW_COPY;
	}
}

void FIRST_STR_hfta_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
}

void FIRST_STR_hfta_HFTA_AGGR_DESTROY_(vstring* scratch) { }


/////////////////////////////////////////////////////////
//		LAST aggregate

// hfta only

void LAST_HFTA_AGGR_INIT_(gs_uint32_t* scratch) { }
void LAST_HFTA_AGGR_REINIT_(gs_uint32_t* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	*scratch = val;
}
void LAST_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { }


void LAST_HFTA_AGGR_INIT_(gs_uint64_t* scratch) { }
void LAST_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	*scratch = val;
}
void LAST_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }



void LAST_ULLHFTA_AGGR_INIT_(gs_uint64_t* scratch) { }

void LAST_ULL_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }

void LAST_ULL_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	*scratch = val;
}

void LAST_ULL_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}

void LAST_ULL_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }


void LAST_STR_HFTA_AGGR_INIT_(vstring* scratch) {
	scratch->offset= 0;
}

void LAST_STR_HFTA_AGGR_REINIT_(vstring* scratch) { }

void LAST_STR_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
	scratch->length = val->length;
  scratch->offset = val->offset;
  scratch->reserved = SHALLOW_COPY;
}

void LAST_STR_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
}

void LAST_STR_HFTA_AGGR_DESTROY_(vstring* scratch) { }

// hfta/lfta split

void LAST_hfta_HFTA_AGGR_INIT_(gs_uint32_t* scratch) { }

void LAST_hfta_HFTA_AGGR_REINIT_(gs_uint32_t* scratch) { }

void LAST_hfta_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	*scratch = val;
}

void LAST_hfta_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}

void LAST_hfta_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { }

void LAST_ULL_hfta_HFTA_AGGR_INIT_(gs_uint64_t* scratch) { }

void LAST_ULL_hfta_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }

void LAST_ULL_hfta_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	*scratch = val;
}

void LAST_ULL_hfta_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}

void LAST_ULL_hfta_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }


void LAST_STR_hfta_HFTA_AGGR_INIT_(vstring* scratch) {
	scratch->offset= 0;
}

void LAST_STR_hfta_HFTA_AGGR_REINIT_(vstring* scratch) { }

void LAST_STR_hfta_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
	scratch->length = val->length;
  scratch->offset = val->offset;
  scratch->reserved = SHALLOW_COPY;
}

void LAST_STR_hfta_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
}

void LAST_STR_hfta_HFTA_AGGR_DESTROY_(vstring* scratch) { }


/////////////////////////////////////////////////////////
//		running_array_aggr aggregate

void running_array_aggr_hfta_HFTA_AGGR_INIT_(vstring* scratch) {
  scratch->offset = NULL;  
  scratch->length = 0;
}

void running_array_aggr_hfta_HFTA_AGGR_REINIT_(vstring* scratch) { }

void running_array_aggr_hfta_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
  char buffer[100];

  gs_uint32_t* ints = (gs_uint32_t*)val->offset;
  switch (val->length / sizeof (gs_uint32_t)) {
    case 4:
      sprintf(buffer, "%u,%u,%u,%u", ints[0], ints[1], ints[2], ints[3]);
      break;
    case 3:
      sprintf(buffer, "%u,%u,%u", ints[0], ints[1], ints[2]);
      break;   
    case 2:
      sprintf(buffer, "%u,%u", ints[0], ints[1]);
      break;        
    case 1:
      sprintf(buffer, "%u", ints[0]);
      break;  
    case 0:
      return;        
  }
  int buf_len = strlen(buffer);

  // append the content of buffer to scratch
	if (!scratch->offset) {
    Vstring_Constructor(scratch, buffer);
	} else {
    scratch->offset = (gs_p_t)realloc((void*)scratch->offset, scratch->length + buf_len + 1);
    *((char*)scratch->offset + scratch->length) = ',';
    memcpy((void*)(scratch->offset + scratch->length + 1), (void*)buffer, buf_len);
    scratch->length += buf_len + 1;
    scratch->reserved = INTERNAL;
  }
}

void running_array_aggr_hfta_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
  res->reserved = SHALLOW_COPY;
}

void running_array_aggr_hfta_HFTA_AGGR_DESTROY_(vstring* scratch) {
  hfta_vstr_destroy(scratch);
 }

