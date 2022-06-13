#ifndef FQRP_AGGREGATOR_AVERAGE_H
#define FQRP_AGGREGATOR_AVERAGE_H

#include <core/aggregator.h>
#include <iostream>

#include <fqrp/conflicts.h>
#include <fqrp/types.h>

namespace fqrp {

namespace aggregators {

struct averageCount {
  long double arcType;
  long double AType;
  long double BType;
  c_graph_info_t avg_c_graph_info;
  c_graph_info_t longest_c_graph_info;
  c_graph_info_t most_chains_c_graph_info;
  forest_info_t avg_mixed_forest_info;
  forest_info_t biggest_tree_mixed_forest_info;
  count_t sample_size;
};

class AverageAggregator : public core::Aggregator<conflictCount, averageCount> {
  count_t arcType_sum;
  count_t AType_sum;
  count_t BType_sum;
  c_graph_info_t c_graph_info_sum;
  c_graph_info_t longest_c_graph_info;
  c_graph_info_t most_chains_c_graph_info;
  forest_info_t mixed_forest_info_sum;
  forest_info_t biggest_tree_mixed_forest_info;
  count_t size;

public:
  AverageAggregator() = default;
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