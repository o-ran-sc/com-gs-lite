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
#include"stringhash.h"


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

//              scratchpad struct
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

// uint
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

// int

void FIRST_HFTA_AGGR_INIT_(gs_int32_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}
void FIRST_HFTA_AGGR_REINIT_(gs_int32_t* scratch) { }
void FIRST_HFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}
void FIRST_HFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch) {
	*res = *scratch;
}
void FIRST_HFTA_AGGR_DESTROY_(gs_int32_t* scratch) { }

// ullong
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

// llong
void FIRST_HFTA_AGGR_INIT_(gs_int64_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}
void FIRST_HFTA_AGGR_REINIT_(gs_int64_t* scratch) { }
void FIRST_HFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}
void FIRST_HFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch) {
	*res = *scratch;
}
void FIRST_HFTA_AGGR_DESTROY_(gs_int64_t* scratch) { }

// string
void FIRST_HFTA_AGGR_INIT_(vstring* scratch) {
	scratch->offset= 0;
}
void FIRST_HFTA_AGGR_REINIT_(vstring* scratch) { }
void FIRST_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
	if (!scratch->offset) {
    scratch->length = val->length;
    scratch->offset = val->offset;
    scratch->reserved = SHALLOW_COPY;
	}
}
void FIRST_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
}
void FIRST_HFTA_AGGR_DESTROY_(vstring* scratch) { }

// hfta/lfta split

// uint
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

// int
void FIRST_INT_hfta_HFTA_AGGR_INIT_(gs_int32_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}
void FIRST_INT_hfta_HFTA_AGGR_REINIT_(gs_int32_t* scratch) { }
void FIRST_INT_hfta_HFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}
void FIRST_INT_hfta_HFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch) {
	*res = *scratch;
}
void FIRST_INT_hfta_HFTA_AGGR_DESTROY_(gs_int32_t* scratch) { }

// ullong
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

// llong
void FIRST_LL_hfta_HFTA_AGGR_INIT_(gs_int64_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
}
void FIRST_LL_hfta_HFTA_AGGR_REINIT_(gs_int64_t* scratch) { }
void FIRST_LL_hfta_HFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
}
void FIRST_LL_hfta_HFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch) {
	*res = *scratch;
}
void FIRST_LL_hfta_HFTA_AGGR_DESTROY_(gs_int64_t* scratch) { }

// string
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

// uint
void LAST_HFTA_AGGR_INIT_(gs_uint32_t* scratch) { }
void LAST_HFTA_AGGR_REINIT_(gs_uint32_t* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	*scratch = val;
}
void LAST_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { }

// int
void LAST_HFTA_AGGR_INIT_(gs_int32_t* scratch) { }
void LAST_HFTA_AGGR_REINIT_(gs_int32_t* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val) {
	*scratch = val;
}
void LAST_HFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(gs_int32_t* scratch) { }

// llong
void LAST_HFTA_AGGR_INIT_(gs_int64_t* scratch) { }
void LAST_HFTA_AGGR_REINIT_(gs_int64_t* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val) {
	*scratch = val;
}
void LAST_HFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(gs_int64_t* scratch) { }


// ullong
void LAST_HFTA_AGGR_INIT_(gs_uint64_t* scratch) { }
void LAST_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	*scratch = val;
}
void LAST_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }

// string
void LAST_HFTA_AGGR_INIT_(vstring* scratch) {
	scratch->offset= 0;
}
void LAST_HFTA_AGGR_REINIT_(vstring* scratch) { }
void LAST_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val) {
	scratch->length = val->length;
  scratch->offset = val->offset;
  scratch->reserved = SHALLOW_COPY;
}
void LAST_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch) {
	*res = *scratch;
}
void LAST_HFTA_AGGR_DESTROY_(vstring* scratch) { }

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

void LAST_INT_hfta_HFTA_AGGR_INIT_(gs_int32_t* scratch) { }
void LAST_INT_hfta_HFTA_AGGR_REINIT_(gs_int32_t* scratch) { }
void LAST_INT_hfta_HFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val) {
	*scratch = val;
}
void LAST_INT_hfta_HFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch) {
	*res = *scratch;
}
void LAST_INT_hfta_HFTA_AGGR_DESTROY_(gs_int32_t* scratch) { }

