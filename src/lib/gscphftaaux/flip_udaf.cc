#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "hfta_udaf.h"

#include <algorithm>    // std::sort 

#include<iostream>

#include "udaf_common.h"
//#define QUANT_LFTA1_SIZE 729
//#define QUANT_LFTA2_SIZE 181
//#define QUANT_LFTA3_SIZE 50		
//#define QUANT_EPS 0.01
//#define SKIPDIR_SIZE 100
//#define SKIPDIR_HEIGHT_MAX 7


//#define max(a,b) ((a) > (b) ? (a) : (b))

using namespace std;

// current use
//	hfta_only: quant_udaf_hfta0 
//	extraction: extr_quant_hfta0_fcn extr_med_hfta0_fcn extr_quant_hfta0_space 
//	lfta/hfta: quant_udaf_lfta3 quant_udaf_hfta3

// TODO
//		- Should the hfta part of the hfta/lfta split (hfta3)
//		  match the hfta-only implementation (hftaZ)?
//		- On out-of-space conditions, try a compress before
//		  discarding the sample.  If that happens, can the rate
//		  of compresses be decreased?
//		- Can the lfta part be made to work with actual compression?
//		  if not, change the implementation to gather a collection
//		  of samples, then send them up.  This should decrease
//		  lfta space use and reduce the cost of adding to the hfta.

/****************************************************************/
/* Data Structures						*/
/****************************************************************/


/****************************************************************/
template <class T> struct tuple_t {
	T val;
	gs_uint32_t gap;
	gs_uint32_t del;
	gs_uint32_t next;
};

template <class T> struct skipnode_t {
	T val;
	gs_uint32_t next;
	gs_uint32_t down;
};

template <class T> struct skipdir_t {
	gs_uint32_t height;				// height of tree
	gs_uint32_t freeptr;				// cursor space stack
	gs_uint32_t headptr[SKIPDIR_HEIGHT_MAX];	// ptrs to levels
	skipnode_t<T> list[SKIPDIR_SIZE+1];
};

/****************************************************************/




template <class T> struct quant_udaf_lfta3_struct_t {
	gs_uint32_t nelts;
	gs_uint32_t freeptr;
	gs_uint32_t usedptr;
	gs_uint32_t circptr;
	gs_uint32_t size;
	tuple_t<T> t[QUANT_LFTA3_SIZE+1];
	skipdir_t<T> sd;
};


template <class T> struct supertuple3_t{	// hfta/lfta
	T val;
	gs_uint32_t gap;
	gs_uint32_t del;
	struct supertuple3_t<T> *next;
};

template <class T> struct supertupleZ_t{
	T val;
	gs_uint32_t gap;
	gs_uint32_t del;
	gs_int32_t next;
};


template <class T> struct quant_udaf_hfta_struct_t {
	gs_uint32_t nelts;		// 4 bytes
	short int used_head;
	short int free_head;
	supertupleZ_t<T> *st;
	gs_uint32_t *vals;
	supertuple3_t<T> *t;		// 8 bytes
};






/*************************** Version 3 **************************/
/* Version 3: LFTA-medium					*/
/****************************************************************/
template <class T> void quant_hfta3_print(quant_udaf_hfta_struct_t<T> *s)
{
        supertuple3_t<T> *t;

//printf("In quant_hfta3_print, s=%llx, t=%llx\n",(unsigned long long int)s,(unsigned long long int)(s->t));
	gslog(LOG_DEBUG,"HFTA tuples:\n");
        for (t=s->t; t != NULL; t=t->next) {
                gslog(LOG_DEBUG,"(%u, %u, %u)\n",t->val,t->gap,t->del);
        }
}

template <class T> void quant_hfta3_compress(quant_udaf_hfta_struct_t<T> *s)
{
	supertuple3_t<T> *t=s->t, *d;
	gs_uint32_t threshold;

	threshold = (gs_uint32_t)ceil((2.0 * QUANT_EPS) * (float)(s->nelts));
	if ((t == NULL) || (t->next == NULL)) return;
	d = t->next;
	while ((d != NULL) && (d->next != NULL)) {
		if (d->gap+d->next->gap+d->next->del < threshold) {
			d->next->gap += d->gap;
			t->next = d->next;
			free(d);
		}
		t = t->next;
		d = t->next;
	}
}


