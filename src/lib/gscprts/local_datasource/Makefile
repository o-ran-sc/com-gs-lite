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

CC=gcc  -g -O3 -msse4.2 -fexpensive-optimizations -I libdag/include -I ../../../../include/lfta/ -I ../../../../include/ -I .././include/ -I ../../gscphost/include -I ../../../../include/lfta/local -I /usr/local/include
CXX=g++  -g -O3 -msse4.2 -fexpensive-optimizations -I libdag/include -I ../../../../include/lfta/ -I ../../../../include/ -I .././include/ -I ../../gscphost/include -I ../../../../include/lfta/local

SOURCE_C =   rts_proto.c 
SOURCE_CC =   
SOURCE =   $(SOURCE_C) $(SOURCE_CC) 


OBJECTS = $(SOURCE_C:.c=.o) $(SOURCE_CC:.cc=.o)


all: rts_proto.o 

LFTA_DIR=$(INCDIR/lfta)


clean:
	rm -f *.o *.a core
