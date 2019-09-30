#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "hfta_udaf.h"

#define QUANT_LFTA1_SIZE 729
#define QUANT_LFTA2_SIZE 181
#define QUANT_LFTA3_SIZE 100

#define QUANT_EPS 0.01
#define SKIPDIR_SIZE 100
#define SKIPDIR_HEIGHT_MAX 7
#define max(a,b) ((a) > (b) ? (a) : (b))


/****************************************************************/
/* Data Structures						*/
/****************************************************************/
typedef struct tuple_t {
	gs_uint32_t val;
	gs_uint32_t gap;
	gs_uint32_t del;
	gs_uint32_t next;
} tuple_t;

typedef struct supertuple_t {
	gs_uint32_t val;
	gs_uint32_t gap;
	gs_uint32_t del;
	struct supertuple_t *next;
} supertuple_t;

/****************************************************************/
typedef gs_uint32_t val_type;

typedef struct skipnode {
	val_type val;
	gs_uint32_t next;
	gs_uint32_t down;
} skipnode_t;

typedef struct skipdir {
	gs_uint32_t height;				// height of tree
	gs_uint32_t freeptr;				// cursor space stack
	gs_uint32_t headptr[SKIPDIR_HEIGHT_MAX];	// ptrs to levels
	skipnode_t list[SKIPDIR_SIZE+1];
} skipdir_t;

/****************************************************************/

typedef struct quant_udaf_hfta0_struct_t {
	gs_uint32_t nelts;		// 4 bytes
	supertuple_t *t;		// 8 bytes
} quant_udaf_hfta0_struct_t;

typedef struct quant_udaf_lfta1_struct_t {
	gs_uint32_t nelts;
	gs_uint32_t samples[QUANT_LFTA1_SIZE];
} quant_udaf_lfta1_struct_t;

typedef struct quant_udaf_hfta1_struct_t {
	gs_uint32_t nelts;		// 4 bytes
	supertuple_t *t;		// 8 bytes
} quant_udaf_hfta1_struct_t;

typedef struct quant_udaf_lfta2_struct_t {
	gs_uint32_t nelts;
	gs_uint32_t freeptr;
	gs_uint32_t usedptr;
	tuple_t t[QUANT_LFTA2_SIZE+1];
} quant_udaf_lfta2_struct_t;

typedef struct quant_udaf_hfta2_struct_t {
	gs_uint32_t nelts;		// 4 bytes
	supertuple_t *t;		// 8 bytes
} quant_udaf_hfta2_struct_t;

typedef struct quant_udaf_lfta3_struct_t {
	gs_uint32_t nelts;
	gs_uint32_t freeptr;
	gs_uint32_t usedptr;
	gs_uint32_t circptr;
	gs_uint32_t size;
	tuple_t t[QUANT_LFTA3_SIZE+1];
	skipdir_t sd;
} quant_udaf_lfta3_struct_t;

typedef struct quant_udaf_hfta3_struct_t {
	gs_uint32_t nelts;		// 4 bytes
	supertuple_t *t;		// 8 bytes
} quant_udaf_hfta3_struct_t;



/*************************** Version 0 **************************/
/* Version 0: HFTA-only						*/
/****************************************************************/
void quant_udaf_hfta0_print(quant_udaf_hfta0_struct_t *s)
{
        supertuple_t *t;

	gslog(LOG_DEBUG,"hfta nelts = %u\n",s->nelts);
	gslog(LOG_DEBUG,"HFTA tuples:\n");
        for (t=s->t; t != NULL; t=t->next) {
                gslog(LOG_DEBUG,"(%u, %u, %u)\n",t->val,t->gap,t->del);
        }
}