/****************************************************************/
/* HFTA3 functions						*/
/****************************************************************/

//		since it does mallocs instead of allocations in a fixed block of memory
template <class T> void quant_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b) {
//printf("sizeof quant_udaf_hfta_struct_t<T> is %lu\n",sizeof(quant_udaf_hfta_struct_t<T>));
//printf("sizeof quant_udaf_lfta3_struct_t<T> is %lu\n",sizeof(quant_udaf_lfta3_struct_t<T>));
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
//printf("quant_udaf_hfta3_HFTA_AGGR_INIT_ size is %lu\n",sizeof(quant_udaf_hfta_struct_t<T>));
	s->nelts = 0;
	s->t = NULL;
	s->vals = NULL;
	s->st = NULL;
	s->used_head = -1;
	s->free_head = -1;
}

void quant_ui_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b){
	quant_udaf_hfta3_HFTA_AGGR_INIT_<gs_uint32_t>(b);
}
void quant_i_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b){
	quant_udaf_hfta3_HFTA_AGGR_INIT_<gs_int32_t>(b);
}
void quant_ul_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b){
	quant_udaf_hfta3_HFTA_AGGR_INIT_<gs_uint64_t>(b);
}
void quant_l_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b){
	quant_udaf_hfta3_HFTA_AGGR_INIT_<gs_int64_t>(b);
}
void quant_f_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b){
	quant_udaf_hfta3_HFTA_AGGR_INIT_<gs_float_t>(b);
}

template <class T> void quant_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v) {
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
	quant_udaf_lfta3_struct_t<T> *vs = (quant_udaf_lfta3_struct_t<T> *)(v->offset);
	supertuple3_t<T> *t=s->t, *tprev=NULL;
	tuple_t<T> *u=vs->t;
	supertuple3_t<T> *newptr;
	gs_uint32_t uptr = vs->usedptr;
	gs_uint32_t threshold;

	if (uptr == 0) return;
	//if (v->length != sizeof(quant_udaf_lfta3_struct_t)) return;

	threshold = (gs_uint32_t)ceil((2.0 * QUANT_EPS) * (float)(vs->nelts));
	while (uptr != 0) {
//printf("uptr=%d\n",uptr);
		if ((u[uptr].next != 0) && (u[uptr].gap+u[u[uptr].next].gap+u[u[uptr].next].del < threshold)) {
			u[u[uptr].next].gap += u[uptr].gap;
		}
		else {
			// find position in superstructure
			while ((t != NULL) && (t->val <= u[uptr].val)) {
				if (t->val == u[uptr].val) {
					t->gap += u[uptr].gap;
					t->del += u[uptr].del;
					uptr = u[uptr].next;
					if (!uptr) break;
				}
				else {
					t->del += u[uptr].gap+u[uptr].del-1;
				}
				tprev = t;
				t = t->next;
			}
			if (!uptr) break;
			// create newptr node
			newptr = (supertuple3_t<T> *)malloc(sizeof(supertuple3_t<T>));
			newptr->val = u[uptr].val;
			newptr->gap = u[uptr].gap;
			newptr->del = u[uptr].del;
			if (t != NULL)
				newptr->del += t->gap + t->del - 1;
			// merge into superstructure
			newptr->next = t;
			if (tprev == NULL)
				s->t = newptr;
			else
				tprev->next = newptr;
			tprev = newptr;
			s->nelts += u[uptr].gap;
		}
		uptr = u[uptr].next;
	}
	quant_hfta3_compress<T>(s);
//quant_hfta3_print(s);
//printf("exiting quant_udaf_hfta3_HFTA_AGGR_UPDATE_, s=%llx, t=%llx\n",(unsigned long long int)s,(unsigned long long int)(s->t));
}

