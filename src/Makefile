
CC = g++
CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -Wextra -Werror -g

CORE = include/core/aggregator.h include/core/algorithms.h include/core/counter.h include/core/generator.h

all: main

main: main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o generators/exhaustiveGenerator.o generators/intervalGenerator.o generators/randomGenerator.o conflicts.o types.o | $(CORE)

%.o: %.h

.PHONY: clean
clean:
	- find . -name "*.o" -delete