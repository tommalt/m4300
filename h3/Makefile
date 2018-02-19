cxx=g++
CFLAGS=-g -ggdb -Wall
.PHONY: clean
.PHONY: all

all: h3-1 h3-2

h3-1: h3-1.cc
	$(cxx) h3-1.cc -o $@ $(CFLAGS)

h3-2: h3-2.cc
	$(cxx) h3-2.cc -o $@ $(CFLAGS) -lm

clean:
	@echo cleaning
	@rm -f h3-1 h3-2
