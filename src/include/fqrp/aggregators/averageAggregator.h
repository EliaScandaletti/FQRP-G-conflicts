#ifndef FQRP_AGGREGATOR_AVERAGE_H
#define FQRP_AGGREGATOR_AVERAGE_H

#include <core/aggregator.h>
#include <iostream>

#include "../types.h"

namespace fqrp {

namespace aggregators {

struct averageCount {
  long double arcType;
  long double AType;
  long double BType;
  forest_info_t mixed_forest_info;
  forest_info_t deepest_c_graph_info;
  forest_info_t biggest_c_graph_info;
  forest_info_t avg_c_graph_info;
  count_t sample_size;
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

std::ostream &operator<<(std::ostream &,
                         const fqrp::aggregators::averageCount &);
std::istream &operator>>(std::istream &, fqrp::aggregators::averageCount &);

#endif