cc=cc
cxx=c++
override cflags+=-Wall -g -ggdb 
BUILD=build

all: $(BUILD)/h2-1 $(BUILD)/h2-2 $(BUILD)/h2-3

$(BUILD)/h2-1: h2-1.cc
	$(cxx) h2-1.cc -o $(BUILD)/h2-1 $(cflags) $(libs)
	ln -sf $(BUILD)/h2-1 h2-1

$(BUILD)/h2-2: h2-2.cc
	$(cxx) h2-2.cc -o $(BUILD)/h2-2 $(cflags) $(libs)
	ln -sf $(BUILD)/h2-2 h2-2

$(BUILD)/h2-3: h2-3.cc
	$(cxx) h2-3.cc -o $(BUILD)/h2-3 $(cflags) $(libs)
	ln -sf $(BUILD)/h2-3 h2-3
clean:
	@echo cleaning
	@rm -f build/* h2-1 h2-2 h2-3