void quant_udaf_hfta0_compress(quant_udaf_hfta0_struct_t *s)
{
	supertuple_t *t=s->t, *d;
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
/* HFTA0 functions						*/
/****************************************************************/
void quant_udaf_hfta0_HFTA_AGGR_INIT_(gs_sp_t b)
{
	quant_udaf_hfta0_struct_t *s = (quant_udaf_hfta0_struct_t *)b;
	s->nelts = 0;
	s->t = NULL;
}

void quant_udaf_hfta0_HFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v)
{
	quant_udaf_hfta0_struct_t *s = (quant_udaf_hfta0_struct_t *)b;
	supertuple_t *t=s->t;
	supertuple_t *newptr;
	gs_uint32_t threshold;
	gs_uint32_t val, gap;
	gs_uint32_t obj;

	s->nelts++;
	// left boundary case
	if ((!t) || (v <= t->val)) {
		newptr = (supertuple_t *)malloc(sizeof(supertuple_t));
		if (!newptr) {
			gslog(LOG_ALERT, "Out of space.\n");
			return;
		}
		newptr->val = v;
		newptr->gap = 1;
		newptr->del = 0;
		newptr->next = s->t;
		s->t = newptr;
		return;
	}

	// locate position that sandwiches v
	while ((t->next) && (t->next->val < v))
		t = t->next;

	// right boundary case
	if (!t->next) {
		// create newptr node
		newptr = (supertuple_t *)malloc(sizeof(supertuple_t));
		newptr->val = v;
		newptr->gap = 1;
		newptr->del = 0;
		newptr->next = NULL;
		t->next = newptr;
	}
	// non-boundary case
	else {
		obj = t->gap+t->next->gap+t->next->del;
		threshold = (gs_uint32_t)ceil(2.0 * QUANT_EPS * (float)s->nelts);
		if (obj <= threshold) {
			// insert into existing bucket
			t->next->gap++;
		}
		else {
			newptr = (supertuple_t *)malloc(sizeof(supertuple_t));
			newptr->val = v;
			newptr->gap = 1;
			newptr->del = t->next->gap+t->next->del-1;
			newptr->next = t->next;
			t->next = newptr;
		}
	}
	quant_udaf_hfta0_compress(s);
}

void quant_udaf_hfta0_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b)
{
	r->length = sizeof(quant_udaf_hfta0_struct_t);
	r->offset = (gs_p_t )b;
	r->reserved = SHALLOW_COPY;
}

void quant_udaf_hfta0_HFTA_AGGR_DESTROY_(gs_sp_t b)
{
        quant_udaf_hfta0_struct_t *s = (quant_udaf_hfta0_struct_t *)b;
	supertuple_t *t=s->t, *n;
	while(t){
		n=t->next;
		free(t);
		t=n;
	}

	return;
}


