#ifndef FQRP_ALGORITHMS_H
#define FQRP_ALGORITHMS_H

#include "aggregator.h"
#include "generator.h"
#include "instance.h"
#include "types.h"

namespace fqrp {

conflictCount getConflictCount(const Instance &instance);

template <typename result_t>
result_t getEstimatedConflictCount(count_t maxSample, Generator *generator,
                                   Aggregator<result_t> *aggregator);

template <typename result_t>
result_t getExactConflictCount(Generator *generator,
                               Aggregator<result_t> *aggregator);

} // namespace fqrp

template <typename result_t>
result_t fqrp::getEstimatedConflictCount(count_t maxSample,
                                         Generator *generator,
                                         Aggregator<result_t> *aggregator) {

  count_t n = 0;

  while (n < maxSample && !generator->finished()) {
    Instance inst = generator->next();
    aggregator->aggregate(getConflictCount(inst));
    n += 1;
  }

  return aggregator->result();
}

template <typename result_t>
result_t fqrp::getExactConflictCount(Generator *generator,
                                     Aggregator<result_t> *aggregator) {
  return getEstimatedConflictCount(-1, generator, aggregator);
}

#endif