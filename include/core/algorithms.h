#ifndef CORE_ALGORITHMS_H
#define CORE_ALGORITHMS_H

#include <limits>

#include "aggregator.h"
#include "counter.h"
#include "generator.h"

namespace core {

template <typename raw_t, typename count_t, typename result_t, typename limit_t>
result_t getEstimatedCount(limit_t limit, Generator<raw_t> &generator,
                           Counter<raw_t, count_t> &counter,
                           Aggregator<count_t, result_t> &aggregator);

template <typename raw_t, typename count_t, typename result_t>
result_t getExactCount(Generator<raw_t> &generator,
                       Counter<raw_t, count_t> &counter,
                       Aggregator<count_t, result_t> &aggregator);

} // namespace core

template <typename raw_t, typename count_t, typename result_t, typename limit_t>
result_t core::getEstimatedCount(limit_t limit, Generator<raw_t> &generator,
                                 Counter<raw_t, count_t> &counter,
                                 Aggregator<count_t, result_t> &aggregator) {

  for (limit_t n = 0; n < limit && !generator.finished(); n++)
    aggregator.aggregate(counter.count(generator.next()));

  return aggregator.result();
}

template <typename raw_t, typename count_t, typename result_t>
result_t core::getExactCount(Generator<raw_t> &generator,
                             Counter<raw_t, count_t> &counter,
                             Aggregator<count_t, result_t> &aggregator) {
  return getEstimatedCount(std::numeric_limits<float>::infinity(), generator,
                           counter, aggregator);
}

#endif