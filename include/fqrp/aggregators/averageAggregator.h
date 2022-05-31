#ifndef FQRP_AGGREGATOR_AVERAGE_H
#define FQRP_AGGREGATOR_AVERAGE_H

#include "../aggregator.h"
#include "../types.h"

struct _result_t {
  long double arcType;
  long double AType;
  long double BType;
  long double CType;
  long double mixedType;
  fqrp::count_t sample_size;
};

namespace fqrp {

namespace aggregators {

class AverageAggregator : public Aggregator<conflictCount, _result_t> {
  conflictCount cumulative;
  count_t size;

public:
  typedef conflictCount value_t;
  typedef _result_t result_t;
  AverageAggregator();
  virtual ~AverageAggregator() = default;

  void aggregate(const value_t &value) override;
  result_t result() const override;

  result_t merge(const AverageAggregator &other);
};

} // namespace aggregators

} // namespace fqrp

#endif