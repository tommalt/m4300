CXX=c++
CFLAGS=-std=c++11

all: h4-1 h4-2 h4-3

h4-1: h4-1.cc
	$(CXX) h4-1.cc $(CFLAGS) -o $@

h4-2: h4-2.cc
	$(CXX) h4-2.cc $(CFLAGS) -o $@

h4-3: h4-3.cc
	$(CXX) h4-3.cc $(CFLAGS) -o $@

.PHONY: clean
clean:
	@echo cleaning
	@rm -f h4-1 h4-2 h4-3
