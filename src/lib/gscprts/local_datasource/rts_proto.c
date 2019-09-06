
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
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "errno.h"

#include "gsconfig.h"
#include "gshub.h"
#include "gstypes.h"
#include "lapp.h"
#include "fta.h"
#include "stdio.h"
#include "stdlib.h"
#include "packet.h"
#include "schemaparser.h"
#include "lfta/rts.h"

// --------------------------------------
//		This is a stub entry point to ensure that proper linking.
//		any actual rts_proto.c should be generated.
// --------------------------------------

    
//	Entry for processing this interface
gs_retval_t main_dproto(gs_int32_t devicenum, gs_sp_t device, gs_int32_t mapcnt, gs_sp_t map[]) {

	fprintf(stderr,"ERROR, empty main_dproto called.\n");
	exit(1);

}

