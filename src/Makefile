
CC = g++
CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -Wextra -Werror -g

DEPENDENCIES = $(subst .cpp,.d,$(shell find . -name "*.cpp"))

all: progs/random_gen_main progs/int_gen_main progs/exh_gen_main progs/exh_filt_gen_main

progs/random_gen_main: progs/random_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o generators/randomGenerator.o conflicts.a types.o

progs/int_gen_main: progs/int_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o generators/intervalGenerator.o conflicts.a types.o

progs/exh_gen_main: progs/exh_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o generators/exhaustiveGenerator.o conflicts.a types.o

progs/exh_filt_gen_main: progs/exh_filt_gen_main.o aggregators/averageAggregator.o counters/conflictCounter.o filters/partitioned.o filters/symmetric.o  generators/exhaustiveGenerator.o conflicts.a types.o

conflicts.a: conflicts.o conflicts.o utils/isAForest.o utils/unionFind.o
	ar r $@ $?


%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(DEPENDENCIES)

.PHONY: clean
clean:
	- which git > /dev/null && git clean -fX || { \
	find . -name "*.o" -delete; \
	find . -name "*.a" -delete; \
	find . -name "*.d" -delete; \
	}