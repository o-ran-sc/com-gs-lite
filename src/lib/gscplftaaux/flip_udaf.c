#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "rts_udaf.h"
#include "gsconfig.h"
#include "gstypes.h"

/*      Full size
#define QUANT_LFTA1_SIZE 729
#define QUANT_LFTA2_SIZE 181
#define QUANT_LFTA3_SIZE 100
*/

/*      half size
*/
#define QUANT_LFTA1_SIZE 378
#define QUANT_LFTA2_SIZE 93
#define QUANT_LFTA3_SIZE 50

/*      quarter size
#define QUANT_LFTA1_SIZE 202
#define QUANT_LFTA2_SIZE 49
#define QUANT_LFTA3_SIZE 25
*/


#define QUANT_EPS 0.01
#define SKIPDIR_SIZE 100
#define SKIPDIR_HEIGHT_MAX 7
#define max(a,b) ((a) > (b) ? (a) : (b))
#define COMPRESSED_XFER

/****************************************************************/
/* Data Structures						*/
/****************************************************************/
typedef struct tuple_t {
	gs_uint32_t val;
	gs_uint32_t gap;
	gs_uint32_t del;
	gs_uint32_t next;
} tuple_t;

// For skip list
typedef gs_uint32_t val_type;

typedef struct skipnode {
	val_type val;
	gs_uint32_t next;
	gs_uint32_t down;
} skipnode_t;

typedef struct skipdir {
	gs_uint32_t height;				// height of tree
	gs_uint32_t freeptr;				// cursor space stack
	gs_uint32_t headptr[SKIPDIR_HEIGHT_MAX+1];	// ptrs to levels
	skipnode_t list[SKIPDIR_SIZE+1];
} skipdir_t;


/****************************************************************/

// fstring(5+(QUANT_LFTA3_SIZE+1)*4 +
//         (2+lg(QUANT_LFTA3_SIZE)+(QUANT_LFTA3_SIZE+1)*3)*4)
typedef struct quant_udaf_lfta3_struct_t {
	gs_uint32_t nelts;	// # stream elements
	gs_uint32_t freeptr;	// ptr to cursor stack
	gs_uint32_t usedptr;	// ptr to allocated memory
	gs_uint32_t circptr;	// circulating ptr used for compression
	gs_uint32_t size;
	tuple_t t[QUANT_LFTA3_SIZE+1];	// samples + auxiliary info
	skipdir_t sd;		// directory for searching tuples
} quant_udaf_lfta3_struct_t;

/****************************************************************/
/* Skip List Functions						*/
/****************************************************************/

// Skip list cursor stack operations
gs_uint32_t skipdir_alloc(skipdir_t *sd)
{
	gs_uint32_t ptr = sd->freeptr;
	if (sd->freeptr != 0)
		sd->freeptr = sd->list[ptr].next;
	return ptr;
}

void skipdir_free(skipdir_t *sd, gs_uint32_t ptr)
{
	sd->list[ptr].val = 0;
	sd->list[ptr].down = 0;
	sd->list[ptr].next = sd->freeptr;
	sd->freeptr = ptr;
}


void skipdir_create(skipdir_t *sd)
{
	gs_int32_t i;

	sd->height = 0;
	sd->freeptr = 1;
	for (i=0; i < SKIPDIR_HEIGHT_MAX; i++)
		sd->headptr[i] = 0;
	for (i=1; i < SKIPDIR_SIZE; i++)
		sd->list[i].next = i+1;
	sd->list[SKIPDIR_SIZE].next = 0;
}

void skipdir_destroy(skipdir_t *sd)
{
	sd->height = 0;
}


void skipdir_search(skipdir_t *sd, val_type val, gs_uint32_t *ptrstack)
{
	gs_uint32_t ptr;
	gs_int32_t l;

	if (sd->height == 0) {
		ptrstack[0] = ptrstack[1] = 0;
		return;
	}
	// search nonleaf nodes
	ptr = sd->headptr[sd->height-1];
	for (l=sd->height-1; l >= 0; l--) {
		if (ptr == 0) {
			ptrstack[l+1] = 0;
			ptr = (l > 0) ? sd->headptr[l-1] : 0;
		}
		else if (val <= sd->list[ptr].val) {
			ptrstack[l+1] = 0;
			ptr = (l > 0) ? sd->headptr[l-1] : 0;
		}
		else {
			while ((sd->list[ptr].next != 0) &&
			(sd->list[sd->list[ptr].next].val < val))
				ptr = sd->list[ptr].next;
			ptrstack[l+1] = ptr;
			ptr = sd->list[ptr].down;
		}
	}
	ptrstack[0] = ptr;
}


