#ifndef RTS_STRING_H
#define RTS_STRING_H

#ifdef __cplusplus
extern "C" {
#endif



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

#include <stdint.h>
#include<math.h>


#include "gsconfig.h"
#include "gstypes.h"

#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x100)

//	struct string32 matches vstring32, its the packed record format.
//	struct gs_string is the in-memory format.

struct string32{
	gs_int32_t length;
	gs_int32_t offset;
	gs_int32_t reserved;
};


/* struct gs_string has to match definition in host.h however, the data
 types differ */

struct gs_string {
    gs_int32_t length;
    gs_sp_t data;
    struct FTA * owner;    
};

#include "fta.h"
#include "rts.h"


/* Basic string operation */

gs_retval_t str_assign_with_copy(struct FTA *, struct gs_string * dest, struct gs_string * src);

gs_retval_t str_assign_with_copy_in_tuple(struct string32 * dest, struct gs_string * src,
                                          gs_sp_t start, gs_sp_t buf);

#define str_destroy(s) {if ((s)->owner!=0) fta_free((s)->owner,(s)->data);}

gs_retval_t str_replace(struct FTA *,  struct gs_string * dest, struct gs_string * src );

#define str_length(s) (s)->length

/* Searching within a string */

gs_retval_t str_exists_substr( struct gs_string * str1, struct gs_string * str2);

/* String comparison */

gs_retval_t str_compare( struct gs_string * str1, struct gs_string * str2);

/* String equality */

gs_retval_t str_equal( struct gs_string * str1, struct gs_string * str2);

/*	Construct a string constant */

gs_retval_t str_constructor(struct gs_string *s, gs_csp_t l);

/*	string hash	*/

#define string_hash(s) lfta_V_STR_to_hash((*(s)))

/* External Function definitions */

#define ULLMIN(x,y) (unsigned long long)(((x)<(y)?(x):(y)))
#define ULLMAX(x,y) (unsigned long long)(((x)<(y)?(y):(x)))
#define LLMIN(x,y) (long long int)(((x)<(y)?(x):(y)))
#define LLMAX(x,y) (long long int)(((x)<(y)?(y):(x)))
#define UMIN(x,y) (unsigned int)(((x)<(y)?(x):(y)))
#define UMAX(x,y) (unsigned int)(((x)<(y)?(y):(x)))
#define LMIN(x,y) (int)(((x)<(y)?(x):(y)))
#define LMAX(x,y) (int)(((x)<(y)?(y):(x)))
#define FMIN(x,y) (double)(((x)<(y)?(x):(y)))
#define FMAX(x,y) (double)(((x)<(y)?(y):(x)))

// type conversion
#define INT(c) ((int)(c))
#define UINT(c) ((unsigned int)(c))
#define ULLONG(c) ((unsigned long long)(c))
#define LLONG(c) ((long long int)(c))
#define FLOAT(c) ((double)(c))

// comparison
#define EQ(x,y) ((x)==(y))
#define GEQ(x,y) ((x)>=(y))
#define GE(x,y) ((x)>(y))
#define LEQ(x,y) ((x)<=(y))
#define LE(x,y) ((x)<(y))

// if_else
#define if_else_f(x,y,z) (double)(((x)==0?(z):(y)))
#define if_else_ll(x,y,z) (long long int)(((x)==0?(z):(y)))
#define if_else_ul(x,y,z) (unsigned long long)(((x)==0?(z):(y)))
#define if_else_u(x,y,z) (unsigned int)(((x)==0?(z):(y)))
#define if_else_i(x,y,z) (int)(((x)==0?(z):(y)))

//	Cast away temporality
#define non_temporal(x)(x)

//	endian swap
#define endian_swap_ui(x) ( (( (x) & 0xFF000000) >> 24) | (( (x) & 0x00FF0000) >> 8) | (( (x) & 0x0000FF00) << 8) | (( (x) & 0x000000FF) << 24) ) 


//	Access math libraries
#define sqrt(x) sqrt(x)
#define pow(x,y) pow((x),(y))
#define sin(x) sin(x)
#define cos(x) cos(x)
#define tan(x) tan(x)
#define asin(x) asin(x)
#define acos(x) acos(x)
#define atan(x) atan(x)
#define log(x) log(x)
#define log2(x) log2(x)
#define log10(x) log10(x)
#define ceil(x) ceil(x)
#define floor(x) floor(x)
#define fmod(x) fmod(x)
#define trunc(x) trunc(x)




gs_uint32_t str_match_offset( gs_uint32_t offset, struct gs_string * s1, struct gs_string * s2);
gs_uint32_t byte_match_offset( gs_uint32_t offset, gs_uint32_t val, struct gs_string * s2);
gs_param_handle_t register_handle_for_str_regex_match_slot_1(struct FTA * f,
                                                             struct gs_string* pattern);
gs_uint32_t str_regex_match(struct gs_string* str, gs_param_handle_t pattern_handle);
gs_retval_t deregister_handle_for_str_regex_match_slot_1(gs_param_handle_t handle);

gs_param_handle_t register_handle_for_str_partial_regex_match_slot_1(struct FTA * f,
                                                                     struct gs_string* pattern);
gs_uint32_t str_partial_regex_match(struct gs_string* str,
                                    gs_param_handle_t pattern_handle,
                                    gs_uint32_t maxlen);
gs_retval_t deregister_handle_for_str_partial_regex_match_slot_1(
                                                                 gs_param_handle_t
                                                                 handle);
// ----------------------------------
//	Substring functions
inline static gs_retval_t str_truncate(struct gs_string * result, struct gs_string *str, gs_uint32_t length) {
	result->data=str->data;
	result->length=(str->length<length)?str->length:length;
	return 0;
}
gs_retval_t str_suffix(struct gs_string * ret, struct gs_string *s, gs_uint32_t n);
gs_retval_t get_list_entry(struct gs_string * ret, struct gs_string *l, struct gs_string *sep, gs_uint32_t pos);


// ----------------------------------
//	constant string conversions
gs_param_handle_t register_handle_for_strtoi_c_slot_0(struct FTA * f, struct gs_string* istr) ;
gs_retval_t deregister_handle_for_strtoi_c_slot_0(gs_param_handle_t h) ;
#define strtoi_c(h) ((unsigned int)(h))

gs_param_handle_t register_handle_for_strtoip_c_slot_0(struct FTA * f, struct gs_string* istr) ;
gs_retval_t deregister_handle_for_strtoip_c_slot_0(gs_param_handle_t h) ;
#define strtoip_c(h) ((unsigned int)(h))



////////////////////////////////////////////////
///		IPV6

#ifndef IPV6_STR
#define IPV6_STR
struct ipv6_str{
	gs_uint32_t v[4];
};
#endif

gs_int32_t ipv6_compare( struct ipv6_str  i1, struct ipv6_str  i2);
gs_int32_t Ipv6_Constructor(struct ipv6_str *s, char *l);
struct ipv6_str And_Ipv6(const struct ipv6_str i1, const struct ipv6_str i2);
struct ipv6_str Or_Ipv6(const struct ipv6_str i1, const struct ipv6_str i2);
struct ipv6_str hton_ipv6(struct ipv6_str s);
struct ipv6_str ntoh_ipv6(struct ipv6_str s);


////////////////////////////////////////////////
///		Regex pattern extraction based on signature library for VideoNOC
gs_param_handle_t register_handle_for_signaturelib_get_content_id_slot_2(struct FTA * f, struct gs_string* signature_file);
gs_uint32_t signaturelib_get_content_id(struct gs_string* result, struct gs_string* url, gs_uint32_t content_length, gs_param_handle_t handle);
gs_retval_t deregister_handle_for_signaturelib_get_content_id_slot_2(gs_param_handle_t handle);

gs_uint32_t signaturelib_get_fqdn(struct gs_string* result);
gs_uint32_t signaturelib_get_channel_type(struct gs_string* result);

#ifdef __cplusplus
}
#endif

#endif
