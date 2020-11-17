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

#include <sys/types.h>
#include <iostream>
extern "C" {
#include "gsconfig.h"
#include "gstypes.h"
#include <regex.h>
#include <rdtsc.h>
#include <stringhash.h>
#include <errno.h>
#include <unistd.h>
}
#include <stdio.h>
#include <string.h>

#include <vstring.h>
#include <host_tuple.h>
#include <fta.h>

#include<map>

// for htonl,ntohl
#include <netinet/in.h>

#define MAX_PATTERN_LEN 1024

// Defined here to avoid link errors as this array is auto generated for the lfta and referenced in the clearinghouse library which gets linked against the hfta
extern "C" gs_sp_t fta_names[]={0};


//		Only used to construct constant strings ...
gs_retval_t Vstring_Constructor(vstring *tmp, gs_csp_t str) {
	tmp->length = strlen(str);
	if(tmp->length)
		tmp->offset = (gs_p_t)strdup(str);
	tmp->reserved = SHALLOW_COPY;
	return 0;
}

//		Assume str is INTERNAL or SHALLOW_COPY.
void hfta_vstr_destroy(vstring * str) {
	if (str->length && str->reserved == INTERNAL) {
		free((gs_sp_t)str->offset);
	}
	str->length = 0;
}

//	Make the vstring safe to destroy even if its never initialized
//	(e.g. stack-allocated groups containing strings)
void hfta_vstr_init(vstring * str) {
	str->length = 0;
}

gs_retval_t hfta_vstr_length(vstring *str) {
	return str->length;
}

//		Assume that SRC is either INTERNAL or SHALLOW_COPY
void hfta_vstr_assign_with_copy_in_tuple(vstring32 * target,
		const vstring * src, gs_sp_t data_offset,  gs_retval_t int_offset) {
	target->length = src->length;
	target->offset = int_offset;
	target->reserved = PACKED;
	if ( src->length)
		memcpy(data_offset, (gs_sp_t)src->offset, src->length);
}

//		Ted wrote the following function.
//		make deep copy of src.  Assume that dst is already empty.
//		Assume that SRC is either INTERNAL or SHALLOW_COPY
void hfta_vstr_assign_with_copy(vstring *dst, const vstring *src){
	dst->length=src->length;
	if(src->length){
		dst->offset=(gs_p_t)malloc(dst->length);
		memcpy((gs_sp_t)(dst->offset),(gs_sp_t)(src->offset),dst->length);
	}
	dst->reserved=INTERNAL;
}

//		Ted wrote the following function.
//		Make a deep copy of src.  garbage collect dst if needed.
//		Assume that SRC is either INTERNAL or SHALLOW_COPY
void hfta_vstr_replace(vstring *dst, const vstring *src){
	hfta_vstr_destroy(dst);
	hfta_vstr_assign_with_copy(dst,src);
}

#define HFTA_VSTR_LHASHFUNC_PRIME 12916008961267169387ull
gs_uint64_t hfta_vstr_long_hashfunc(const vstring *s) {
	gs_uint64_t hash_code;
	gs_int32_t n_steps;
	gs_int32_t substr_len;
	gs_int32_t j, k;
	gs_uint64_t sub_hash;
	gs_sp_t sv;

	sv=(gs_sp_t)(s->offset);
	hash_code = 0;
	n_steps = s->length / 4;
	if(4*n_steps < s->length) n_steps++;

	for (j = 0; j <  n_steps; j++) {
		if(4*(j+1) < s->length) substr_len = 4;
		else                  substr_len = s->length - 4*j;

		sub_hash = 0;
	 	for(k=0;k<4;k++){
		  if(k < substr_len)
  			sub_hash = (sub_hash << 4) + *sv;
  		  else
  			sub_hash = (sub_hash << 4);
		  sv++;
	  	}

		hash_code = (sub_hash + hash_code * HFTA_VSTR_LHASHFUNC_PRIME);
	}

	return(hash_code);
}

#define HFTA_VSTR_HASHFUNC_PRIME 2995999
gs_uint32_t hfta_vstr_hashfunc(const vstring *s) {
	gs_uint32_t hash_code;
	gs_int32_t n_steps;
	gs_int32_t substr_len;
	gs_int32_t j;
	gs_uint32_t k, sub_hash;
	gs_sp_t sv;

	sv=(gs_sp_t)(s->offset);
	hash_code = 0;
	n_steps = s->length / 4;
	if(4*n_steps < s->length) n_steps++;

	for (j = 0; j <  n_steps; j++) {
		if(4*(j+1) < s->length) substr_len = 4;
		else                  substr_len = s->length - 4*j;

		sub_hash = 0;
	 	for(k=0;k<4;k++){
		  if(k < substr_len)
  			sub_hash = (sub_hash << 4) + *sv;
  		  else
  			sub_hash = (sub_hash << 4);
		  sv++;
	  	}

		hash_code = (sub_hash + hash_code * HFTA_VSTR_HASHFUNC_PRIME);
	}

	return(hash_code);
}


