# created with:sm --main h2-1.cc 

cc=cc
cxx=c++
override cflags+=-Wall -g -ggdb 
override libs+=
opt=0
BUILD=build

objs=$(BUILD)/h2-1.o 
.PHONY: $(BUILD)/h2-1

$(BUILD)/h2-1: $(objs)
	$(cxx) $(objs) -o $(BUILD)/h2-1 $(cflags) $(libs) -O$(opt)
	ln -sf $(BUILD)/h2-1 h2-1

$(BUILD)/h2-1.o: h2-1.cc
	$(cxx) -c h2-1.cc -o $(BUILD)/h2-1.o $(cflags) -O$(opt)

clean:
	@echo cleaning
	@rm -f build/* h2-1