void skipdir_insert(skipdir_t *sd, gs_uint32_t *ptrstack,
			gs_uint32_t leafptr, val_type val)
{
	gs_uint32_t newptr, oldptr;
	gs_int32_t l;

	// if path already existed then point to new duplicate
	if ((ptrstack[1] == 0) && (sd->headptr[0] != 0)
	&& (sd->list[sd->headptr[0]].val == val)) {
		sd->list[sd->headptr[0]].down = leafptr;
		return;
	}
	if ((ptrstack[1] != 0) && (sd->list[ptrstack[1]].next != 0)
	&& (sd->list[sd->list[ptrstack[1]].next].val == val)) {
		sd->list[sd->list[ptrstack[1]].next].down = leafptr;
		return;
	}

	for (l=0; l < SKIPDIR_HEIGHT_MAX; l++) {
		if (random() % 2) break;
		newptr = skipdir_alloc(sd);
		if (!newptr) break;	// out of memory
		sd->list[newptr].val = val;
		//copy(&val, &list[newptr[l]].val);
		// link new directory node to level below
		if (l > 0)
			sd->list[newptr].down = oldptr;
		else
			sd->list[newptr].down = leafptr;
		// insert node into current level
		if ((l >= sd->height) || (ptrstack[l+1] == 0)) {
			sd->list[newptr].next = sd->headptr[l];
			sd->headptr[l] = newptr;
		}
		else {
			sd->list[newptr].next = sd->list[ptrstack[l+1]].next;
			sd->list[ptrstack[l+1]].next = newptr;
		}
		oldptr = newptr;
	}
	if (l > sd->height) sd->height = l;
	//fprintf(stderr,"new height = %u\n",sd->height);
}


void skipdir_delete(skipdir_t *sd, gs_uint32_t *ptrstack, val_type val)
{
	gs_uint32_t delptr;
	gs_int32_t l;

	for (l=0; l < sd->height; l++) {
		if (ptrstack[l+1] == 0) {
			delptr = sd->headptr[l];
			if (delptr == 0) break;
			if (sd->list[delptr].val == val) {
				sd->headptr[l] = sd->list[delptr].next;
				skipdir_free(sd, delptr);
			}
			else
				break;
		}
		else {
			delptr = sd->list[ptrstack[l+1]].next;
			if (delptr == 0) break;
			if (sd->list[delptr].val == val) {
				sd->list[ptrstack[l+1]].next = sd->list[delptr].next;
				skipdir_free(sd, delptr);
			}
			else
				break;
		}
	}
}

// For Debugging
void skipdir_print(skipdir_t *sd)
{
	gs_uint32_t ptr;
	gs_int32_t l;

	for (l=sd->height-1; l >= 0; l--) {
		for (ptr=sd->headptr[l]; ptr != 0; ptr=sd->list[ptr].next)
			fprintf(stderr,"%u ", sd->list[ptr].val);
		fprintf(stderr,"\n");
	}
	fprintf(stderr,"-------\n");
	for (l=sd->height-1; l > 0; l--) {
		for (ptr=sd->headptr[l]; ptr != 0; ptr=sd->list[ptr].next)
			fprintf(stderr,"%u ", sd->list[sd->list[ptr].down].val);
		fprintf(stderr,"\n");
	}
	fprintf(stderr,"-------\n");
}




/*************************** Version 3 **************************/
/* Version 3: LFTA-medium					*/
/*								*/
/* NIC performs O(log n) operations at each update.		*/
/****************************************************************/

/****************************************************************/
/* Helper functions						*/
/****************************************************************/
gs_uint32_t quant_udaf_lfta3_cursor_alloc(quant_udaf_lfta3_struct_t *s)
{
	gs_uint32_t ptr = s->freeptr;
	if (s->freeptr != 0) s->freeptr = s->t[ptr].next;
	s->size++;
	return ptr;
}

void quant_udaf_lfta3_cursor_free(quant_udaf_lfta3_struct_t *s, gs_uint32_t ptr)
{
	s->t[ptr].next = s->freeptr;
	s->freeptr = ptr;
	s->size--;
}

void quant_lfta3_print(quant_udaf_lfta3_struct_t *s)
{
	tuple_t *t=s->t;
	gs_uint32_t ptr = s->usedptr;

	if (ptr == 0) {
		fprintf(stderr,"<empty>\n");
		return;
	}
	//skipdir_print(&s->sd);
	for (; ptr != 0; ptr=t[ptr].next) {
		fprintf(stderr,"(%u, %u, %u) ",t[ptr].val,t[ptr].gap,t[ptr].del);
	}
	fprintf(stderr,"\n");
}