//	return negative if s1 < s2, 0 if s1==s2, positive if s1>s2
gs_retval_t hfta_vstr_compare(const vstring * s1, const vstring * s2) {
	gs_int32_t minlen,cmp_ret;
	minlen=(s1->length<s2->length?s1->length:s2->length);
	cmp_ret=memcmp((void *)s1->offset,(void *)s2->offset,minlen);

	if(cmp_ret) return cmp_ret;
	return(s1->length - s2->length);
}

gs_retval_t hfta_vstr_equal(const vstring * s1, const vstring * s2) {
	gs_int32_t x;

	if(s1->length != s2->length)
		return -1;

//	cmp_ret=memcmp((void *)s1->offset,(void *)s2->offset,s1->length);
    for(x=0;x<s1->length;x++) {
        if (((char *)(s1->offset))[x]!=((char *)(s2->offset))[x]) {
            return -1;
        }
    }


	return 0;
}



gs_param_handle_t register_handle_for_str_regex_match_slot_1(vstring* pattern) {
    regex_t * reg;
    gs_int32_t res;

    if ((reg=(regex_t *) malloc(sizeof(regex_t)))==0)  {
	gslog(LOG_EMERG, "No memory for regular expression %s\n",
		(gs_sp_t)(pattern->offset));
	return 0;
    }

    if (regcomp(reg,(char*)(pattern->offset), REG_NEWLINE|REG_EXTENDED|REG_NOSUB)!=0) {
	gslog(LOG_EMERG, "Illegal regular expression %s\n",
		(gs_sp_t)(pattern->offset));
	return 0;
    }
    return (gs_param_handle_t) reg;
}

gs_uint32_t str_regex_match(vstring* str, gs_param_handle_t pattern_handle) {
    regex_t * reg = (regex_t *) pattern_handle ;
    gs_int32_t res;
    static gs_sp_t d=0;
    static gs_uint32_t dlen=0;
    // grow our static buffer to the longest string we ever see
    if ((str->length+1) >= dlen) {
        if (d!=0) free((void*)d);
        dlen=0;
        d=0;
        if ((d=(gs_sp_t)malloc(str->length+1))==0) return 0;
        dlen=str->length+1;
    }
    
    if (str->length==0) return 0;
    
    // copy the string and 0 terminate it
    memcpy((void *)d,(void *) str->offset, str->length);
    d[str->length]=0;
    
    res = REG_NOMATCH;
    res = regexec(reg, d, 0, NULL, 0);
    return (res==REG_NOMATCH)?0:1;
}

gs_retval_t deregister_handle_for_str_regex_match_slot_1(gs_param_handle_t handle) {
    regex_t * x = (regex_t *) handle;
    regfree(x);
    if (x!=0) free(x);
    return 0;
}

gs_param_handle_t register_handle_for_str_partial_regex_match_slot_1(vstring* pattern) {
    regex_t * reg;
    gs_int32_t res;

    if ((reg=(regex_t *) malloc(sizeof(regex_t)))==0)  {
	gslog(LOG_EMERG, "No memory for regular expression %s\n",
		(gs_sp_t)(pattern->offset));
	return 0;
    }

    if (regcomp(reg,(gs_sp_t)(pattern->offset), REG_NEWLINE|REG_EXTENDED|REG_NOSUB)!=0) {
	gslog(LOG_EMERG, "Illegal regular expression %s\n",
		(gs_sp_t)(pattern->offset));
	return 0;
    }
    return (gs_param_handle_t) reg;
}

