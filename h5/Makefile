
.PHONY: all
all: h5-1 h5-2 h5-3

h5-1: h5-1.cc
	g++ h5-1.cc -o $@ -g -ggdb
	
h5-2: h5-2.cc
	g++ h5-2.cc -o $@ -g -ggdb

h5-3: h5-3.cc
	g++ h5-3.cc -o $@ -g -ggdb
clean:
	@echo cleaning
	@rm -f h5-1 h5-2 h5-3
