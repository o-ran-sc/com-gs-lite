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

void FIRST_ULL_lfta_LFTA_AGGR_INIT_(gs_uint64_t* scratch);
void FIRST_ULL_lfta_LFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
gs_retval_t FIRST_ULL_lfta_LFTA_AGGR_FLUSHME_(gs_uint64_t* scratch);
void FIRST_ULL_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void FIRST_ULL_lfta_LFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

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

void LAST_ULL_lfta_LFTA_AGGR_INIT_(gs_uint64_t* scratch);
void LAST_ULL_lfta_LFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
gs_retval_t LAST_ULL_lfta_LFTA_AGGR_FLUSHME_(gs_uint64_t* scratch);
void LAST_ULL_lfta_LFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void LAST_ULL_lfta_LFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void LAST_STR_lfta_LFTA_AGGR_INIT_(struct gs_string* scratch);
void LAST_STR_lfta_LFTA_AGGR_UPDATE_(struct gs_string* scratch, struct gs_string* val);
gs_retval_t LAST_STR_lfta_LFTA_AGGR_FLUSHME_(struct gs_string* scratch);
void LAST_STR_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, struct gs_string* scratch);
void LAST_STR_lfta_LFTA_AGGR_DESTROY_(struct gs_string* scratch);

//		running_array_aggr aggregate
void running_array_aggr_lfta_LFTA_AGGR_INIT_(char* scratch);
void running_array_aggr_lfta_LFTA_AGGR_UPDATE_(char* scratch, gs_uint32_t val);
gs_retval_t running_array_aggr_lfta_LFTA_AGGR_FLUSHME_(char* scratch);
void running_array_aggr_lfta_LFTA_AGGR_OUTPUT_(struct gs_string* res, char* scratch);
void running_array_aggr_lfta_LFTA_AGGR_DESTROY_(char* scratch);


#endif
