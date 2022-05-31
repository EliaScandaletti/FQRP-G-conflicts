#ifndef FQRP_AGGREGATOR_H
#define FQRP_AGGREGATOR_H

#include "types.h"

namespace fqrp {

template <typename result_t> class Aggregator {
public:
  virtual ~Aggregator() = default;
  virtual void aggregate(const conflictCount &) = 0;
  virtual result_t result() const = 0;
};

} // namespace fqrp

#endif