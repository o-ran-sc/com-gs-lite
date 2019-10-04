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

#ifndef _HFTA_UDAF_H_INCLUDED_
#define _HFTA_UDAF_H_INCLUDED_

#include "vstring.h"
#include "host_tuple.h"
#include "gsconfig.h"

// -------------------------------------------------------------------
//		sum over 3 intervals : test rUDAF
void sum3_HFTA_AGGR_INIT_(gs_sp_t buf) ;
void sum3_HFTA_AGGR_UPDATE_(gs_sp_t buf, gs_uint32_t s) ;
void sum3_HFTA_AGGR_OUTPUT_(gs_uint32_t *result, gs_sp_t buf) ;
void sum3_HFTA_AGGR_DESTROY_(gs_sp_t buf) ;
void sum3_HFTA_AGGR_REINIT_( gs_sp_t buf) ;


// -------------------------------------------------------------------
//		running sum over arbitrary intervals.
void moving_sum_udaf_HFTA_AGGR_INIT_(gs_sp_t buf) ;
void moving_sum_udaf_HFTA_AGGR_UPDATE_(gs_sp_t buf, gs_uint32_t s, gs_uint32_t N) ;
void moving_sum_udaf_HFTA_AGGR_OUTPUT_(gs_uint64_t *result, gs_sp_t buf) ;
void moving_sum_udaf_HFTA_AGGR_DESTROY_(gs_sp_t buf) ;
void moving_sum_udaf_HFTA_AGGR_REINIT_( gs_sp_t buf) ;

#define super_moving_sum_udaf_HFTA_AGGR_INIT_ moving_sum_udaf_HFTA_AGGR_INIT_
void super_moving_sum_udaf_HFTA_AGGR_UPDATE_(gs_sp_t buf, gs_uint64_t s) ;
#define super_moving_sum_udaf_HFTA_AGGR_OUTPUT_ moving_sum_udaf_HFTA_AGGR_OUTPUT_
#define super_moving_sum_udaf_HFTA_AGGR_DESTROY_ moving_sum_udaf_HFTA_AGGR_DESTROY_
#define super_moving_sum_udaf_HFTA_AGGR_REINIT_ moving_sum_udaf_HFTA_AGGR_REINIT_

gs_uint32_t moving_sum_extract(gs_uint64_t result);
gs_float_t moving_sum_extract_exp(gs_uint64_t result, gs_float_t alpha);


/////////////////////////////////////////////////////////////////////////
/////   Calculate the average of all positive float numbers

void POSAVG_HFTA_AGGR_INIT_(gs_sp_t buf);
void POSAVG_HFTA_AGGR_UPDATE_(gs_sp_t buf, gs_float_t v);
void POSAVG_HFTA_AGGR_OUTPUT_(gs_float_t * v, gs_sp_t buf);
void POSAVG_HFTA_AGGR_DESTROY_(gs_sp_t buf);


///////////////////////////////////////////////////////////////////
/////			avg_udaf (simple example)

//		hfta avg_udaf
void avg_udaf_HFTA_AGGR_INIT_(gs_sp_t b);
void avg_udaf_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v);
void avg_udaf_HFTA_AGGR_OUTPUT_(vstring *r,gs_sp_t b);
void avg_udaf_HFTA_AGGR_DESTROY_(gs_sp_t b);

//		avg_udaf superaggregate
void avg_udaf_hfta_HFTA_AGGR_INIT_(gs_sp_t b);
void avg_udaf_hfta_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v);
void avg_udaf_hfta_HFTA_AGGR_OUTPUT_(vstring *r,gs_sp_t b);
void avg_udaf_hfta_HFTA_AGGR_DESTROY_(gs_sp_t b);

//		Extraction function
gs_float_t extr_avg_fcn(vstring *v);

//      first aggregate
// hfta only
void FIRST_HFTA_AGGR_INIT_(gs_uint32_t* scratch);
void FIRST_HFTA_AGGR_REINIT_(gs_uint32_t* scratch);
void FIRST_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val);
void FIRST_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch);
void FIRST_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch);

void FIRST_HFTA_AGGR_INIT_(gs_uint64_t* scratch);
void FIRST_HFTA_AGGR_REINIT_(gs_uint64_t* scratch);
void FIRST_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
void FIRST_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void FIRST_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch);


void FIRST_ULL_HFTA_AGGR_INIT_(gs_uint64_t* scratch);
void FIRST_ULL_HFTA_AGGR_REINIT_(gs_uint64_t* scratch);
void FIRST_ULL_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
void FIRST_ULL_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void FIRST_ULL_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void FIRST_STR_HFTA_AGGR_INIT_(vstring* scratch);
void FIRST_STR_HFTA_AGGR_REINIT_(vstring* scratch);
void FIRST_STR_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val);
void FIRST_STR_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch);
void FIRST_STR_HFTA_AGGR_DESTROY_(vstring* scratch);
// hfts-lfta split
void FIRST_hfta_HFTA_AGGR_INIT_(gs_uint32_t* scratch);
void FIRST_hfta_HFTA_AGGR_REINIT_(gs_uint32_t* scratch);
void FIRST_hfta_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val);
void FIRST_hfta_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch);
void FIRST_hfta_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch);