void quant_lfta3_compress(quant_udaf_lfta3_struct_t *s)
{
	tuple_t *t = s->t;
	gs_uint32_t delptr;
	gs_uint32_t threshold;
	gs_uint32_t ptrstack[SKIPDIR_HEIGHT_MAX+5];

	threshold = (gs_uint32_t)ceil(2.0 * QUANT_EPS * (gs_float_t)s->nelts);
//if(s->circptr < 0 || s->circptr >= QUANT_LFTA3_SIZE)
// printf("1) s->circptr = %d\n",s->circptr);
//if(t[s->circptr].next < 0 || t[s->circptr].next >= QUANT_LFTA3_SIZE)
// printf("t[s->circptr].next = %d\n",t[s->circptr].next);
	if ((s->circptr == 0) || (t[s->circptr].next == 0)
	|| (t[t[s->circptr].next].next == 0))
		s->circptr = s->usedptr;
	//if ((s->size % 10) != 0) return;
	if (s->nelts > 2) {
//if(s->circptr < 0 || s->circptr >= QUANT_LFTA3_SIZE)
// printf("2) s->circptr = %d\n",s->circptr);
		delptr = t[s->circptr].next;
//if(delptr < 0 || delptr >= QUANT_LFTA3_SIZE)
// printf("delptr = %d\n",delptr);
//if(t[delptr].next < 0 || t[delptr].next >= QUANT_LFTA3_SIZE)
// printf("t[delptr].next = %d\n",t[delptr].next);
		if (t[delptr].gap+t[t[delptr].next].gap+t[t[delptr].next].del < threshold) {
			// delete from directory
			if (t[s->circptr].val != t[delptr].val) {
				// leftmost duplicate (if multiplicity)
				skipdir_search(&(s->sd), t[delptr].val, ptrstack);
				if (t[delptr].val == t[t[delptr].next].val) {
//if(s->sd.headptr[0] < 0 || s->sd.headptr[0] >= QUANT_LFTA3_SIZE)
// printf("s->sd.headptr[0] = %d\n",s->sd.headptr[0]);
					// duplicates case
					if ((ptrstack[1] == 0)
					&& (s->sd.headptr[0] != 0)
					&& (s->sd.list[s->sd.headptr[0]].val == t[delptr].val))
						s->sd.list[s->sd.headptr[0]].down = t[delptr].next;
					else if ((ptrstack[1] != 0)
					&& (s->sd.list[ptrstack[1]].next != 0)
					&& (s->sd.list[s->sd.list[ptrstack[1]].next].val == t[delptr].val))
						s->sd.list[s->sd.list[ptrstack[1]].next].down = t[delptr].next;
				}
				else {
					// non-duplicates case
					skipdir_delete(&(s->sd), ptrstack, t[delptr].val);
				}
			}
			// delete from list
			//fprintf(stderr,"DELETED %u\n", t[delptr].val);
			t[s->circptr].next = t[delptr].next;
			quant_udaf_lfta3_cursor_free(s, delptr);
		}
		else {
			s->circptr = t[s->circptr].next;
		}
	}
}


/****************************************************************/
/* LFTA3 functions						*/
/****************************************************************/
void quant_udaf_lfta3_LFTA_AGGR_INIT_(gs_sp_t b)
{
	gs_uint32_t i;

	quant_udaf_lfta3_struct_t *s = (quant_udaf_lfta3_struct_t *)b;
	s->nelts = 0;
	s->usedptr = 0;		// NULL ptr
	s->circptr = 0;
	// initialize cursor stack
	s->freeptr = 1;
	s->size = 0;
	for (i=1; i < QUANT_LFTA3_SIZE; i++)
		s->t[i].next = i+1;
	s->t[QUANT_LFTA3_SIZE].next = 0;
	skipdir_create(&(s->sd));
}