gs_uint32_t str_partial_regex_match(vstring* str, gs_param_handle_t pattern_handle,
			     uint maxlen) {
    regex_t * reg = (regex_t *) pattern_handle ;
    gs_int32_t res;
    gs_int32_t end;
    static gs_sp_t d=0;
    static gs_uint32_t dlen=0;
    // grow our static buffer to the longest string we ever see
    if ((str->length+1) >= dlen) {
        if (d!=0) free((void*)d);
        dlen=0;
        d=0;
        if ((d=(gs_sp_t)malloc(str->length+1))==0) return 0;
        dlen=str->length+1;
    }
    
    if (str->length==0) return 0;
    
    end=(maxlen>(str->length))?(str->length):maxlen;
    
    // copy the string and 0 terminate it
    memcpy((void *)d,(void *) str->offset, end);
    d[end]=0;
 
    res = REG_NOMATCH;
    res = regexec(reg, d,0, NULL, 0);
    return (res==REG_NOMATCH)?0:1;
}


gs_retval_t deregister_handle_for_str_partial_regex_match_slot_1(
					     gs_param_handle_t handle) {
    regex_t * x = (regex_t *) handle;
    regfree(x);
    if (x!=0) free(x);
    return 0;
}

gs_param_handle_t register_handle_for_str_extract_regex_slot_1(vstring* pattern) {
    regex_t * reg;
    
    if ((reg=(regex_t *) malloc(sizeof(regex_t)))==0)  {
        gslog(LOG_EMERG, "No memory for regular expression %s\n",
              (gs_sp_t)(pattern->offset));
        return 0;
    }
    if (regcomp(reg,(gs_sp_t)(pattern->offset), REG_EXTENDED)!=0) {
        gslog(LOG_EMERG, "Illegal regular expression %s\n",
              (gs_sp_t)(pattern->offset));
        return 0;
    }
    return (gs_param_handle_t) reg;
}


/* partial function return 0 if the value is valid */
gs_retval_t str_extract_regex( vstring * result, vstring * str, gs_param_handle_t handle) {
    regex_t * reg = (regex_t *) handle ;
    gs_sp_t source = (gs_sp_t)(str->offset);
    gs_retval_t res;
    regmatch_t match;
    static gs_sp_t d=0;
    static gs_uint32_t dlen=0;
    // grow our static buffer to the longest string we ever see
    if ((str->length+1) >= dlen) {
        if (d!=0) free((void*)d);
        dlen=0;
        d=0;
        if ((d=(gs_sp_t)malloc(str->length+1))==0) return 1;
        dlen=str->length+1;
    }
    
    if (str->length==0) return 1;
    
    // copy the string and 0 terminate it
    memcpy((void *)d,(void *) str->offset, str->length);
    d[str->length]=0;

    res = REG_NOMATCH;
    res = regexec(reg, d, 1, &match, 0);
    if (res==REG_NOMATCH) return 1;
    result->offset= (gs_p_t) &source[match.rm_so];
    result->length=match.rm_eo-match.rm_so;
    result->reserved = SHALLOW_COPY;
    return 0;
}

gs_retval_t deregister_handle_for_str_extract_regex_slot_1(gs_param_handle_t handle) {
    regex_t * x = (regex_t *) handle;
    regfree(x);
    if (x!=0) free(x);
    return 0;
}

// -------------------------------------------------
//		More substring functions

//	 get last n bytes, if available
//	 getting the prefix is done by str_truncate, defined in the include file
gs_retval_t str_suffix(vstring *result,  vstring *s, gs_uint32_t n){
  register gs_p_t st = (gs_p_t)s->offset; 
  int prefix = (n > s->length) ? 0 : s->length-n;  
  result->offset = st + prefix;
  result->length = s->length-prefix;
  result->reserved = SHALLOW_COPY;
  return 0;
}


//	Split the string on sep, get the i'th substring, if any
gs_retval_t get_list_entry(vstring *result, vstring *l,  vstring *sep, gs_uint32_t pos){
	char s;
	gs_int32_t c;

	result->offset = l->offset;	// empty return string
	result->reserved = SHALLOW_COPY;
	result->length = 0;

	if(sep->length > 0){	// get the sep char, ensure the string is nonempty
		s = ((gs_sp_t)(sep->offset))[0];
	}else{
		return 0;
	}

	for(c=0;c < l->length && pos>0; ++c){
		if(((gs_sp_t)(l->offset))[c] == s){
			pos--;
		}
	}

	if(pos>0 || c >= l->length-1){ // not enough seps, or final string is empty
		return 0;
	}
	
	result->offset = l->offset + c;
	for(; c<l->length && ((gs_sp_t)(l->offset))[c] != s; ++c, ++result->length);
	
	return 0;
}


// -------------------------------------------------