/****************************************************************/
/* HFTA0 Extraction functions					*/
/****************************************************************/
gs_uint32_t extr_quant_hfta0_fcn(vstring *v, gs_float_t phi)
{
//printf("In extr_quant_hfta0_fcn offset=%llx length=%d\n",v->offset, v->length);
	quant_udaf_hfta0_struct_t *vs = (quant_udaf_hfta0_struct_t *)(v->offset);
//printf("nelts=%d t=%llx\n",vs->nelts, (unsigned long long int)(vs->t));
	supertuple_t *t, *p;
	gs_uint32_t nelts=0;
	gs_uint32_t rmin=0, rmax, rank, ropt=UINT_MAX;
	gs_uint32_t count=0;

	for (t=vs->t; t != NULL; t=t->next) {
//printf("in loop.\n");
//printf("gap is %d\n",t->gap);
		nelts += t->gap;
		count++;
	}
	rank = (gs_uint32_t) (phi*(float)nelts);

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

gs_uint32_t extr_med_hfta0_fcn(vstring *v)
{
	return extr_quant_hfta0_fcn(v, 0.5);
}

gs_uint32_t extr_quant_hfta0_space(vstring *v)
{
	quant_udaf_hfta0_struct_t *vs = (quant_udaf_hfta0_struct_t *)(v->offset);
	supertuple_t *t;
	gs_uint32_t count=0;

	for (t=vs->t; t != NULL; t=t->next)
		count++;
	return count;
}


/*************************** Version 3 **************************/
/* Version 3: LFTA-medium					*/
/****************************************************************/
void quant_hfta3_print(quant_udaf_hfta3_struct_t *s)
{
        supertuple_t *t;

//printf("In quant_hfta3_print, s=%llx, t=%llx\n",(unsigned long long int)s,(unsigned long long int)(s->t));
	gslog(LOG_DEBUG,"HFTA tuples:\n");
        for (t=s->t; t != NULL; t=t->next) {
                gslog(LOG_DEBUG,"(%u, %u, %u)\n",t->val,t->gap,t->del);
        }
}

void quant_hfta3_compress(quant_udaf_hfta3_struct_t *s)
{
	supertuple_t *t=s->t, *d;
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
void quant_udaf_hfta3_HFTA_AGGR_INIT_(gs_sp_t b)
{
	quant_udaf_hfta3_struct_t *s = (quant_udaf_hfta3_struct_t *)b;
	s->nelts = 0;
	s->t = NULL;
}

void quant_udaf_hfta3_HFTA_AGGR_UPDATE_(gs_sp_t b, vstring *v)
{
	quant_udaf_hfta3_struct_t *s = (quant_udaf_hfta3_struct_t *)b;
	quant_udaf_lfta3_struct_t *vs = (quant_udaf_lfta3_struct_t *)(v->offset);
	supertuple_t *t=s->t, *tprev=NULL;
	tuple_t *u=vs->t;
	supertuple_t *newptr;
	gs_uint32_t uptr = vs->usedptr;
	gs_uint32_t threshold;

	if (uptr == 0) return;
	//if (v->length != sizeof(quant_udaf_lfta3_struct_t)) return;

	threshold = (gs_uint32_t)ceil((2.0 * QUANT_EPS) * (float)(vs->nelts));
	while (uptr != 0) {
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
			newptr = (supertuple_t *)malloc(sizeof(supertuple_t));
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
	quant_hfta3_compress(s);
//quant_hfta3_print(s);
//printf("exiting quant_udaf_hfta3_HFTA_AGGR_UPDATE_, s=%llx, t=%llx\n",(unsigned long long int)s,(unsigned long long int)(s->t));
}

void quant_udaf_hfta3_HFTA_AGGR_OUTPUT_(vstring *r, gs_sp_t b)
{
	r->length = sizeof(quant_udaf_hfta3_struct_t);
	r->offset = (gs_p_t )b;
	r->reserved = SHALLOW_COPY;

	quant_udaf_hfta3_struct_t *s = (quant_udaf_hfta3_struct_t *)b;
//printf("In quant_udaf_hfta3_HFTA_AGGR_OUTPUT_, s=%llx, t=%llx\n\n",(unsigned long long int)s,(unsigned long long int)(s->t));
}

void quant_udaf_hfta3_HFTA_AGGR_DESTROY_(gs_sp_t b)
{
	return;
}

/****************************************************************/
/* HFTA3 Extraction functions					*/
/****************************************************************/
gs_uint32_t extr_quant_hfta3_fcn(vstring *v, gs_float_t  phi)
{
	quant_udaf_hfta3_struct_t *vs = (quant_udaf_hfta3_struct_t *)(v->offset);
	supertuple_t *t, *p;
	gs_uint32_t nelts=0;
	gs_uint32_t rmin=0, rmax, rank, ropt=UINT_MAX;
	gs_uint32_t count=0;

	for (t=vs->t; t != NULL; t=t->next) {
		nelts += t->gap;
		count++;
	}
	rank = (gs_uint32_t) (phi*(float)nelts);

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

gs_uint32_t extr_med_hfta3_fcn(vstring *v)
{
	return extr_quant_hfta3_fcn(v, 0.5);
}

gs_uint32_t extr_quant_hfta3_space(vstring *v)
{
	quant_udaf_hfta3_struct_t *vs = (quant_udaf_hfta3_struct_t *)(v->offset);
	supertuple_t *t;
	gs_uint32_t count=0;

	for (t=vs->t; t != NULL; t=t->next)
		count++;
	return count;
}
