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

#ifndef __HFTA_RUNTIME_LIBRARY__
#define __HFTA_RUNTIME_LIBRARY__
#include "host_tuple.h"
#include "gsconfig.h"
#include "gstypes.h"


#define string_hash(s) hfta_vstr_hashfunc(s)
#define string_hash_long(s) hfta_vstr_long_hashfunc(s) 


#define DNS_SAMPLE_HASH_SZ 50000000
#define DNS_HITLIST_HASH_SZ 50000000
#define DNS_HITLIST_ENTRY_SZ 500000


//		Internal functions
void hfta_vstr_init(vstring * str);
gs_retval_t Vstring_Constructor(vstring *, gs_csp_t);
gs_retval_t hfta_vstr_length(vstring *);
void hfta_vstr_assign_with_copy_in_tuple(vstring32 *, const vstring *,
	gs_sp_t, int);
void hfta_vstr_assign_with_copy(vstring *, const vstring *);
void hfta_vstr_destroy(vstring *);
void hfta_vstr_replace(vstring *, const vstring *);

gs_uint32_t hfta_vstr_hashfunc(const vstring *);
gs_uint64_t hfta_vstr_long_hashfunc(const vstring *);
gs_retval_t hfta_vstr_compare(const vstring *, const vstring *);
gs_retval_t hfta_vstr_equal(const vstring *, const vstring *);

gs_retval_t hfta_ipv6_compare(const hfta_ipv6_str &i1, const hfta_ipv6_str &i2);
hfta_ipv6_str And_Ipv6(const hfta_ipv6_str &i1, const hfta_ipv6_str &i2);
hfta_ipv6_str Or_Ipv6(const hfta_ipv6_str &i1, const hfta_ipv6_str &i2);
gs_uint32_t hfta_ipv6_hashfunc(const hfta_ipv6_str *s) ;
hfta_ipv6_str hton_ipv6(hfta_ipv6_str s);
hfta_ipv6_str ntoh_ipv6(hfta_ipv6_str s);
gs_retval_t HFTA_Ipv6_Constructor(hfta_ipv6_str *s, gs_csp_t l) ;




//		External functions

inline static gs_retval_t str_truncate(vstring * result, vstring *str, gs_uint32_t length) {
	result->offset=str->offset;
	result->length=(str->length<length)?str->length:length;
	result->reserved=SHALLOW_COPY;
	return 0;
}
gs_retval_t str_suffix(vstring *result,  vstring *s, gs_uint32_t n);
gs_retval_t get_list_entry(vstring *result, vstring *s, vstring *sep, gs_uint32_t pos);


gs_retval_t str_exists_substr(vstring * s1, vstring * s2);
gs_retval_t str_compare(vstring * s1, vstring * s2);
gs_retval_t str_equal(vstring * s1, vstring * s2);

gs_uint32_t str_match_offset(gs_uint32_t offset,vstring *s1,vstring *s2);
gs_uint32_t byte_match_offset( gs_uint32_t offset, gs_uint32_t val,vstring *s2);


// REGEX functions

gs_retval_t str_regex_match(vstring* str, gs_param_handle_t pattern_handle);
gs_param_handle_t register_handle_for_str_regex_match_slot_1(vstring* pattern);
gs_retval_t deregister_handle_for_str_regex_match_slot_1(gs_param_handle_t handle);

gs_retval_t str_partial_regex_match(vstring* str, gs_param_handle_t pattern_handle);
gs_param_handle_t register_handle_for_str_partial_regex_match_slot_1(vstring* pattern);
gs_retval_t deregister_handle_for_str_partial_regex_match_slot_1(gs_param_handle_t handle);

gs_param_handle_t register_handle_for_str_extract_regex_slot_1(vstring* pattern);
gs_retval_t str_extract_regex( vstring * result, vstring * str, gs_param_handle_t handle);
gs_retval_t deregister_handle_for_str_extract_regex_slot_1(gs_param_handle_t handle);




// type conversion
//		Avoid redefinition from rts_udaf.h
#ifndef INT
	#define INT(c) ((int)(c))
	#define UINT(c) ((gs_uint32_t)(c))
	#define FLOAT(c) ((gs_float_t)(c))
	#define LLONG(c) ((long long int)(c))
	#define ULLONG(c) ((gs_uint64_t)(c))
#endif

// string conversions

gs_uint32_t strtoi(gs_uint32_t * r, struct vstring *data);
gs_uint32_t strtoip(gs_uint32_t * r, struct vstring *data);

//	constant string conversions
//		Avoid redefinition from rts_udaf.h
#ifndef strtoi_c
	#define strtoi_c(h) ((gs_uint32_t)(h))
	#define strtoip_c(h) ((gs_uint32_t)(h))
#endif
gs_param_handle_t register_handle_for_strtoi_c_slot_0(vstring* istr) ;
gs_retval_t deregister_handle_for_strtoi_c_slot_0(gs_param_handle_t h) ;

gs_param_handle_t register_handle_for_strtoip_c_slot_0(vstring* istr) ;
gs_retval_t deregister_handle_for_strtoip_c_slot_0(gs_param_handle_t h) ;


inline gs_uint32_t str_match_offset( gs_uint32_t offset, struct vstring * s1, struct vstring * s2) {
	register gs_uint8_t *st1 = (gs_uint8_t *) s1->offset;
	register gs_uint8_t *st2 = (gs_uint8_t *) (s2->offset+offset);
	register gs_int32_t x;
	register gs_int32_t len2 = s2->length-offset;
	register gs_int32_t len1 = s1->length;
	if (len2<len1) return 0;
	for(x=0; x<len1; x++) {
		if (st1[x]!=st2[x]) return 0;
	}
	return 1;
}

// -------------------------------------------------------
//		map_int_to_string and its support functions, structs

gs_param_handle_t register_handle_for_int_to_string_map_slot_1(vstring *filename);
gs_retval_t int_to_string_map(vstring *result, gs_int64_t val, gs_param_handle_t handle);
gs_param_handle_t deregister_handle_for_int_to_string_map_slot_1(gs_param_handle_t handle);

// --------------------------------------------------
//	to_hex_string, for printing a binary string

gs_retval_t to_hex_string(vstring *result, vstring *val);

// ------------------------------------------------------
//		sum up unsigned integers expressed as a string with separators,
//		e.g. on input '34|45|56' and sep '|', return 135.
//		This kind of thing is common in Nokia PCMD data.
// gracefully handle empty entries, e.g. '|8|' should return 8
gs_int64_t sum_uint_in_list(struct vstring *list, struct vstring *sepchar);

// --------------------------------------------
//	Convert an string to an integer
gs_int64_t to_llong(vstring *v);


#endif