static gs_uint32_t nextint(struct vstring *str , gs_uint32_t * offset, gs_uint32_t *res) {
	gs_uint8_t * s = (gs_uint8_t *)(str->offset);
	int v = 0;
	*res = 0;
	while(*offset<str->length) {
		if ((s[*offset]>='0') && (s[*offset]<='9')) {
			v=1;
			*res= (*res*10) + (gs_uint32_t) (s[*offset]-'0');
		} else {
			if (v!=0) { // got some valid result
				return 1;
			} // otherwise skip leading grabage
		}
		(*offset)++;
 	}
	return v;
}


gs_uint32_t strtoi(gs_uint32_t * r, struct vstring * s)
{
	gs_uint32_t offset;
	offset=0;
	if (nextint(s,&offset,r)==0) return 1;
	return 0;
}

gs_param_handle_t register_handle_for_strtoi_c_slot_0(vstring* istr) {
	gs_uint32_t offset,r;
	offset=0;
	if (nextint(istr,&offset,&r)!=0)
		return (gs_param_handle_t) r;
	return (gs_param_handle_t) 0;
}
gs_retval_t deregister_handle_for_strtoi_c_slot_0(gs_param_handle_t h) {
	return 0;
}


gs_uint32_t strtoip(gs_uint32_t * r, struct vstring * s)
{
        gs_uint32_t ip1,ip2,ip3,ip4,offset;
        offset=0;
        if (nextint(s,&offset,&ip1)==0) return 1;
        //fprintf (stderr, "1 %u %u\n",ip1,offset);
        if (nextint(s,&offset,&ip2)==0) return 1;
        //fprintf (stderr, "2 %u %u\n",ip2,offset);
        if (nextint(s,&offset,&ip3)==0) return 1;
        //fprintf (stderr, "3 %u %u\n",ip3,offset);
        if (nextint(s,&offset,&ip4)==0) return 1;
        //fprintf (stderr, "4 %u %u\n",ip4,offset);
        *r=ip1<<24|ip2<<16|ip3<<8|ip4;
        return 0;
}

gs_param_handle_t register_handle_for_strtoip_c_slot_0(vstring* istr) {
        gs_uint32_t ip1,ip2,ip3,ip4,offset,r;
        offset=0;
        if (nextint(istr,&offset,&ip1)==0) return (gs_param_handle_t)0;
        if (nextint(istr,&offset,&ip2)==0) return (gs_param_handle_t)0;
        if (nextint(istr,&offset,&ip3)==0) return (gs_param_handle_t)0;
        if (nextint(istr,&offset,&ip4)==0) return (gs_param_handle_t)0;
        r=ip1<<24|ip2<<16|ip3<<8|ip4;
		return (gs_param_handle_t)r;
}
gs_retval_t deregister_handle_for_strtoip_c_slot_0(gs_param_handle_t h) {
	return 0;
}

gs_uint32_t partn_hash(  gs_uint32_t ip1, gs_uint32_t ip2) {
    return (ip1^ip2);
}

gs_uint32_t rand_hash() {
    return rand();
}

///////////////////////////////////////
//		IPv6 fcns.
//	return negative if s1 < s2, 0 if s1==s2, positive if s1>s2
gs_retval_t hfta_ipv6_compare(const hfta_ipv6_str &i1, const hfta_ipv6_str &i2) {
    if(i1.v[0] > i2.v[0])
        return 1;
    if(i1.v[0] < i2.v[0])
        return -1;
    if(i1.v[1] > i2.v[1])
        return 1;
    if(i1.v[1] < i2.v[1])
        return -1;
    if(i1.v[2] > i2.v[2])
        return 1;
    if(i1.v[2] < i2.v[2])
        return -1;
    if(i1.v[3] > i2.v[3])
        return 1;
    if(i1.v[3] < i2.v[3])
        return -1;

    return 0;
}

hfta_ipv6_str And_Ipv6(const hfta_ipv6_str &i1, const hfta_ipv6_str &i2){
	hfta_ipv6_str ret;
	ret.v[0] = i1.v[0] & i2.v[0];
	ret.v[1] = i1.v[1] & i2.v[1];
	ret.v[2] = i1.v[2] & i2.v[2];
	ret.v[3] = i1.v[3] & i2.v[3];
	return ret;
}

hfta_ipv6_str Or_Ipv6(const hfta_ipv6_str &i1, const hfta_ipv6_str &i2){
	hfta_ipv6_str ret;
	ret.v[0] = i1.v[0] | i2.v[0];
	ret.v[1] = i1.v[1] | i2.v[1];
	ret.v[2] = i1.v[2] | i2.v[2];
	ret.v[3] = i1.v[3] | i2.v[3];
	return ret;
}