void quant_ui_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v){
	quant_udaf_hfta3_HFTA_AGGR_UPDATE_<gs_uint32_t>(b, v);
}
void quant_i_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v){
	quant_udaf_hfta3_HFTA_AGGR_UPDATE_<gs_int32_t>(b, v);
}
void quant_ul_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v){
	quant_udaf_hfta3_HFTA_AGGR_UPDATE_<gs_uint64_t>(b, v);
}
void quant_l_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v){
	quant_udaf_hfta3_HFTA_AGGR_UPDATE_<gs_int64_t>(b, v);
}
void quant_f_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v){
	quant_udaf_hfta3_HFTA_AGGR_UPDATE_<gs_float_t>(b, v);
}

template <class T> void quant_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	r->length = sizeof(quant_udaf_hfta_struct_t<T>);
	r->offset = (gs_p_t )b;
	r->reserved = SHALLOW_COPY;

	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
//printf("In quant_udaf_hfta3_HFTA_AGGR_OUTPUT_, s=%llx, t=%llx\n\n",(unsigned long long int)s,(unsigned long long int)(s->t));
}

void quant_ui_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_OUTPUT_<gs_uint32_t>(r, b);
}
void quant_i_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_OUTPUT_<gs_int32_t>(r, b);
}
void quant_ul_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_OUTPUT_<gs_uint64_t>(r, b);
}
void quant_l_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_OUTPUT_<gs_int64_t>(r, b);
}
void quant_f_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_OUTPUT_<gs_float_t>(r, b);
}

template <class T> void quant_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b) {
    quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
	supertuple3_t<T> *t=s->t, *n;
	while(t){
		n=t->next;
		free(t);
		t=n;
	}
	return;
}

void quant_ui_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_DESTROY_<gs_uint32_t>(b);
}
void quant_i_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_DESTROY_<gs_int32_t>(b);
}
void quant_ul_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_DESTROY_<gs_uint64_t>(b);
}
void quant_l_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_DESTROY_<gs_int64_t>(b);
}
void quant_f_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b) {
	quant_udaf_hfta3_HFTA_AGGR_DESTROY_<gs_float_t>(b);
}

/****************************************************************/
/* HFTA3 Extraction functions					*/
/****************************************************************/
template <class T> T extr_quant_hfta3_fcn(vstring *v, gs_float_t  phi) {
	quant_udaf_hfta_struct_t<T> *vs = (quant_udaf_hfta_struct_t<T> *)(v->offset);
	supertuple3_t<T> *t, *p;
	gs_uint32_t nelts=0;
	gs_int32_t rmin=0, rmax, rank, ropt=INT_MAX;
	gs_uint32_t count=0;

	for (t=vs->t; t != NULL; t=t->next) {
		nelts += t->gap;
		count++;
	}
	rank = (gs_int32_t) (phi*(float)nelts);

	for (t=vs->t; t != NULL; t=t->next) {
		rmin += t->gap;
		rmax = rmin+t->del;
		if (max(abs(rmin-rank), abs(rmax-rank)) < ropt) {
			p = t;
			ropt = max(abs(rmin-rank), abs(rmax-rank));
		}
	}
	return p->val;
}

/*
gs_uint32_t extr_quant_ui_hfta3_fcn(vstring *v, gs_float_t  phi){
	return extr_quant_hfta3_fcn<gs_uint32_t>(v, phi);
}
gs_int32_t extr_quant_i_hfta3_fcn(vstring *v, gs_float_t  phi){
	return extr_quant_hfta3_fcn<gs_int32_t>(v, phi);
}
gs_uint64_t extr_quant_ul_hfta3_fcn(vstring *v, gs_float_t  phi){
	return extr_quant_hfta3_fcn<gs_uint64_t>(v, phi);
}
gs_int64_t extr_quant_l_hfta3_fcn(vstring *v, gs_float_t  phi){
	return extr_quant_hfta3_fcn<gs_int64_t>(v, phi);
}
gs_float_t extr_quant_f_hfta3_fcn(vstring *v, gs_float_t  phi){
	return extr_quant_hfta3_fcn<gs_float_t>(v, phi);
}
*/

template <class T> T extr_med_hfta3_fcn(vstring *v)
{
	return extr_quant_hfta3_fcn<T>(v, 0.5);
}

