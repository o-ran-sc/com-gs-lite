# ------------------------------------------------
#   Copyright 2014 AT&T Intellectual Property
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
# -------------------------------------------

CPP=g++ -g -O3  -fexpensive-optimizations -I ../gscpaux/acl/ -I ../gscpaux/ -I ../../../include/lfta/ -I ../../../include/
CC=gcc -g -O3  -fexpensive-optimizations -I ../gscpaux/acl/ -I ../gscpaux/ -I ../../../include/lfta/ -I ../../../include/

SOURCE =  rts_string.c rts_byteswap.c rts_sample.c rts_udaf.c flip_udaf.cc

OBJECTS = rts_string.o rts_byteswap.o rts_sample.o rts_udaf.o flip_udaf.o

INCDIR=../../../include
HFTA_DIR=$(INCDIR/hfta)
LFTA_DIR=$(INCDIR/lfta)

all: libgscplftaaux.a
	cp libgscplftaaux.a ../../../lib/ ; ranlib ../../../lib/libgscplftaaux.a

libgscplftaaux.a: $(OBJECTS) Makefile 
	ar  rc libgscplftaaux.a $(OBJECTS) 

rts_string.c : $(LFTA_DIR/rts_external.h) $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h)

rts_byteswap.c : $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h)

rts_sample.c : $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h) $(LFTA_DIR/rts_external.h)

rts_udaf.c : $(LFTA_DIR/rts_udaf.h) $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h) 

flip_udaf.cc : $(LFTA_DIR/flip_udaf.h) $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h) 

lpm.c : $(LFTA_DIR/rts_external.h) $(INCDIR/fta.h) $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h)

flip_udaf.cc : $(LFTA_DIR/rts_udaf.h) $(INCDIR/gsconfig.h) $(INCDIR/gstypes.h)

flip_udaf.o : flip_udaf.cc
	$(CPP) -c -o flip_udaf.o flip_udaf.cc

install: all

clean:
	rm -f *.o *.a core