void LAST_ULL_hfta_HFTA_AGGR_INIT_(gs_uint64_t* scratch) { }
void LAST_ULL_hfta_HFTA_AGGR_REINIT_(gs_uint64_t* scratch) { }
void LAST_ULL_hfta_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	*scratch = val;
}
void LAST_ULL_hfta_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}
void LAST_ULL_hfta_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { }

void LAST_LL_hfta_HFTA_AGGR_INIT_(gs_int64_t* scratch) { }
void LAST_LL_hfta_HFTA_AGGR_REINIT_(gs_int64_t* scratch) { }
void LAST_LL_hfta_HFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val) {
	*scratch = val;
}
void LAST_LL_hfta_HFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch) {
	*res = *scratch;
}
void LAST_LL_hfta_HFTA_AGGR_DESTROY_(gs_int64_t* scratch) { }


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


////////////////////////////////////////////////////////////
//		count different (# of times the value is different than the previous)

struct count_diff_scratch{
	gs_uint32_t count;
	union{
		gs_uint32_t ui;
		gs_int32_t i;
		gs_uint64_t ul;
		gs_int64_t l;
	} r;
};

//////////  HFTA only

// uint32
void count_diff_HFTA_AGGR_INIT_(gs_sp_t s){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	scratch->count = 0;
	scratch->r.ul = 0;
}
void count_diff_HFTA_AGGR_REINIT_(gs_sp_t s){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	scratch->count = 0;
}
void count_diff_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint32_t val){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	if(scratch->count==0 || scratch->r.ui != val)
		scratch->count++;
	scratch->r.ui = val;
}
void count_diff_HFTA_AGGR_OUTPUT_(gs_uint32_t *res, gs_sp_t s){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	*res = scratch->count;
}
void count_diff_HFTA_AGGR_DESTROY_(gs_sp_t s){ }

// int32
void count_diff_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_int32_t val){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	if(scratch->count==0 || scratch->r.i != val)
		scratch->count++;
	scratch->r.i = val;
}

// uint64
void count_diff_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint64_t val){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	if(scratch->count==0 || scratch->r.ul != val)
		scratch->count++;
	scratch->r.ul = val;
}

// int64
void count_diff_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_int64_t val){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	if(scratch->count==0 || scratch->r.l != val)
		scratch->count++;
	scratch->r.l = val;
}

// vstring
void count_diff_HFTA_AGGR_UPDATE_(gs_sp_t s, vstring* val){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	gs_uint64_t hashval = hfta_vstr_long_hashfunc(val);
	if(scratch->count==0 || scratch->r.l != hashval)
		scratch->count++;
	scratch->r.l = hashval;
}

////////// HFTA / LFTA split

struct lfta_count_diff_scratch{
	gs_uint32_t count;
	union{
		gs_uint32_t ui;
		gs_int32_t i;
		gs_uint64_t ul;
		gs_int64_t l;
	} first;
	union{
		gs_uint32_t ui;
		gs_int32_t i;
		gs_uint64_t ul;
		gs_int64_t l;
	} last;
};


void count_diff_hfta_HFTA_AGGR_INIT_(gs_sp_t s){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	scratch->count = 0;
	scratch->r.ul = 0;
}
void count_diff_hfta_HFTA_AGGR_REINIT_(gs_sp_t s){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	scratch->count = 0;
	scratch->r.ul = 0;
}
void count_diff_hfta_HFTA_AGGR_UPDATE_(gs_sp_t s, vstring *v){
	lfta_count_diff_scratch *val = (lfta_count_diff_scratch *)v;
	count_diff_scratch *scratch = (count_diff_scratch *)(v->offset);
	scratch->count += val->count - 1;
	if(scratch->r.l != val->first.l)
		scratch->count++;
	scratch->r.l = val->last.l;
}
void count_diff_hfta_HFTA_AGGR_OUTPUT_(gs_uint32_t *res, gs_sp_t s){
	count_diff_scratch *scratch = (count_diff_scratch *)s;
	*res = (scratch->count)+1;
}
void count_diff_hfta_HFTA_AGGR_DESTROY_(gs_sp_t scratch){ }
	


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


////////////////////////////////////////////
//		Aggregate strings by catenation
	

struct CAT_aggr_scratch{
	std::string val;
	int x;
};

struct CAT_aggr_scratch_ptr{
	CAT_aggr_scratch *ptr;
};

