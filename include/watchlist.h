#ifndef __WATCHLIST_H_DEFINED__
#define __WATCHLIST_H_DEFINED__


static inline gs_retval_t wl_csv_uint(char *p, gs_uint32_t *t)
{
    *t = strtoul((const char*)p, NULL, 10);
	return 0;
}

static inline gs_retval_t wl_csv_ullong(char *p, gs_uint64_t *t)
{
    *t = strtoull((const char*)p, NULL, 10);
	return 0;
}

static inline gs_retval_t wl_csv_ip(char *p, gs_uint32_t *t)
{
	unsigned ip1,ip2,ip3,ip4;
    sscanf((const char*) p,"%u.%u.%u.%u",&ip1,&ip2,&ip3,&ip4);
	*t=(ip1<<24)|(ip2<<16)|(ip3<<8)|ip4;
	return 0;
}

static inline gs_retval_t wl_csv_ipv6(char *p, struct ipv6_str *t)
{
    gs_uint32_t v[8];
    sscanf((const char*) p,"%x:%x:%x:%x:%x:%x:%x:%x",&v[0],&v[1],&v[2],&v[3],&v[4],&v[5],&v[6],&v[7]);
	t->v[0]=htonl(v[0]<<16|v[1]);
	t->v[1]=htonl(v[2]<<16|v[3]);
	t->v[2]=htonl(v[4]<<16|v[5]);
	t->v[3]=htonl(v[6]<<16|v[7]);
	return 0;
}

static inline gs_retval_t wl_csv_string(char *p, struct gs_string * t)
{
    size_t sz = strlen(p);
	t->data=(gs_sp_t)strndup(p, sz);
    t->length=sz;
	t->owner=(struct FTA *)1;
    return 0;
}

static inline gs_retval_t wl_csv_bool(char *p, gs_uint32_t *t)
{
	*t=0;
	if ((strlen((const char*)p)==4) &&
		(strncasecmp("TRUE",(const char*)p,4) ==0) ) {
		*t=1;
	}
    return 0;
}

static inline gs_retval_t wl_csv_int(char *p, gs_int32_t *t)
{
    *t = strtol((const char*)p, NULL, 10);
    return 0;
}

static inline gs_retval_t wl_csv_llong(char *p, gs_int64_t *t)
{
    *t = strtoll((const char*)p, NULL, 10);
    return 0;
}

static inline gs_retval_t wl_csv_float(char *p, gs_float_t *t)
{
    *t = strtod((const char*)p, NULL);
    return 0;
}




#endif
