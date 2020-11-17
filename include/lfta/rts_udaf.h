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
#ifndef _RTS_UDAF_H_INCLUDED_
#define _RTS_UDAF_H_INCLUDED_

#ifdef __cplusplus
extern "C" {
#endif

#include "gsconfig.h"
#include "gstypes.h"
#include "rts_external.h"


//			avg_udaf
void avg_udaf_lfta_LFTA_AGGR_INIT_(gs_sp_t);
void avg_udaf_lfta_LFTA_AGGR_UPDATE_(gs_sp_t,gs_uint32_t);
gs_retval_t avg_udaf_lfta_LFTA_AGBGR_FLUSHME_(gs_sp_t);
void avg_udaf_lfta_LFTA_AGGR_OUTPUT_(struct gs_string *,gs_sp_t);
void avg_udaf_lfta_LFTA_AGGR_DESTROY_(gs_sp_t);

//		moving sum
void moving_sum_lfta_LFTA_AGGR_INIT_(gs_sp_t b);
void moving_sum_lfta_LFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v, gs_uint32_t N);
gs_retval_t moving_sum_lfta_LFTA_AGGR_FLUSHME_(gs_sp_t b);
void moving_sum_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t *r, gs_sp_t b);
gs_retval_t moving_sum_lfta_LFTA_AGGR_DESTROY_(gs_sp_t b);


//      first aggregate
void FIRST_lfta_LFTA_AGGR_INIT_(gs_uint32_t* scratch);
void FIRST_lfta_LFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val);
gs_retval_t FIRST_lfta_LFTA_AGGR_FLUSHME_(gs_uint32_t* scratch);
void FIRST_lfta_LFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch);
void FIRST_lfta_LFTA_AGGR_DESTROY_(gs_uint32_t* scratch);

void FIRST_INT_lfta_LFTA_AGGR_INIT_(gs_int32_t* scratch);
void FIRST_INT_lfta_LFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val);
gs_retval_t FIRST_INT_lfta_LFTA_AGGR_FLUSHME_(gs_int32_t* scratch);
void FIRST_INT_lfta_LFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch);
void FIRST_INT_lfta_LFTA_AGGR_DESTROY_(gs_int32_t* scratch);

void FIRST_ULL_lfta_LFTA_AGGR_INIT_(gs_uint64_t* scratch);
void FIRST_ULL_lfta_LFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
gs_retval_t FIRST_ULL_lfta_LFTA_AGGR_FLUSHME_(gs_uint64_t* scratch);
void FIRST_ULL_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void FIRST_ULL_lfta_LFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void FIRST_LL_lfta_LFTA_AGGR_INIT_(gs_int64_t* scratch);
void FIRST_LL_lfta_LFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val);
gs_retval_t FIRST_LL_lfta_LFTA_AGGR_FLUSHME_(gs_int64_t* scratch);
void FIRST_LL_lfta_LFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch);
void FIRST_LL_lfta_LFTA_AGGR_DESTROY_(gs_int64_t* scratch);

void FIRST_STR_lfta_LFTA_AGGR_INIT_(struct gs_string* scratch);
void FIRST_STR_lfta_LFTA_AGGR_UPDATE_(struct gs_string* scratch, struct gs_string* val);
gs_retval_t FIRST_STR_lfta_LFTA_AGGR_FLUSHME_(struct gs_string* scratch);
void FIRST_STR_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, struct gs_string* scratch);
void FIRST_STR_lfta_LFTA_AGGR_DESTROY_(struct gs_string* scratch);

//      last aggregate
void LAST_lfta_LFTA_AGGR_INIT_(gs_uint32_t* scratch);
void LAST_lfta_LFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val);
gs_retval_t LAST_lfta_LFTA_AGGR_FLUSHME_(gs_uint32_t* scratch);
void LAST_lfta_LFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch);
void LAST_lfta_LFTA_AGGR_DESTROY_(gs_uint32_t* scratch);

void LAST_INT_lfta_LFTA_AGGR_INIT_(gs_int32_t* scratch);
void LAST_INT_lfta_LFTA_AGGR_UPDATE_(gs_int32_t* scratch, gs_int32_t val);
gs_retval_t LAST_INT_lfta_LFTA_AGGR_FLUSHME_(gs_int32_t* scratch);
void LAST_INT_lfta_LFTA_AGGR_OUTPUT_(gs_int32_t* res, gs_int32_t* scratch);
void LAST_INT_lfta_LFTA_AGGR_DESTROY_(gs_int32_t* scratch);

void LAST_ULL_lfta_LFTA_AGGR_INIT_(gs_uint64_t* scratch);
void LAST_ULL_lfta_LFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
gs_retval_t LAST_ULL_lfta_LFTA_AGGR_FLUSHME_(gs_uint64_t* scratch);
void LAST_ULL_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void LAST_ULL_lfta_LFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void LAST_LL_lfta_LFTA_AGGR_INIT_(gs_int64_t* scratch);
void LAST_LL_lfta_LFTA_AGGR_UPDATE_(gs_int64_t* scratch, gs_int64_t val);
gs_retval_t LAST_LL_lfta_LFTA_AGGR_FLUSHME_(gs_int64_t* scratch);
void LAST_LL_lfta_LFTA_AGGR_OUTPUT_(gs_int64_t* res, gs_int64_t* scratch);
void LAST_LL_lfta_LFTA_AGGR_DESTROY_(gs_int64_t* scratch);