void CAT_aggr_HFTA_AGGR_INIT_(gs_sp_t s){
	CAT_aggr_scratch_ptr *p = (CAT_aggr_scratch_ptr *)s;
	CAT_aggr_scratch *v = new CAT_aggr_scratch();
	v->x = 101;

	p->ptr = v;
}
void CAT_aggr_HFTA_AGGR_REINIT_(gs_sp_t s){
	CAT_aggr_scratch_ptr *p = (CAT_aggr_scratch_ptr *)s;
	CAT_aggr_scratch *v = p->ptr;
	v->val="";
}
void CAT_aggr_HFTA_AGGR_UPDATE_(gs_sp_t s, vstring *sep, vstring *str){
char buf1[MAXTUPLESZ-20], buf2[MAXTUPLESZ-20];
int i;
for(i=0;i<sep->length;++i) buf1[i] = *(((char *)sep->offset)+i);
buf1[i]='\0';
for(i=0;i<str->length;++i) buf2[i] = *(((char *)str->offset)+i);
buf2[i]='\0';
	CAT_aggr_scratch_ptr *p = (CAT_aggr_scratch_ptr *)s;
	CAT_aggr_scratch *v = p->ptr;
	if(v->val.size()>0)
		v->val.append((char *)(sep->offset), sep->length);
	v->val.append((char *)(str->offset), str->length);
//printf("sep=%s, str=%s, val=%s\n",buf1,buf2,v->val.c_str());
}
void CAT_aggr_HFTA_AGGR_OUTPUT_(vstring *res, gs_sp_t s){
	CAT_aggr_scratch_ptr *p = (CAT_aggr_scratch_ptr *)s;
	CAT_aggr_scratch *v = p->ptr;
//printf("output val=%s\n",v->val.c_str());
	res->offset = (gs_p_t)malloc(v->val.size());
	res->length = v->val.size();
	if(res->length>MAXTUPLESZ-20)
		res->length=MAXTUPLESZ-20;
//	v->val.copy((char *)(res->offset), 0, res->length);
	const char *dat = v->val.c_str();
	memcpy((char *)(res->offset), dat, res->length);
//	for(int i=0;i<res->length;++i)
//		*(((char *)res->offset)+i) = dat[i];
	res->reserved = INTERNAL;
}
void CAT_aggr_HFTA_AGGR_DESTROY_(gs_sp_t s){
	CAT_aggr_scratch_ptr *p = (CAT_aggr_scratch_ptr *)s;
	CAT_aggr_scratch *v = p->ptr;
	delete v;
}

	
	
///////////////////////////////////////////////////////////////
//	time_avg((sample, ts, window_size)
//  Compute time-weighted average sum(sample*duration)/window_size
//  duration is difference between current and next ts.
//  The idea is to compute a sum over a step function.
//  
	
struct time_avg_udaf_str{
	gs_float_t sum;
	gs_float_t last_val;
	gs_uint64_t last_ts;
	gs_uint64_t window;
	gs_uint64_t first_ts;
	gs_uint8_t event_occurred;
};
	
void time_avg_HFTA_AGGR_INIT_(gs_sp_t s){
	time_avg_udaf_str *scratch = (time_avg_udaf_str *)s;
	scratch->sum = 0.0;
	scratch->last_val = 0.0;
	scratch->last_ts = 0;
	scratch->first_ts = 0;
	scratch->event_occurred = 0;
}

void time_avg_HFTA_AGGR_DESTROY_(gs_sp_t s){
}

void time_avg_HFTA_AGGR_REINIT_(gs_sp_t s){
	time_avg_udaf_str *scratch = (time_avg_udaf_str *)s;
	scratch->event_occurred = 0;
	scratch->sum = 0;
//printf("time_avg_reinit: occurred=%d, last_val=%lf, sum=%lf, first_ts=%lld, last_ts=%lld\n",scratch->event_occurred, scratch->last_val, scratch->sum, scratch->first_ts, scratch->last_ts);
}

void time_avg_HFTA_AGGR_OUTPUT_(gs_float_t *result, gs_sp_t s){
	time_avg_udaf_str *scratch = (time_avg_udaf_str *)s;
	if(scratch->event_occurred==0){
		*result =  scratch->last_val;
//printf("\ttime_avg outpt1 sum=%lf, last_val=%lf, result=%lf\n", scratch->sum, scratch->last_val, *result);
		return;
	}
	gs_int64_t end_time = scratch->window * (scratch->last_ts/scratch->window + 1);
	scratch->sum += (end_time - scratch->last_ts) * (gs_float_t)(scratch->last_val); 
	gs_int64_t start_time = end_time - scratch->window;
	if(scratch->first_ts > start_time){
		*result = scratch->sum / (end_time - scratch->first_ts);
//printf("\ttime_avg outpt2 sum=%lf, start_time=%lld, end_time=%lld, first_ts=%lld, last_ts=%lld,result=%lf\n", scratch->sum, start_time, end_time, scratch->first_ts, scratch->last_ts, *result);
	}else{
		*result = scratch->sum / (end_time - start_time);
//printf("\ttime_avg outpt3 sum=%lf, start_time=%lld, end_time=%lld, first_ts=%lld, last_ts=%lld,result=%lf\n", scratch->sum, start_time, end_time, scratch->first_ts, scratch->last_ts, *result);
	}
}

