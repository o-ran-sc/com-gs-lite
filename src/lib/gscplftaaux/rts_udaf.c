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

///////////////// FIRST

// uint
void FIRST_lfta_LFTA_AGGR_INIT_(gs_uint32_t* scratch) {
	*scratch = UINT_MAX;	// we will encode uninitialized value of UINT_MAX
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

// int
void FIRST_INT_lfta_LFTA_AGGR_INIT_(gs_int32_t* scratch) {
	*scratch = INT_MAX;	// we will encode uninitialized value of ULLONG_MAX
	return;
}
void FIRST_INT_lfta_LFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val) {
	if (*scratch == INT_MAX)
		*scratch = val;
	return;
}
gs_retval_t FIRST_INT_lfta_LFTA_AGGR_FLUSHME_( gs_int32_t* scratch) { return 0; }
void FIRST_INT_lfta_LFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch) {
	*res = *scratch;
}
void FIRST_INT_lfta_LFTA_AGGR_DESTROY_(gs_int32_t* scratch) { return; }

// ullong
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

// llong
void FIRST_LL_lfta_LFTA_AGGR_INIT_(gs_int64_t* scratch) {
	*scratch = LLONG_MAX;		// we will encode uninitialized value of ULLONG_MAX
	return;
}
void FIRST_LL_lfta_LFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val) {
	if (*scratch == LLONG_MAX)
		*scratch = val;
	return;
}
gs_retval_t FIRST_LL_lfta_LFTA_AGGR_FLUSHME_( gs_int64_t* scratch) { return 0; }
void FIRST_LL_lfta_LFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch) {
	*res = *scratch;
}
void FIRST_LL_lfta_LFTA_AGGR_DESTROY_(gs_int64_t* scratch) { return; }

// string
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

///////////////// LAST

// uint
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

// int
void LAST_INT_lfta_LFTA_AGGR_INIT_(gs_int32_t* scratch) { }
void LAST_INT_lfta_LFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val) {
	*scratch = val;
	return;
}
gs_retval_t LAST_INT_lfta_LFTA_AGGR_FLUSHME_( gs_int32_t* scratch) { return 0; }
void LAST_INT_lfta_LFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch) {
	*res = *scratch;
}
void LAST_INT_lfta_LFTA_AGGR_DESTROY_(gs_int32_t* scratch) { return; }

// ullong
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

// llong
void LAST_LL_lfta_LFTA_AGGR_INIT_(gs_int64_t* scratch) { }
void LAST_LL_lfta_LFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val) {
	*scratch = val;
	return;
}
gs_retval_t LAST_LL_lfta_LFTA_AGGR_FLUSHME_( gs_int64_t* scratch) { return 0; }
void LAST_LL_lfta_LFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch) {
	*res = *scratch;
}
void LAST_LL_lfta_LFTA_AGGR_DESTROY_(gs_int64_t* scratch) { return; }

// string
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

////////////////////////////////////////////////////////
//	count_diff aggregate
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

//	unsigned int
void count_diff_lfta_ui_LFTA_AGGR_INIT_(gs_sp_t s) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	scratch->count = 0;
	scratch->first.l = 0;
	scratch->last.l = 0;
}
void count_diff_lfta_ui_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint32_t val) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	if(scratch->count==0){
		scratch->count = 1;
		scratch->first.ui = val;
	}else{
		if(scratch->last.ui != val)
			scratch->count++;
	}
	scratch->last.ui = val;
}
void count_diff_lfta_ui_LFTA_AGGR_OUTPUT_(struct gs_string * res, gs_sp_t scratch) {
	res->data = (gs_sp_t)scratch;
	res->length = sizeof(struct lfta_count_diff_scratch);
	res->owner = NULL;
}
void count_diff_lfta_ui_LFTA_AGGR_DESTROY_(gs_sp_t s) { }

gs_retval_t count_diff_lfta_ui_LFTA_AGGR_FLUSHME_(gs_sp_t s) {
	return 0;
}

//	int
void count_diff_lfta_i_LFTA_AGGR_INIT_(gs_sp_t s) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	scratch->count = 0;
	scratch->first.l = 0;
	scratch->last.l = 0;
}
void count_diff_lfta_i_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_int32_t val) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	if(scratch->count==0){
		scratch->count = 1;
		scratch->first.i = val;
	}else{
		if(scratch->last.i != val)
			scratch->count++;
	}
	scratch->last.i = val;
}
void count_diff_lfta_i_LFTA_AGGR_OUTPUT_(struct gs_string * res, gs_sp_t scratch) {
	res->data = (gs_sp_t)scratch;
	res->length = sizeof(struct lfta_count_diff_scratch);
	res->owner = NULL;
}
void count_diff_lfta_i_LFTA_AGGR_DESTROY_(gs_sp_t s) { }
gs_retval_t count_diff_lfta_i_LFTA_AGGR_FLUSHME_(gs_sp_t s) {
	return 0;
}

