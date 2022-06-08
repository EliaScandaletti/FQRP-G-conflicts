
CC = g++
CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -Wextra -Werror -g

CORE = include/core/aggregator.h include/core/algorithms.h include/core/counter.h include/core/generator.h

all: tests/random_gen_main tests/int_gen_main tests/exh_gen_main

main: main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o generators/exhaustiveGenerator.o generators/intervalGenerator.o generators/randomGenerator.o conflicts.o types.o | $(CORE)

tests/random_gen_main: tests/random_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o generators/randomGenerator.o conflicts.o types.o | $(CORE)

tests/int_gen_main: tests/int_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o generators/intervalGenerator.o conflicts.o types.o | $(CORE)

tests/exh_gen_main: tests/exh_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o generators/exhaustiveGenerator.o conflicts.o types.o | $(CORE)

%.o: include/fqrp/%.h

.PHONY: clean
clean:
	- which git > /dev/null && git clean -fX || find . -name "*.o" -delete