gs_uint32_t extr_ui_med_hfta3_fcn(vstring *v){
	return extr_med_hfta3_fcn<gs_uint32_t>(v);
}
gs_int32_t extr_i_med_hfta3_fcn(vstring *v){
	return extr_med_hfta3_fcn<gs_int32_t>(v);
}
gs_uint64_t extr_ul_med_hfta3_fcn(vstring *v){
	return extr_med_hfta3_fcn<gs_uint64_t>(v);
}
gs_int64_t extr_l_med_hfta3_fcn(vstring *v){
	return extr_med_hfta3_fcn<gs_int64_t>(v);
}
gs_float_t extr_f_med_hfta3_fcn(vstring *v){
	return extr_med_hfta3_fcn<gs_float_t>(v);
}

template <class T> gs_uint32_t extr_quant_hfta3_space(vstring *v)
{
	quant_udaf_hfta_struct_t<T> *vs = (quant_udaf_hfta_struct_t<T> *)(v->offset);
	supertuple3_t<T> *t;
	gs_uint32_t count=0;

	for (t=vs->t; t != NULL; t=t->next)
		count++;
	return count;
}



//////////////////////////////////////////////////////////////////////
//		 hfta-only code V3

//	This approach stores values in a buffer until
//	the buffer gets filled, and then puts the values into
//	the approximate quantile udaf.
//
//	Further, the code is templatized

#define MAX_QUANT_ELEMS 128
#define MAX_VAL_ELEMS 50
//	MAX_VAL_ELEMS must be less than MAX_QUANT_ELEMS,
//	and probably somewhat less than 1/QUANT_EPS
//	Another consideration is space use, as most groups are small,
//	so you want MAX_VAL_ELEMS to be as small as possible
//	and still capture most small groups.

//	To really optimize for space, use a doubling realloc
//	strategy until the doubled size would be 2K bytes,
//	and then instead of doubling, insert into the approx
//	structure.
//	

/*
template <class T> struct supertupleZ_t{
	T val;
	gs_uint32_t gap;
	gs_uint32_t del;
	gs_int32_t next;
};
*/

/*
template <class T> struct quant_udaf_hftaZ_struct_t{
	gs_uint32_t nelts;
	short int used_head;
	short int free_head;
	supertupleZ_t<T> *st;
	gs_uint32_t *vals;
};
*/


template <class T> void quant_udaf_hftaZ_compress(quant_udaf_hfta_struct_t<T> *s)
{
	int t = s->used_head, d, d_next=-1;
	gs_uint32_t threshold;
	supertupleZ_t<T> *st = s->st;

	threshold = (gs_uint32_t)ceil((2.0 * QUANT_EPS) * (float)(s->nelts));
	if ((t == -1) || (st[t].next == -1)) return;
	d = st[t].next;
	while ((d != -1) && (st[d].next != -1)) {
		d_next = st[d].next;
		if (st[d].gap + st[d_next].gap + st[d_next].del < threshold) {
			st[d_next].gap += st[d].gap;
			st[t].next = st[d].next;
			st[d].next = s->free_head;
			s->free_head = d;
		}
		t = st[t].next;
		d = st[t].next;
	}
}

template <class T>  void quant_udaf_hftaZ_HFTA_AGGR_INIT_(gs_sp_t b) {
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
//printf("quant_udaf_hftaZ_HFTA_AGGR_INIT_ size is %lu\n",sizeof(quant_udaf_hfta_struct_t<T>));
	s->nelts = 0;
	s->st=NULL;
	s->vals = (gs_uint32_t *)malloc(MAX_VAL_ELEMS*sizeof(T));
	s->t = NULL;
}

