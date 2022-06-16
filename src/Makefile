
CC = g++
CPPFLAGS = -Iinclude
CXXFLAGS = -Wall -Wextra -Werror -g

DEPENDENCIES = $(subst .cpp,.d,$(shell find . -name "*.cpp"))

all: progs/rand_filt_gen_main progs/int_filt_gen_main progs/exh_gen_main progs/exh_filt_gen_main

progs/rand_filt_gen_main: progs/rand_filt_gen_main.o aggregators/distribution_aggregator.o utils/distribution.o counters/conflictCounter.o filters/partitioned.o generators/randomGenerator.o conflicts.a types.o

progs/int_filt_gen_main: progs/int_filt_gen_main.o aggregators/distribution_aggregator.o utils/distribution.o counters/conflictCounter.o filters/partitioned.o generators/intervalGenerator.o conflicts.a types.o

progs/exh_gen_main: progs/exh_gen_main.o aggregators/distribution_aggregator.o utils/distribution.o counters/conflictCounter.o generators/exhaustiveGenerator.o conflicts.a types.o

progs/exh_filt_gen_main: progs/exh_filt_gen_main.o aggregators/distribution_aggregator.o utils/distribution.o counters/conflictCounter.o filters/partitioned.o filters/symmetric.o  generators/exhaustiveGenerator.o conflicts.a types.o

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
	- git rev-parse --git-dir > /dev/null 2>&1 && find . -wholename .git && git clean -fX || { \
	find . -name "*.o" -delete; \
	find . -name "*.a" -delete; \
	find . -name "*.d" -delete; \
	}