void quant_udaf_lfta3_LFTA_AGGR_UPDATE_(gs_sp_t b, gs_uint32_t v)
{
	quant_udaf_lfta3_struct_t *s = (quant_udaf_lfta3_struct_t *)b;
	tuple_t *t = s->t;
	gs_uint32_t ptr = s->usedptr;
	gs_uint32_t newptr, delptr;
	gs_uint32_t obj;	// objective function
	gs_uint32_t threshold;
	gs_uint32_t ptrstack[SKIPDIR_HEIGHT_MAX+5];
	gs_uint32_t debugptr;

//printf("AGGR_UPDATE start\n");
	s->nelts++;
	//fprintf(stderr,"nelts = %u\n",s->nelts);
	// left boundary case
	if ((ptr == 0) || (v < t[ptr].val)) {
		if (t[ptr].val == v) {
			t[ptr].gap++;
//printf("AGGR_UPDATE END 1\n");
			return;
		}
		newptr = quant_udaf_lfta3_cursor_alloc(s);
		if (newptr == 0) {
			gslog(LOG_ALERT, "Out of space.\n");
			return;
		}
		t[newptr].val = v;
		t[newptr].gap = 1;
		t[newptr].del = 0;
		t[newptr].next = s->usedptr;
		s->usedptr = newptr;
//printf("AGGR_UPDATE END 2\n");
		return;
	}

	// locate $i$ such that (v_i-1 < v <= v_i)
	skipdir_search(&(s->sd), v, ptrstack);

	//ptr = (ptrstack[0] == 0) ? s->usedptr : s->sd.list[ptrstack[0]].down;
	ptr = (ptrstack[0] == 0) ? s->usedptr : ptrstack[0];
	while ((t[ptr].next != 0) && (t[t[ptr].next].val < v))
		ptr = t[ptr].next;

/*
	// duplicate value
	if ((t[ptr].next != 0) && (t[t[ptr].next].val == v)) {
		t[t[ptr].next].gap++;
printf("AGGR_UPDATE END 3\n");
		return;
	}
*/

	// right boundary case
	if (t[ptr].next == 0) {
		newptr = quant_udaf_lfta3_cursor_alloc(s);
		if (newptr == 0) {
			gslog(LOG_ALERT, "Out of space.\n");
			return;
		}
		t[newptr].val = v;
		t[newptr].gap = 1;
		t[newptr].del = 0;
		t[newptr].next = 0;
		t[ptr].next = newptr;
//printf("AGGR_UPDATE END 4\n");
		return;
	}

	// non-boundary case
//printf("1) t[ptr].next =%d, ptr=%d\n",t[ptr].next,ptr);
	obj = t[ptr].gap+t[t[ptr].next].gap+t[t[ptr].next].del;
	threshold = (gs_uint32_t)ceil(2.0 * QUANT_EPS * (gs_float_t)s->nelts);
	if (obj > threshold) {
		newptr = quant_udaf_lfta3_cursor_alloc(s);
		if (newptr == 0) {
			gslog(LOG_ALERT, "Out of memory.\n");
			return;
		}
//printf("newptr=%d\n",newptr);
		t[newptr].val = v;
		t[newptr].gap = 1;
		t[newptr].del = t[t[ptr].next].gap+t[t[ptr].next].del - 1;
		t[newptr].next = t[ptr].next;
		t[ptr].next = newptr;
		skipdir_insert(&(s->sd), ptrstack, newptr, v);
	}
	else {
		// insert into existing bucket
//printf("t[ptr].next =%d\n",t[ptr].next);
		t[t[ptr].next].gap++;
	}
	quant_lfta3_compress(s);
//printf("AGGR_UPDATE END 5\n");
}

gs_int32_t quant_udaf_lfta3_LFTA_AGGR_FLUSHME_(gs_sp_t b)
{
	quant_udaf_lfta3_struct_t *s = (quant_udaf_lfta3_struct_t *)b;

	if (s->freeptr == 0)
		return 1;
	else
		return 0;
}

void quant_udaf_lfta3_LFTA_AGGR_OUTPUT_(struct gs_string *r, gs_sp_t b)
{
#ifdef COMPRESSED_XFER
	quant_udaf_lfta3_struct_t *s = (quant_udaf_lfta3_struct_t *)b;
	tuple_t tmp[QUANT_LFTA3_SIZE+1];
	gs_uint32_t ptr=s->usedptr;
	gs_int32_t i=0,j;

	for (; ptr != 0; ptr=s->t[ptr].next) {
		tmp[i].val = s->t[ptr].val;
		tmp[i].gap = s->t[ptr].gap;
		tmp[i].del = s->t[ptr].del;
		i++;
	}
	for (j=1; j <= i; j++) {
		s->t[j].val = tmp[j-1].val;
		s->t[j].gap = tmp[j-1].gap;
		s->t[j].del = tmp[j-1].del;
		s->t[j].next = j+1;
	}
	s->t[i].next = 0;
	s->usedptr = 1;

	r->length = (5 + 4*(i+1))*sizeof(gs_uint32_t);
#endif
#ifndef COMPRESSED_XFER
	r->length = sizeof(quant_udaf_lfta3_struct_t);
#endif
	r->data = b;
}

void quant_udaf_lfta3_LFTA_AGGR_DESTROY_(gs_sp_t b)
{
	return;
}