void time_avg_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_float_t val, gs_int64_t ts, gs_int64_t window){
	time_avg_udaf_str *scratch = (time_avg_udaf_str *)s;
	scratch->window = window;
	if(scratch->first_ts==0){
		scratch->first_ts = ts;
	}else{
		if(scratch->event_occurred){

			scratch->sum += (ts - scratch->last_ts) * scratch->last_val;
		}else{
			gs_int64_t start_time = scratch->window * (scratch->last_ts/scratch->window);
			scratch->sum += (ts - start_time) * scratch->last_val;
		}
	}
//printf("time_avg_upd: val=%lf, occurred=%d, last_val=%lf, sum=%lf, ts=%lld, first_ts=%lld, last_ts=%lld\n",val, scratch->event_occurred, scratch->last_val, scratch->sum, ts, scratch->first_ts, scratch->last_ts);
	scratch->last_val = val;
	scratch->last_ts = ts;
	scratch->event_occurred = 1;
}
void time_avg_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint32_t val, gs_int64_t ts, gs_int64_t window){
	time_avg_HFTA_AGGR_UPDATE_(s, (gs_float_t)val, ts, window);
}
void time_avg_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_int32_t val, gs_int64_t ts, gs_int64_t window){
	time_avg_HFTA_AGGR_UPDATE_(s, (gs_float_t)val, ts, window);
}
void time_avg_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint64_t val, gs_int64_t ts, gs_int64_t window){
	time_avg_HFTA_AGGR_UPDATE_(s, (gs_float_t)val, ts, window);
}
void time_avg_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_int64_t val, gs_int64_t ts, gs_int64_t window){
	time_avg_HFTA_AGGR_UPDATE_(s, (gs_float_t)val, ts, window);
}
	

// ------------------------------------------------------------
//		running_sum_max : get the running sum of an int,
//		be able to report this sum and also its max value
//		during the time window

struct run_sum_max_udaf_str{
	gs_int64_t sum;
	gs_int64_t max;
};
void run_sum_max_HFTA_AGGR_INIT_(gs_sp_t s){
	run_sum_max_udaf_str *scratch = (run_sum_max_udaf_str *)s;
	scratch->sum = 0;
	scratch->max = 0;
}
void run_sum_max_HFTA_AGGR_REINIT_(gs_sp_t s){
	run_sum_max_udaf_str *scratch = (run_sum_max_udaf_str *)s;
	scratch->max = scratch->sum;
}
void run_sum_max_HFTA_AGGR_OUTPUT_(vstring *r,gs_sp_t b){
        r->length = sizeof(run_sum_max_udaf_str);
        r->offset = (gs_p_t)(b);
        r->reserved = SHALLOW_COPY;
}
void run_sum_max_HFTA_AGGR_DESTROY_(gs_sp_t b){
        return;
}

void run_sum_max_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint64_t v){
	run_sum_max_udaf_str *scratch = (run_sum_max_udaf_str *)s;
	scratch->sum+=v;
	if(scratch->sum>scratch->max) scratch->max=scratch->sum;
}
void run_sum_max_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_int64_t v){
	run_sum_max_udaf_str *scratch = (run_sum_max_udaf_str *)s;
	scratch->sum+=v;
	if(scratch->sum>scratch->max) scratch->max=scratch->sum;
}
void run_sum_max_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint32_t v){
	run_sum_max_udaf_str *scratch = (run_sum_max_udaf_str *)s;
	scratch->sum+=v;
	if(scratch->sum>scratch->max) scratch->max=scratch->sum;
}
void run_sum_max_HFTA_AGGR_UPDATE_(gs_sp_t s, gs_int32_t v){
	run_sum_max_udaf_str *scratch = (run_sum_max_udaf_str *)s;
	scratch->sum+=v;
	if(scratch->sum>scratch->max) scratch->max=scratch->sum;
}
//	the extraction functions
gs_int64_t extr_running_sum(vstring *v){
	if(v->length != sizeof(run_sum_max_udaf_str)) return 0;
	run_sum_max_udaf_str *vs = (run_sum_max_udaf_str *)(v->offset);
	return vs->sum;
}
gs_int64_t extr_running_sum_max(vstring *v){
	if(v->length != sizeof(run_sum_max_udaf_str)) return 0;
	run_sum_max_udaf_str *vs = (run_sum_max_udaf_str *)(v->offset);
	return vs->max;
}

