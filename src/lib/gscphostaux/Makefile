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

CC=gcc -O3  -fexpensive-optimizations -I ../../../include

SOURCE =  byteswap.c

OBJECTS = $(SOURCE:.c=.o)

all: install

install: libgscphostaux.a
	cp libgscphostaux.a ../../../lib ; ranlib ../../../lib/libgscphostaux.a

INCDIR=../../../include

byteswap.c : $(INCDIR/gstypes.h) $(INCDIR/gsconfig.h)

libgscphostaux.a: $(OBJECTS) Makefile 
	ar  rc libgscphostaux.a $(OBJECTS) 

clean:
	rm -f *.o *.a core


$(OBJECTS): 
