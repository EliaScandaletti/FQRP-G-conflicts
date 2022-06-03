#ifndef FQRP_AGGREGATOR_AVERAGE_H
#define FQRP_AGGREGATOR_AVERAGE_H

#include <core/aggregator.h>

#include "../types.h"

namespace fqrp {

namespace aggregators {

struct averageCount {
  long double arcType;
  long double AType;
  long double BType;
  long double CType;
  long double mixedType;
  fqrp::count_t sample_size;
};

class AverageAggregator : public core::Aggregator<conflictCount, averageCount> {
  conflictCount cumulative;
  count_t size;

public:
  AverageAggregator();
  virtual ~AverageAggregator() = default;

  void aggregate(const conflictCount &value) override;
  averageCount result() const override;

  averageCount merge(const AverageAggregator &other);
};

} // namespace aggregators

} // namespace fqrp

#endif