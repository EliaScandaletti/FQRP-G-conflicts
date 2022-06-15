
CC = g++
CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -Wextra -Werror -g

CORE = include/core/aggregator.h include/core/algorithms.h include/core/counter.h include/core/generator.h
UTILS = include/utils/unionFind.h include/utils/isAForest.h

all: tests/random_gen_main tests/int_gen_main tests/exh_gen_main tests/exh_filt_gen_main

tests/random_gen_main: tests/random_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o generators/randomGenerator.o conflicts.o utils/isAForest.o utils/unionFind.o types.o | $(CORE)

tests/int_gen_main: tests/int_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o generators/intervalGenerator.o conflicts.o utils/isAForest.o utils/unionFind.o types.o | $(CORE)

tests/exh_gen_main: tests/exh_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o generators/exhaustiveGenerator.o conflicts.o utils/isAForest.o utils/unionFind.o types.o | $(CORE)

tests/exh_filt_gen_main: tests/exh_filt_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o filters/symmetric.o  generators/exhaustiveGenerator.o conflicts.o utils/isAForest.o utils/unionFind.o types.o | $(CORE)

%.o: include/fqrp/%.h

.PHONY: clean
clean:
	- which git > /dev/null && git clean -fX || find . -name "*.o" -delete