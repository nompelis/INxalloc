###### Pre-processor directives to increase verbosity
DEBUG = -D   _DEBUG_

###### additional compile-time configuration
SPECIAL_OPTIONS = -D  _LINUX_

###### C++ 
CXX = g++
CXXOPTS = -Wall -fPIC -O0 -std=c++98 -pedantic
CXXOPTS = -Wall -fPIC -O0
CXXOPTS += $(SPECIAL_OPTIONS)

###### C
CC = gcc
COPTS = -Wall -fPIC -O0
COPTS += $(SPECIAL_OPTIONS)

###### linker
LD = ld

###### library

all:
	$(CC) -c $(DEBUG) $(COPTS) $(INCLUDE) inxalloc_plain.c
	$(LD) -shared  -rpath=. \
	      -soname libINxalloc.so \
         -o libINxalloc.so \
                inxalloc_plain.o  \
         -lc 

test:
	$(CC) $(DEBUG) $(COPTS)  -I . main.c -Wl,-rpath=.  -L . -lINxalloc

clean:
	rm -f *.o *.a a.out *.so *.a

