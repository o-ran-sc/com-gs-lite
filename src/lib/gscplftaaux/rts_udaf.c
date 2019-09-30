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

#include "rts_udaf.h"
#include "gsconfig.h"
#include "gstypes.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>


#define max(a,b) ((a) > (b) ? (a) : (b))
#define MAX_BUFSIZE     128


/****************************************************************/
/* LFTA functions                                               */
/****************************************************************/


////////////////////////////////////////////////////////////////////////
////		avg_udaf

typedef struct avg_udaf_lfta_struct_t{
	gs_int64_t sum;
	gs_uint32_t cnt;
} avg_udaf_lfta_struct_t;

void avg_udaf_lfta_LFTA_AGGR_INIT_(gs_sp_t b){
	avg_udaf_lfta_struct_t *s = (avg_udaf_lfta_struct_t *)b;
	s->sum = 0;
	s->cnt = 0;
}

void avg_udaf_lfta_LFTA_AGGR_UPDATE_(gs_sp_t  b,gs_uint32_t v){
	avg_udaf_lfta_struct_t *s = (avg_udaf_lfta_struct_t *)b;
	s->sum += v;
	s->cnt++;
}

gs_retval_t avg_udaf_lfta_LFTA_AGGR_FLUSHME_(gs_sp_t b){
	return 0;
}

void avg_udaf_lfta_LFTA_AGGR_OUTPUT_(struct gs_string *r,gs_sp_t b){
	r->length = 12;
	r->data = b;
}

void avg_udaf_lfta_LFTA_AGGR_DESTROY_(gs_sp_t b){
	return;
}

/////////////////////////////////////////////////////////
//		Moving sum

typedef struct moving_sum_lfta_struct{
	gs_uint32_t sum;
	gs_uint32_t N;
} moving_sum_lfta_struct;

void moving_sum_lfta_LFTA_AGGR_INIT_(gs_sp_t b){
	moving_sum_lfta_struct *s = (moving_sum_lfta_struct *)b;
	s->sum = 0;
	s->N = 0;
}

void moving_sum_lfta_LFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v, gs_uint32_t N){
	moving_sum_lfta_struct *s = (moving_sum_lfta_struct *)b;
	s->sum += v;
	s->N = N;
}
	
gs_retval_t moving_sum_lfta_LFTA_AGGR_FLUSHME_(gs_sp_t b){
	return 0;
}

void moving_sum_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t *r, gs_sp_t b){
	moving_sum_lfta_struct *s = (moving_sum_lfta_struct *)b;
	*r = ((gs_uint64_t)(s->N) << 32) | (gs_uint64_t)(s->sum);
}

gs_retval_t moving_sum_lfta_LFTA_AGGR_DESTROY_(gs_sp_t b){
	return 0;
}

/////////////////////////////////////////////////////////
//		FIRST and LAST aggregates

void FIRST_lfta_LFTA_AGGR_INIT_(gs_uint32_t* scratch) {
	*scratch = UINT_MAX;		// we will encode uninitialized value of UINT_MAX
	return;
}

void FIRST_lfta_LFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	if (*scratch == UINT_MAX)
		*scratch = val;
	return;
}

gs_retval_t FIRST_lfta_LFTA_AGGR_FLUSHME_( gs_uint32_t* scratch) { return 0; }

void FIRST_lfta_LFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}

void FIRST_lfta_LFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { return; }

void FIRST_ULL_lfta_LFTA_AGGR_INIT_(gs_uint64_t* scratch) {
	*scratch = ULLONG_MAX;		// we will encode uninitialized value of ULLONG_MAX
	return;
}

void FIRST_ULL_lfta_LFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	if (*scratch == ULLONG_MAX)
		*scratch = val;
	return;
}

gs_retval_t FIRST_ULL_lfta_LFTA_AGGR_FLUSHME_( gs_uint64_t* scratch) { return 0; }

void FIRST_ULL_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}

void FIRST_ULL_lfta_LFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { return; }