gs_uint32_t hfta_ipv6_hashfunc(const hfta_ipv6_str *s) {
	return s->v[0] ^ s->v[1] ^ s->v[2] ^ s->v[3];
}

hfta_ipv6_str hton_ipv6(hfta_ipv6_str s){
	hfta_ipv6_str ret;

//	ret.v[0] = htonl(s.v[0]);
//	ret.v[1] = htonl(s.v[1]);
//	ret.v[2] = htonl(s.v[2]);
//	ret.v[3] = htonl(s.v[3]);
	ret.v[0] = s.v[0];
	ret.v[1] = s.v[1];
	ret.v[2] = s.v[2];
	ret.v[3] = s.v[3];
	return ret;
}

hfta_ipv6_str ntoh_ipv6(hfta_ipv6_str s){
	hfta_ipv6_str ret;
//	ret.v[0] = ntohl(s.v[0]);
//	ret.v[1] = ntohl(s.v[1]);
//	ret.v[2] = ntohl(s.v[2]);
//	ret.v[3] = ntohl(s.v[3]);
	ret.v[0] = s.v[0];
	ret.v[1] = s.v[1];
	ret.v[2] = s.v[2];
	ret.v[3] = s.v[3];
	return ret;
}

int HFTA_Ipv6_Constructor(hfta_ipv6_str *s, gs_csp_t l) {
        gs_uint32_t i0=0,i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0;
        sscanf(l,"%x:%x:%x:%x:%x:%x:%x:%x",&i0,&i1,&i2,&i3,&i4,&i5,&i6,&i7);
        s->v[0] = ((i0 & 0xffff) << 16) | (i1 & 0xffff);
        s->v[1] = ((i2 & 0xffff) << 16) | (i3 & 0xffff);
        s->v[2] = ((i4 & 0xffff) << 16) | (i5 & 0xffff);
        s->v[3] = ((i6 & 0xffff) << 16) | (i7 & 0xffff);
    return(0);
}

gs_retval_t str_exists_substr(vstring * s1,vstring * s2)
{
  gs_uint8_t *st1 = (gs_uint8_t *)s1->offset;
  gs_uint8_t *st2 = (gs_uint8_t *)s2->offset;
  gs_uint8_t *s2f = (gs_uint8_t *)s2->offset;
  gs_uint8_t len1 = s1->length-s2->length;
  gs_uint8_t len2 = s2->length;
  gs_uint8_t x,y;

  for (x=0; x<len1 ; x++)
  {
      if (st1[x]== *s2f)
	{
	  for (y=0; y<len2 && st1[x+y]==st2[y];y++);
	  if (y==len2)
	      return 1;
	}
  }
  return 0;
}

gs_retval_t str_compare(vstring *s1,vstring *s2)
{
  return hfta_vstr_compare(s1,s2);
}

gs_uint32_t str_match_offset( gs_uint32_t offset, vstring *s1, vstring *s2)
{
  gs_uint8_t *st1 = (gs_uint8_t *)s1->offset;
  gs_uint8_t *st2 = &(((gs_uint8_t *)s2->offset)[offset]);
  gs_int32_t x;
  gs_int32_t len2 = s2->length-offset;
  gs_int32_t len1 = s1->length;

  if (len2 < len1)
    return 0;

  for(x = 0; x < len1; x++)
    {
      if (st1[x] != st2[x])
	return 0;
    }
  return 1;
}

gs_uint32_t byte_match_offset( gs_uint32_t offset, gs_uint32_t val,vstring *s2)
{
  gs_uint8_t *st2 = (gs_uint8_t *)s2->offset;
  gs_uint8_t v = (unsigned char) val;

//  if ((s2->length <= offset)||(offset<0))
  if (s2->length <= offset)
      return 0;

  return (st2[offset]==v)?1:0;
}


// -------------------------------------------------------
//		map_int_to_string and its support functions, structs

struct int_to_string_map_struct{
	std::map<gs_int64_t, vstring> i2s_map;
	std::string fname;
	vstring empty_string;
};