void LAST_STR_lfta_LFTA_AGGR_INIT_(struct gs_string* scratch);
void LAST_STR_lfta_LFTA_AGGR_UPDATE_(struct gs_string* scratch, struct gs_string* val);
gs_retval_t LAST_STR_lfta_LFTA_AGGR_FLUSHME_(struct gs_string* scratch);
void LAST_STR_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, struct gs_string* scratch);
void LAST_STR_lfta_LFTA_AGGR_DESTROY_(struct gs_string* scratch);

//	count_diff aggregate
void count_diff_lfta_ui_LFTA_AGGR_INIT_(gs_sp_t s) ;
void count_diff_lfta_ui_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint32_t val) ;
void count_diff_lfta_ui_LFTA_AGGR_OUTPUT_(struct gs_string *res, gs_sp_t s) ;
void count_diff_lfta_ui_LFTA_AGGR_DESTROY_(gs_sp_t s) ;
gs_retval_t count_diff_lfta_ui_LFTA_AGGR_FLUSHME_(gs_sp_t s) ;

void count_diff_lfta_i_LFTA_AGGR_INIT_(gs_sp_t s) ;
void count_diff_lfta_i_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_int32_t val) ;
void count_diff_lfta_i_LFTA_AGGR_OUTPUT_(struct gs_string *res, gs_sp_t s) ;
void count_diff_lfta_i_LFTA_AGGR_DESTROY_(gs_sp_t s) ;
gs_retval_t count_diff_lfta_i_LFTA_AGGR_FLUSHME_(gs_sp_t s) ;

void count_diff_lfta_ul_LFTA_AGGR_INIT_(gs_sp_t s) ;
void count_diff_lfta_ul_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_uint64_t val) ;
void count_diff_lfta_ul_LFTA_AGGR_OUTPUT_(struct gs_string *res, gs_sp_t s) ;
void count_diff_lfta_ul_LFTA_AGGR_DESTROY_(gs_sp_t s) ;
gs_retval_t count_diff_lfta_ul_LFTA_AGGR_FLUSHME_(gs_sp_t s) ;

void count_diff_lfta_l_LFTA_AGGR_INIT_(gs_sp_t s) ;
void count_diff_lfta_l_LFTA_AGGR_UPDATE_(gs_sp_t s, gs_int64_t val) ;
void count_diff_lfta_l_LFTA_AGGR_OUTPUT_(struct gs_string *res, gs_sp_t s) ;
void count_diff_lfta_l_LFTA_AGGR_DESTROY_(gs_sp_t s) ;
gs_retval_t count_diff_lfta_l_LFTA_AGGR_FLUSHME_(gs_sp_t s) ;

void count_diff_lfta_s_LFTA_AGGR_INIT_(gs_sp_t s) ;
void count_diff_lfta_s_LFTA_AGGR_UPDATE_(gs_sp_t s, struct gs_string *val) ;
void count_diff_lfta_s_LFTA_AGGR_OUTPUT_(struct gs_string *res, gs_sp_t s) ;
void count_diff_lfta_s_LFTA_AGGR_DESTROY_(gs_sp_t s) ;
gs_retval_t count_diff_lfta_s_LFTA_AGGR_FLUSHME_(gs_sp_t s) ;


//		running_array_aggr aggregate
void running_array_aggr_lfta_LFTA_AGGR_INIT_(char* scratch);
void running_array_aggr_lfta_LFTA_AGGR_UPDATE_(char* scratch, gs_uint32_t val);
gs_retval_t running_array_aggr_lfta_LFTA_AGGR_FLUSHME_(char* scratch);
void running_array_aggr_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, char* scratch);
void running_array_aggr_lfta_LFTA_AGGR_DESTROY_(char* scratch);

//////////////////////////////////////////////////////////////////
///		Flip-s sample-based quantiles

/****************************************************************/
/* LFTA functions						*/
/****************************************************************/

void quant_udaf_lfta3_LFTA_AGGR_INIT_(gs_sp_t);
void quant_udaf_lfta3_LFTA_AGGR_UPDATE_(gs_sp_t, gs_uint32_t);
gs_retval_t quant_udaf_lfta3_LFTA_AGGR_FLUSHME_(gs_sp_t);
void quant_udaf_lfta3_LFTA_AGGR_OUTPUT_(struct gs_string *, gs_sp_t);
void quant_udaf_lfta3_LFTA_AGGR_DESTROY_(gs_sp_t);

/////////////////////////////////////////////////////////
// ==============================================================
//	other rts functions.	

//		sum up unsigned integers expressed as a string with separators,
//		e.g. on input '34|45|56' and sep '|', return 135.
//		This kind of thing is common in Nokia PCMD data.
// gracefully handle empty entries, e.g. '|8|' should return 8
gs_int64_t sum_uint_in_list(struct gs_string *list, struct gs_string *sepchar);

//	Convert a string to a llong.
//	Has some protection to reject non-numeric characters.
//	a leading minus sign is allowed
gs_int64_t to_llong(struct gs_string *v);

#ifdef __cplusplus
}
#endif

#endif
