cc=cc
cxx=c++
override cflags+=-Wall -g -ggdb 
BUILD=build

all: make_build $(BUILD)/h2-1 $(BUILD)/h2-2 $(BUILD)/h2-3

.PHONY: make_build
make_build: $(BUILD)

$(BUILD):
	mkdir -p $(BUILD)

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
	@rm -f build/*
	@ls | grep "h2-[0-9]$$" |xargs rm -f
