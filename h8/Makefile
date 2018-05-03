.PHONY: all
all: h8-1 h8-2

h8-1: h8-1.cc
	g++ $< -o $@ -std=c++14 -g -ggdb -fopenmp $(CFLAGS)
h8-2: h8-2.cc
	g++ $< -o $@ -std=c++14 -g -ggdb -fopenmp $(CFLAGS)
clean:
	@echo cleaning
	@rm -f h8-1 h8-2 *.o