template <class T>  void quant_udaf_hftaZ_HFTA_AGGR_UPDATE_(gs_sp_t b, T v) {
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
	if(s->nelts<MAX_VAL_ELEMS){
		s->vals[s->nelts] = v;
		s->nelts++;
		return;
	}

	if(s->nelts==MAX_VAL_ELEMS){
//		qsort(s->vals, MAX_VAL_ELEMS, sizeof(gs_uint32_t), compare_gs_uint32);
		sort(s->vals,s->vals+s->nelts);
		s->st = (supertupleZ_t<T> *)malloc(MAX_QUANT_ELEMS*sizeof(quant_udaf_hfta_struct_t<T>));
		for(int i=0;i<MAX_VAL_ELEMS;++i){
			s->st[i].val = s->vals[i];
			s->st[i].gap = 1;
			s->st[i].del = 0;
			s->st[i].next = i+1;
		}
		s->st[MAX_VAL_ELEMS-1].next = -1;
		for(int i=MAX_VAL_ELEMS; i<MAX_QUANT_ELEMS; ++i){
			s->st[i].next = i+1;
		}
		s->st[MAX_QUANT_ELEMS-1].next = -1;
		s->free_head = MAX_VAL_ELEMS;
		s->used_head = 0;
		free(s->vals);
		s->vals = NULL;
	}

//		s->nelts > MAX_VAL_ELEMS
	int t=s->used_head;
	int newptr;
	gs_uint32_t threshold;
	gs_uint32_t val, gap;
	gs_uint32_t obj;
	supertupleZ_t<T> *st = s->st;

	s->nelts++;
	// left boundary case
	if ((t==-1) || (v <= st[t].val)) {
		newptr = s->free_head;
		if (newptr==-1) {
			gslog(LOG_ALERT, "Out of space in quant_udaf_hftaZ_HFTA_AGGR_UPDATE_.\n");
			cout << v << endl;
			quant_udaf_hftaZ_compress<T>(s);
			return;
		}
		s->free_head = st[newptr].next;
		st[newptr].val = v;
		st[newptr].gap = 1;
		st[newptr].del = 0;
		st[newptr].next = s->used_head;
		s->used_head = newptr;
		return;
	}

	// locate position that sandwiches v
	int ptr=t;
	while ((st[ptr].next!=-1) && (st[st[ptr].next].val < v))
		ptr = st[ptr].next;

	// right boundary case
	if (st[ptr].next==-1) {
		// create newptr node
		newptr = s->free_head;
		if (newptr==-1) {
			gslog(LOG_ALERT, "Out of space in quant_udaf_hftaZ_HFTA_AGGR_UPDATE_.\n");
			quant_udaf_hftaZ_compress<T>(s);
			return;
		}
		s->free_head = st[newptr].next;
		st[newptr].val = v;
		st[newptr].gap = 1;
		st[newptr].del = 0;
		st[newptr].next =-1;
		st[ptr].next = newptr;
	}
	// non-boundary case
	else {
		int nextptr = st[ptr].next;
		obj = st[ptr].gap + st[nextptr].gap + st[nextptr].del;
		threshold = (gs_uint32_t)ceil(2.0 * QUANT_EPS * (float)s->nelts);
		if (obj <= threshold) {
			// insert into existing bucket
			st[nextptr].gap++;
		}
		else {
			newptr = s->free_head;
			if (newptr==-1) {
				gslog(LOG_ALERT, "Out of space in quant_udaf_hftaZ_HFTA_AGGR_UPDATE_.\n");
				quant_udaf_hftaZ_compress<T>(s);
				return;
			}
			s->free_head = st[newptr].next;
			st[newptr].val = v;
			st[newptr].gap = 1;
			st[newptr].del = st[nextptr].gap + st[nextptr].del-1;
			st[newptr].next = st[ptr].next;
			st[ptr].next = newptr;
		}
	}
	if(s->nelts>100 && (s->nelts & 0x03)==0)
		quant_udaf_hftaZ_compress<T>(s);
}

template <class T>  void quant_udaf_hftaZ_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	r->length = sizeof(quant_udaf_hfta_struct_t<T>);
	r->offset = (gs_p_t )b;
	r->reserved = SHALLOW_COPY;
}

template <class T>  void quant_udaf_hftaZ_HFTA_AGGR_DESTROY_(gs_sp_t b){
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
	if(s->vals != NULL)
		free(s->vals);
	if(s->st)
		free(s->st);
}