// ---------------------------------------------
//		Approximate count distinct.
//		Rely on the minhashing approach.
//		Currently HFTA-only
//		Uses a 32-bit hash, tested up to 100,000,000 elements
//		and it gave good results (within 7%)


#define COUNT_DISTINCT_NREPS 250
#define COUNT_DISTINCT_MAX_STRING_LEN 200	// number of 4-byte words

static Hash32bit2univID hids[COUNT_DISTINCT_NREPS];
static int approx_count_distinct_udaf_initialized = 0;
struct approx_count_distinct_udaf_str{
	unsigned int mn[COUNT_DISTINCT_NREPS];
};


void approx_count_distinct_udaf_HFTA_AGGR_INIT_(gs_sp_t buf){
	approx_count_distinct_udaf_str *cd = (approx_count_distinct_udaf_str *)buf;
	for(int i=0;i<COUNT_DISTINCT_NREPS;++i)
		cd->mn[i]=4294967295;
	if(approx_count_distinct_udaf_initialized==0){
		for(int i=0;i<COUNT_DISTINCT_NREPS;++i)
			hids[i] = InitStringHash32bit2univ(COUNT_DISTINCT_MAX_STRING_LEN);
		approx_count_distinct_udaf_initialized=1;
	}
}
void running_approx_count_distinct_udaf_HFTA_AGGR_INIT_(gs_sp_t buf){
	approx_count_distinct_udaf_HFTA_AGGR_INIT_(buf);
}

void approx_count_distinct_udaf_HFTA_AGGR_REINIT_(gs_sp_t buf){ }
void running_approx_count_distinct_udaf_HFTA_AGGR_REINIT_(gs_sp_t buf){}

void approx_count_distinct_udaf_HFTA_AGGR_DESTROY_(gs_sp_t buf){ }
void running_approx_count_distinct_udaf_HFTA_AGGR_DESTROY_(gs_sp_t buf){ }

void approx_count_distinct_udaf_HFTA_AGGR_UPDATE_(gs_sp_t buf, vstring *val){
	approx_count_distinct_udaf_str *cd = (approx_count_distinct_udaf_str *)buf;
	unsigned int buffer[sizeof(unsigned int)*COUNT_DISTINCT_MAX_STRING_LEN];
	buffer[val->length/4] = 0;
	memcpy((char *)buffer, (char *)val->offset, min(val->length, 800));
	unsigned int len4 = val->length/4 + ((val->length&0x03)>0);

	for(int i=0; i<COUNT_DISTINCT_NREPS; ++i){
		unsigned int h = StringHash32bit2univ(buffer, len4, hids[i]);
		if(h < cd->mn[i]) cd->mn[i] = h;
	}
}
void running_approx_count_distinct_udaf_HFTA_AGGR_UPDATE_(gs_sp_t buf, vstring *val){
	approx_count_distinct_udaf_HFTA_AGGR_UPDATE_(buf, val);
}

void approx_count_distinct_udaf_HFTA_AGGR_OUTPUT_(vstring *res, gs_sp_t buf){
	res->offset = (gs_p_t)buf;
	res->length = sizeof(approx_count_distinct_udaf_str);
	res->reserved = SHALLOW_COPY;
}
void running_approx_count_distinct_udaf_HFTA_AGGR_OUTPUT_(vstring *res, gs_sp_t buf){
	approx_count_distinct_udaf_HFTA_AGGR_OUTPUT_(res, buf);
}

gs_float_t extr_approx_count_distinct(vstring *v){
	approx_count_distinct_udaf_str *cd = (approx_count_distinct_udaf_str *)(v->offset);
	gs_float_t avg = 0.0;
	for(int i=0;i<COUNT_DISTINCT_NREPS;++i){
		avg += cd->mn[i];
	}
	avg /= COUNT_DISTINCT_NREPS;
	gs_float_t est = (4294967295.0 / avg) - 1;
	return est;
}


