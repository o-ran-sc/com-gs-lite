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
#ifndef __RDTSC_H__
#define __RDTSC_H__

#include "gsconfig.h"
#include "gstypes.h"

#if defined(__i386__) || defined(__x86_64__)

static __inline__ gs_uint64_t rdtsc(void)
{
    gs_uint64_t x=0;
    gs_uint32_t low;
    gs_uint32_t high;
    __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
    x=((gs_uint64_t)high)<<32;
    x=x|((gs_uint64_t)low);
    return x;
}
#endif

#endif	// __RDTSC_H__