//	unsigned long long int
void count_diff_lfta_ul_LFTA_AGGR_INIT_(gs_sp_t s) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	scratch->count = 0;
	scratch->first.l = 0;
	scratch->last.l = 0;
}
void count_diff_lfta_ul_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint64_t val) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	if(scratch->count==0){
		scratch->count = 1;
		scratch->first.ul = val;
	}else{
		if(scratch->last.ul != val)
			scratch->count++;
	}
	scratch->last.ul = val;
}
void count_diff_lfta_ul_LFTA_AGGR_OUTPUT_(struct gs_string * res, gs_sp_t scratch) {
	res->data = (gs_sp_t)scratch;
	res->length = sizeof(struct lfta_count_diff_scratch);
	res->owner = NULL;
}
void count_diff_lfta_ul_LFTA_AGGR_DESTROY_(gs_sp_t s) { }
gs_retval_t count_diff_lfta_ul_LFTA_AGGR_FLUSHME_(gs_sp_t s) {
	return 0;
}

//	long long int
void count_diff_lfta_l_LFTA_AGGR_INIT_(gs_sp_t s) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	scratch->count = 0;
	scratch->first.l = 0;
	scratch->last.l = 0;
}
void count_diff_lfta_l_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_int64_t val) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	if(scratch->count==0){
		scratch->count = 1;
		scratch->first.l = val;
	}else{
		if(scratch->last.l != val)
			scratch->count++;
	}
	scratch->last.l = val;
}
void count_diff_lfta_l_LFTA_AGGR_OUTPUT_(struct gs_string* res, gs_sp_t scratch) {
	res->data = (gs_sp_t)scratch;
	res->length = sizeof(struct lfta_count_diff_scratch);
	res->owner = NULL;
}
void count_diff_lfta_l_LFTA_AGGR_DESTROY_(gs_sp_t s) { }
gs_retval_t count_diff_lfta_l_LFTA_AGGR_FLUSHME_(gs_sp_t s) {
	return 0;
}

//	string

static gs_uint64_t local_hash_string(struct gs_string *x){
	gs_uint32_t i;
	gs_uint64_t ret=0,tmp_sum = 0;
	for(i=0;i<x->length;++i){
		tmp_sum |= (x->data[i]) << (8*(i%4));
		if((i%4) == 3){
			ret = tmp_sum + 12916008961267169387ull * ret;
			tmp_sum = 0;
		}
	}
	if((i%4)!=0) ret = tmp_sum + 12916008961267169387ull * ret;
	return(ret);
}


void count_diff_lfta_s_LFTA_AGGR_INIT_(gs_sp_t s) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	scratch->count = 0;
	scratch->first.ul = 0;
	scratch->last.ul = 0;
}
void count_diff_lfta_s_LFTA_AGGR_UPDATE_(gs_sp_t s, struct gs_string* val) {
	struct lfta_count_diff_scratch* scratch = (struct lfta_count_diff_scratch*)s;
	gs_uint64_t hashval;
	hashval = local_hash_string(val);
	if(scratch->count==0){
		scratch->count = 1;
		scratch->first.ul = hashval;
	}else{
		if(scratch->last.ul != hashval)
			scratch->count++;
	}
	scratch->last.ul = hashval;
}
void count_diff_lfta_s_LFTA_AGGR_OUTPUT_(struct gs_string* res, gs_sp_t scratch) {
	res->data = (gs_sp_t)scratch;
	res->length = sizeof(struct lfta_count_diff_scratch);
	res->owner = NULL;
}
void count_diff_lfta_s_LFTA_AGGR_DESTROY_(gs_sp_t s) { }
gs_retval_t count_diff_lfta_s_LFTA_AGGR_FLUSHME_(gs_sp_t s) {
	return 0;
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



/////////////////////////////////////////////////////////
// ==============================================================
//		other rts functions.

// sum_int_in_list
// given e.g. '34|45|56' and sepchar '|', return 135.
// gracefully handle empty entries, e.g. '|8|' should return 8
gs_int64_t sum_uint_in_list(struct gs_string *list, struct gs_string *sepchar){
	gs_int64_t ret = 0;
	gs_int64_t val = 0;
	gs_uint8_t sep;
	gs_uint8_t v;
	int c;

	if(sepchar->length < 1)
		return 0;
	sep = sepchar->data[0];

	for(c=0;c<list->length;++c){
		v = list->data[c];
		if(v==sep){
			ret+=val;
			val = 0;
		}else{
			val = 10*val + (v>='0' && v<='9')*(v-'0');
		}
	}
	ret += val;
	return ret;
}

//	Convert an string to an integer
gs_int64_t to_llong(struct gs_string *v){
	gs_int64_t ret=0;
	gs_uint8_t d;
	int c;
	int neg=1;

	if(v->length < 1)
		return 0;
	d = v->data[0];
	if(d=='-'){
		neg=-1;
	}else{
		ret = (d>='0' && d<='9')*(d-'0');
	}

	for(c=1;c<v->length;++c){
		d = v->data[c];
		ret = 10*ret+(d>='0' && d<='9')*(d-'0');
	}

	return neg*ret;
}

	