template <class T> T extr_quant_hftaZ_fcn(vstring *v, gs_float_t phi) {
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)(v->offset);
	int t, p;

	if(s->t != NULL){	// separate path for hfta/lfta split
		return extr_quant_hfta3_fcn<T>(v, phi);
	}

	if(s->vals){
//		qsort(s->vals, s->nelts, sizeof(gs_uint32_t), compare_gs_uint32);
		sort(s->vals,s->vals+s->nelts);
		gs_int32_t rank = (gs_int32_t) (phi*(float)(s->nelts));
		if(rank>=s->nelts)
			rank=s->nelts-1;
		return s->vals[rank];
	}


	gs_int32_t rmin=0, rmax, rank, ropt=INT_MAX;
	gs_uint32_t count=0;
	supertupleZ_t<T> *st = s->st;

	rank = (gs_int32_t) (phi*(float)(s->nelts));

	for (t=s->used_head; t != -1; t=st[t].next) {
		rmin += st[t].gap;
		rmax = rmin+st[t].del;
		if (max(abs(rmin-rank), abs(rmax-rank)) < ropt) {
			p = t;
			ropt = max(abs(rmin-rank), abs(rmax-rank));
		} else break;
	}
	return st[p].val;
}
template <class T> T extr_med_hftaZ_fcn(vstring *v) {
	return extr_quant_hftaZ_fcn<T>(v, 0.5);
}


template <class T> int quant_udaf_hftaZ_nelem(gs_sp_t b) {
	quant_udaf_hfta_struct_t<T> *s = (quant_udaf_hfta_struct_t<T> *)b;
	supertupleZ_t<T> *st = s->st;

	if(s->vals != NULL)
		return s->nelts;

	int ctr=0;
	int t=s->used_head;
	while(t>=0){
		ctr++;
		t=st[t].next;
	}
	return ctr;
}

//	Unsigned int
void quant_ui_udaf_hftaZ_HFTA_AGGR_INIT_(gs_sp_t b){
	  quant_udaf_hftaZ_HFTA_AGGR_INIT_<gs_uint32_t>(b);
}
void quant_ui_udaf_hftaZ_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v){
	quant_udaf_hftaZ_HFTA_AGGR_UPDATE_<gs_uint32_t>(b,v);
}
void quant_ui_udaf_hftaZ_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hftaZ_HFTA_AGGR_OUTPUT_<gs_uint32_t>(r,b);
}
void quant_ui_udaf_hftaZ_HFTA_AGGR_DESTROY_(gs_sp_t b){
	quant_udaf_hftaZ_HFTA_AGGR_DESTROY_<gs_uint32_t>(b);
}
gs_uint32_t extr_quant_ui_hftaZ_fcn(vstring *v, gs_float_t phi) {
	return extr_quant_hftaZ_fcn<gs_uint32_t>(v,phi);
}
gs_uint32_t extr_med_ui_hftaZ_fcn(vstring *v){
	return extr_med_hftaZ_fcn<gs_uint32_t>(v);
}
int quant_ui_udaf_hftaZ_nelem(gs_sp_t b) {
	return quant_udaf_hftaZ_nelem<gs_uint32_t>(b);
}

//	int
void quant_i_udaf_hftaZ_HFTA_AGGR_INIT_(gs_sp_t b){
	  quant_udaf_hftaZ_HFTA_AGGR_INIT_<gs_int32_t>(b);
}
void quant_i_udaf_hftaZ_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_int32_t v){
	quant_udaf_hftaZ_HFTA_AGGR_UPDATE_<gs_int32_t>(b,v);
}
void quant_i_udaf_hftaZ_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hftaZ_HFTA_AGGR_OUTPUT_<gs_int32_t>(r,b);
}
void quant_i_udaf_hftaZ_HFTA_AGGR_DESTROY_(gs_sp_t b){
	quant_udaf_hftaZ_HFTA_AGGR_DESTROY_<gs_int32_t>(b);
}
gs_int32_t extr_quant_i_hftaZ_fcn(vstring *v, gs_float_t phi) {
	return extr_quant_hftaZ_fcn<gs_int32_t>(v,phi);
}
gs_int32_t extr_med_i_hftaZ_fcn(vstring *v){
	return extr_med_hftaZ_fcn<gs_int32_t>(v);
}
gs_int32_t quant_i_udaf_hftaZ_nelem(gs_sp_t b) {
	return quant_udaf_hftaZ_nelem<gs_int32_t>(b);
}