gs_param_handle_t register_handle_for_int_to_string_map_slot_1(vstring *filename){
	int_to_string_map_struct *map_struct;

	map_struct = new int_to_string_map_struct();
	if(map_struct == NULL){
		gslog(LOG_EMERG, "int_to_string_map:: Could not allocate handle memory\n");
		return 0;
	}

	map_struct->empty_string.offset = (gs_p_t)malloc(1);
	map_struct->empty_string.reserved = INTERNAL;
	map_struct->empty_string.length = 0;

	gs_sp_t filenamec;
	filenamec = (gs_sp_t)alloca(filename->length+1);
	if (filenamec==0) {
		gslog(LOG_EMERG, "int_to_string_map:: Could not allocate filename memory\n");
		return 0;
	}
	memcpy(filenamec,(gs_sp_t)filename->offset,filename->length);
	filenamec[filename->length]=0;	
	map_struct->fname = filenamec;

	FILE *fl = fopen(filenamec, "r");
	if(fl==NULL){
		gslog(LOG_EMERG, "int_to_string_map:: Could not open regex file %s \n",filename);
		return 0;
	}
	
	gs_int32_t buflen = 10000;
	char buf[buflen], buf_str[buflen];
	gs_int64_t val;
	char *fret;
	fret = fgets(buf, buflen, fl);
	while(fret != NULL){
		int nvals = sscanf(buf, "%lld,%s", &val, buf_str);
		if(nvals >= 2){
			vstring new_str;
			new_str.reserved = SHALLOW_COPY;
			new_str.length = strlen(buf_str);
			new_str.offset = (gs_p_t)malloc(new_str.length);
			memcpy((char *)new_str.offset, buf_str, new_str.length);
			map_struct->i2s_map[val] = new_str;
		}
		fret = fgets(buf, buflen, fl);
	}

	fclose(fl);

	return (gs_param_handle_t) map_struct;
}

gs_retval_t int_to_string_map(vstring *result, gs_int64_t val, gs_param_handle_t handle){
	int_to_string_map_struct *map_struct = (int_to_string_map_struct *)handle;
	if(map_struct->i2s_map.count(val)>0){
		vstring ret = map_struct->i2s_map[val];
		result->offset = ret.offset;
		result->reserved = ret.reserved;
		result->length = ret.length;
	}else{
		result->offset = map_struct->empty_string.offset;
		result->reserved = map_struct->empty_string.reserved;
		result->length = map_struct->empty_string.length;
	}

	return 0;
}

gs_param_handle_t deregister_handle_for_int_to_string_map_slot_1(gs_param_handle_t handle){
	int_to_string_map_struct *map_struct = (int_to_string_map_struct *)handle;
	for(std::map<gs_int64_t, vstring>::iterator i2si = map_struct->i2s_map.begin(); i2si!=map_struct->i2s_map.end(); ++i2si){
		free((void *)((*i2si).second.offset));
	}
	free((void *)(map_struct->empty_string.offset));
	delete map_struct;
}

// ---------------------------------------------------
//		Return a (binary, non-ascii) string in its hex representation

static char hexmap[16] = {
  '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'
};

gs_retval_t to_hex_string(vstring *result, vstring *val){
	result->length = 2*(val->length);
	result->offset = (gs_p_t)malloc(result->length);
	result->reserved = INTERNAL;
	unsigned char *rs = (unsigned char *)(result->offset);
	unsigned char *vs = (unsigned char *)(val->offset);

	for(int c=0;c<val->length; ++c){
		rs[2*c] = hexmap[vs[c] >> 4];
		rs[2*c+1] = hexmap[vs[c] & 0x0f];
	}

	return 0;
}


// ---------------------------------------------
//		sum up unsigned integers expressed as a string with separators,
//		e.g. on input '34|45|56' and sep '|', return 135.
//		This kind of thing is common in Nokia PCMD data.
// gracefully handle empty entries, e.g. '|8|' should return 8
gs_int64_t sum_uint_in_list(struct vstring *list, struct vstring *sepchar){
	gs_int64_t ret = 0;
	gs_int64_t val = 0;
	char sep;
	char v;
	int c;

	if(sepchar->length < 1)
		return 0;
	sep = ((char *)(sepchar->offset))[0];

	for(c=0;c<list->length;++c){
		v = ((char *)(list->offset))[c];
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
gs_int64_t to_llong(vstring *v){
	gs_int64_t ret=0;
	gs_uint8_t d;
	int c;
	int neg=1;

	if(v->length < 1)
		return 0;
	d = ((char *)(v->offset))[0];
	if(d=='-'){
		neg=-1;
	}else{
		ret = (d>='0' && d<='9')*(d-'0');
	}

	for(c=1;c<v->length;++c){
		d = ((char *)(v->offset))[c];
		ret = 10*ret+(d>='0' && d<='9')*(d-'0');
	}

	return neg*ret;
}

