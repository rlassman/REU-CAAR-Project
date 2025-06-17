# Compiler and flags
CC = g++
TARGET := simple
SRC := simpleTest
OBJ := $(SRC:.cpp=.o)
COMMON = common_sort.h regionsSort.h parallel.h prefixsum.h radix_configs.h sequence.h sequenceIO.h triangle.h utils.h IO.h edge.h edgelistgraph.h block.h example.cpp misc.h radixSort.h

CFLAGS := -std=c++17 -Wall -g -O3 -flto -march=native -I. -I./parlaylib -DPARLAY -w #-fsanitize=address #disabled warnings

LDFLAGS := -flto -lpthread

ifeq ($(DEBUG),1)
	CFLAGS += -O0 -DDEBUG
endif

ifeq ($(REFERENCE),1)
	CFLAGS += -DRUN_REFERENCE_CODE=1
endif

ifeq ($(PROFILE),1)
	CFLAGS += -DPROFILE
	LDFLAGS += -lprofiler
endif

.PHONY: default clean

default: radixSort radixSort_cycle

radixSort: $(COMMON)
	$(CC) $(CFLAGS) example.cpp -DBITS_HACK -o radixSort $(LDFLAGS)

radixSort_cycle: $(COMMON)
	$(CC) $(CFLAGS) example.cpp -DCYCLE -DBITS_HACK -o radixSort_cycle $(LDFLAGS)

# Dependency generation
-include $(SRC:.cpp=.d)

%.d : %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM -MT $*.o -MP -MF $@.$$$$ $(CFLAGS) $<; \
	sed -e 's|\($*\)\.o[ :]*|\1.o $@ : |g' < $@.$$$$ > $@; \
	rm -f $@.$$$$*

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

simple: simple.o $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

clean:
	rm -f *.o *.d* *~ $(TARGET) radixSort radixSort_cycle