void FIRST_ULL_hfta_HFTA_AGGR_INIT_(gs_uint64_t* scratch);
void FIRST_ULL_hfta_HFTA_AGGR_REINIT_(gs_uint64_t* scratch);
void FIRST_ULL_hfta_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
void FIRST_ULL_hfta_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void FIRST_ULL_hfta_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void FIRST_STR_hfta_HFTA_AGGR_INIT_(vstring* scratch);
void FIRST_STR_hfta_HFTA_AGGR_REINIT_(vstring* scratch);
void FIRST_STR_hfta_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val);
void FIRST_STR_hfta_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch);
void FIRST_STR_hfta_HFTA_AGGR_DESTROY_(vstring* scratch);

//      last aggregate
//  hfta only
void LAST_HFTA_AGGR_INIT_(gs_uint32_t* scratch);
void LAST_HFTA_AGGR_REINIT_(gs_uint32_t* scratch);
void LAST_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val);
void LAST_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch);
void LAST_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch);

void LAST_HFTA_AGGR_INIT_(gs_uint64_t* scratch);
void LAST_HFTA_AGGR_REINIT_(gs_uint64_t* scratch);
void LAST_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
void LAST_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void LAST_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void LAST_ULL_HFTA_AGGR_INIT_(gs_uint64_t* scratch);
void LAST_ULL_HFTA_AGGR_REINIT_(gs_uint64_t* scratch);
void LAST_ULL_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
void LAST_ULL_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void LAST_ULL_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void LAST_STR_HFTA_AGGR_INIT_(vstring* scratch);
void LAST_STR_HFTA_AGGR_REINIT_(vstring* scratch);
void LAST_STR_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val);
void LAST_STR_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch);
void LAST_STR_HFTA_AGGR_DESTROY_(vstring* scratch);

// hfta/lfta split
void LAST_hfta_HFTA_AGGR_INIT_(gs_uint32_t* scratch);
void LAST_hfta_HFTA_AGGR_REINIT_(gs_uint32_t* scratch);
void LAST_hfta_HFTA_AGGR_UPDATE_(gs_uint32_t* scratch, gs_uint32_t val);
void LAST_hfta_HFTA_AGGR_OUTPUT_(gs_uint32_t* res, gs_uint32_t* scratch);
void LAST_hfta_HFTA_AGGR_DESTROY_(gs_uint32_t* scratch);

void LAST_ULL_hfta_HFTA_AGGR_INIT_(gs_uint64_t* scratch);
void LAST_ULL_hfta_HFTA_AGGR_REINIT_(gs_uint64_t* scratch);
void LAST_ULL_hfta_HFTA_AGGR_UPDATE_(gs_uint64_t* scratch, gs_uint64_t val);
void LAST_ULL_hfta_HFTA_AGGR_OUTPUT_(gs_uint64_t* res, gs_uint64_t* scratch);
void LAST_ULL_hfta_HFTA_AGGR_DESTROY_(gs_uint64_t* scratch);

void LAST_STR_hfta_HFTA_AGGR_INIT_(vstring* scratch);
void LAST_STR_hfta_HFTA_AGGR_REINIT_(vstring* scratch);
void LAST_STR_hfta_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val);
void LAST_STR_hfta_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch);
void LAST_STR_hfta_HFTA_AGGR_DESTROY_(vstring* scratch);

//		running_array_aggr aggregate
void running_array_aggr_hfta_HFTA_AGGR_INIT_(vstring* scratch);
void running_array_aggr_hfta_HFTA_AGGR_REINIT_(vstring* scratch);
void running_array_aggr_hfta_HFTA_AGGR_UPDATE_(vstring* scratch, vstring* val);
void running_array_aggr_hfta_HFTA_AGGR_OUTPUT_(vstring* res, vstring* scratch);
void running_array_aggr_hfta_HFTA_AGGR_DESTROY_(vstring* scratch);

////////////////////////////////////////////////////////////////
///		Flip's sample-based quantiles

/****************************************************************/
/* HFTA functions						*/
/****************************************************************/

void quant_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t);
void quant_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t, vstring *);
void quant_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *, gs_sp_t);
void quant_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t);
gs_uint32_t extr_quant_hfta3_fcn(vstring *, gs_float_t);
gs_uint32_t extr_med_hfta3_fcn(vstring *);
gs_uint32_t extr_quant_hfta3_space(vstring *);

/****************************************************************/
/* HFTA-only functions						*/
/****************************************************************/
void quant_udaf_hfta0_HFTA_AGGR_INIT_(gs_sp_t);
void quant_udaf_hfta0_HFTA_AGGR_UPDATE_(gs_sp_t, gs_uint32_t);
void quant_udaf_hfta0_HFTA_AGGR_OUTPUT_(vstring *, gs_sp_t);
void quant_udaf_hfta0_HFTA_AGGR_DESTROY_(gs_sp_t);
gs_uint32_t extr_quant_hfta0_fcn(vstring *, gs_float_t);
gs_uint32_t extr_med_hfta0_fcn(vstring *);
gs_uint32_t extr_quant_hfta0_space(vstring *);

#endif