void FIRST_STR_lfta_LFTA_AGGR_INIT_(struct gs_string* scratch) {
	scratch->data = NULL;
	return;
}

void FIRST_STR_lfta_LFTA_AGGR_UPDATE_(struct gs_string* scratch, struct gs_string* val) {
	if (!scratch->data) {
		str_assign_with_copy(NULL, scratch, val);
	}
	return;
}

gs_retval_t FIRST_STR_lfta_LFTA_AGGR_FLUSHME_(struct gs_string* scratch) { return 0; }

void FIRST_STR_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, struct gs_string* scratch) {
	*res = *scratch;
}

void FIRST_STR_lfta_LFTA_AGGR_DESTROY_(struct gs_string* scratch) { 
	if (scratch->data) 
		fta_free(NULL, scratch->data);
}

void LAST_lfta_LFTA_AGGR_INIT_(gs_uint32_t* scratch) { }

void LAST_lfta_LFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val) {
	*scratch = val;
	return;
}

gs_retval_t LAST_lfta_LFTA_AGGR_FLUSHME_( gs_uint32_t* scratch) { return 0; }

void LAST_lfta_LFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch) {
	*res = *scratch;
}

void LAST_lfta_LFTA_AGGR_DESTROY_(gs_uint32_t* scratch) { return; }

void LAST_ULL_lfta_LFTA_AGGR_INIT_(gs_uint64_t* scratch) { }

void LAST_ULL_lfta_LFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val) {
	*scratch = val;
	return;
}

gs_retval_t LAST_ULL_lfta_LFTA_AGGR_FLUSHME_( gs_uint64_t* scratch) { return 0; }

void LAST_ULL_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch) {
	*res = *scratch;
}

void LAST_ULL_lfta_LFTA_AGGR_DESTROY_(gs_uint64_t* scratch) { return; }



void LAST_STR_lfta_LFTA_AGGR_INIT_(struct gs_string* scratch) {
	scratch->data = NULL;
	return;
}

void LAST_STR_lfta_LFTA_AGGR_UPDATE_(struct gs_string* scratch, struct gs_string* val) {
	if (!scratch->data) {
		str_assign_with_copy(NULL, scratch, val);
	} else {
		if (!str_compare(scratch, val)) {
			fta_free(NULL, scratch->data);
			str_assign_with_copy(NULL, scratch, val);
		}
	}
	return;
}

gs_retval_t LAST_STR_lfta_LFTA_AGGR_FLUSHME_(struct gs_string* scratch) { return 0; }

void LAST_STR_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, struct gs_string* scratch) {
	*res = *scratch;
}

void LAST_STR_lfta_LFTA_AGGR_DESTROY_(struct gs_string* scratch) { 
	if (scratch->data) 
		fta_free(NULL, scratch->data);
}


/////////////////////////////////////////////////////////
//		running_array_aggr aggregate

struct running_array_aggr_str{
	gs_uint32_t num_list[4];
	gs_uint8_t n_num;
};

void running_array_aggr_lfta_LFTA_AGGR_INIT_(char* scratch) {
	struct running_array_aggr_str* aggr = (struct running_array_aggr_str*)scratch;
	aggr->n_num = 0;
}

void running_array_aggr_lfta_LFTA_AGGR_UPDATE_(char* scratch, gs_uint32_t val) {
	struct running_array_aggr_str* aggr = (struct running_array_aggr_str*)scratch;
	aggr->num_list[aggr->n_num++] = val;
}

gs_retval_t running_array_aggr_lfta_LFTA_AGGR_FLUSHME_(char* scratch) {
	struct running_array_aggr_str* aggr = (struct running_array_aggr_str*)scratch;
	return (aggr->n_num == 4);
}
void running_array_aggr_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, char* scratch) {
	struct running_array_aggr_str* aggr = (struct running_array_aggr_str*)scratch;	
	res->data = scratch;
	res->length = aggr->n_num * sizeof(gs_uint32_t);
	res->owner = NULL;
}

void running_array_aggr_lfta_LFTA_AGGR_DESTROY_(char* scratch) { }