//	Unsigned long long int
void quant_ul_udaf_hftaZ_HFTA_AGGR_INIT_(gs_sp_t b){
	  quant_udaf_hftaZ_HFTA_AGGR_INIT_<gs_uint64_t>(b);
}
void quant_ul_udaf_hftaZ_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint64_t v){
	quant_udaf_hftaZ_HFTA_AGGR_UPDATE_<gs_uint64_t>(b,v);
}
void quant_ul_udaf_hftaZ_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hftaZ_HFTA_AGGR_OUTPUT_<gs_uint64_t>(r,b);
}
void quant_ul_udaf_hftaZ_HFTA_AGGR_DESTROY_(gs_sp_t b){
	quant_udaf_hftaZ_HFTA_AGGR_DESTROY_<gs_uint64_t>(b);
}
gs_uint64_t extr_quant_ul_hftaZ_fcn(vstring *v, gs_float_t phi) {
	return extr_quant_hftaZ_fcn<gs_uint64_t>(v,phi);
}
gs_uint64_t extr_med_ul_hftaZ_fcn(vstring *v){
	return extr_med_hftaZ_fcn<gs_uint64_t>(v);
}
int quant_ul_udaf_hftaZ_nelem(gs_sp_t b) {
	return quant_udaf_hftaZ_nelem<gs_uint64_t>(b);
}

//	long long int
void quant_l_udaf_hftaZ_HFTA_AGGR_INIT_(gs_sp_t b){
	  quant_udaf_hftaZ_HFTA_AGGR_INIT_<gs_int64_t>(b);
}
void quant_l_udaf_hftaZ_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_int64_t v){
	quant_udaf_hftaZ_HFTA_AGGR_UPDATE_<gs_int64_t>(b,v);
}
void quant_l_udaf_hftaZ_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hftaZ_HFTA_AGGR_OUTPUT_<gs_int64_t>(r,b);
}
void quant_l_udaf_hftaZ_HFTA_AGGR_DESTROY_(gs_sp_t b){
	quant_udaf_hftaZ_HFTA_AGGR_DESTROY_<gs_int64_t>(b);
}
gs_int64_t extr_quant_l_hftaZ_fcn(vstring *v, gs_float_t phi) {
	return extr_quant_hftaZ_fcn<gs_int64_t>(v,phi);
}
gs_int64_t extr_med_l_hftaZ_fcn(vstring *v){
	return extr_med_hftaZ_fcn<gs_int64_t>(v);
}
int quant_l_udaf_hftaZ_nelem(gs_sp_t b) {
	return quant_udaf_hftaZ_nelem<gs_int64_t>(b);
}


//	double
void quant_f_udaf_hftaZ_HFTA_AGGR_INIT_(gs_sp_t b){
	  quant_udaf_hftaZ_HFTA_AGGR_INIT_<gs_float_t>(b);
}
void quant_f_udaf_hftaZ_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_float_t v){
	quant_udaf_hftaZ_HFTA_AGGR_UPDATE_<gs_float_t>(b,v);
}
void quant_f_udaf_hftaZ_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b) {
	quant_udaf_hftaZ_HFTA_AGGR_OUTPUT_<gs_float_t>(r,b);
}
void quant_f_udaf_hftaZ_HFTA_AGGR_DESTROY_(gs_sp_t b){
	quant_udaf_hftaZ_HFTA_AGGR_DESTROY_<gs_float_t>(b);
}
gs_float_t extr_quant_f_hftaZ_fcn(vstring *v, gs_float_t phi) {
	return extr_quant_hftaZ_fcn<gs_float_t>(v,phi);
}
gs_float_t extr_med_f_hftaZ_fcn(vstring *v){
	return extr_med_hftaZ_fcn<gs_float_t>(v);
}
int quant_f_udaf_hftaZ_nelem(gs_sp_t b) {
	return quant_udaf_hftaZ_nelem<gs_float_t>(b);
}


