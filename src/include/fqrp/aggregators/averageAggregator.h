#ifndef FQRP_AGGREGATOR_AVERAGE_H
#define FQRP_AGGREGATOR_AVERAGE_H

#include <core/aggregator.h>
#include <iostream>

#include <fqrp/conflicts.h>
#include <fqrp/types.h>

namespace fqrp {

namespace aggregators {

struct avg_c_graph_info_t {
  long double max_length;
  long double tree_num;
  long double arcs_num;
  long double chain_num;
  long double vehicles_num;
  explicit avg_c_graph_info_t(long double max_length = 0,
                              long double tree_num = 0,
                              long double arcs_num = 0,
                              long double chain_num = 0,
                              long double vehicles_num = 0);
};

struct avg_forest_info_t {
  long double tree_num;
  long double max_tree_size;
  long double nodes_num;
  long double edges_num;
  explicit avg_forest_info_t(long double tree_num = 0,
                             long double max_tree_size = 0,
                             long double nodes_num = 0,
                             long double edges_num = 0);
};

struct averageCount {
  long double arcType;
  long double AType;
  long double BType;
  avg_c_graph_info_t avg_c_graph_info;
  c_graph_info_t longest_c_graph_info;
  c_graph_info_t most_chains_c_graph_info;
  avg_forest_info_t avg_mixed_forest_info;
  forest_info_t biggest_tree_mixed_forest_info;
  count_t sample_size;
  explicit averageCount(
      long double arcType = 0, long double AType = 0, long double BType = 0,
      const avg_c_graph_info_t &avg_c_graph_info = avg_c_graph_info_t(),
      const c_graph_info_t &longest_c_graph_info = c_graph_info_t(),
      const c_graph_info_t &most_chains_c_graph_info = c_graph_info_t(),
      const avg_forest_info_t &avg_mixed_forest_info = avg_forest_info_t(),
      const forest_info_t &biggest_tree_mixed_forest_info = forest_info_t(),
      count_t sample_size = 0);
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
  AverageAggregator();
  virtual ~AverageAggregator() = default;

  void aggregate(const conflictCount &value) override;
  averageCount result() const override;

  averageCount merge(const AverageAggregator &other);
};

} // namespace aggregators

} // namespace fqrp

std::ostream &operator<<(std::ostream &,
                         const fqrp::aggregators::avg_c_graph_info_t &);
std::istream &operator>>(std::istream &,
                         fqrp::aggregators::avg_c_graph_info_t &);

std::ostream &operator<<(std::ostream &,
                         const fqrp::aggregators::avg_forest_info_t &);
std::istream &operator>>(std::istream &,
                         fqrp::aggregators::avg_forest_info_t &);

std::ostream &operator<<(std::ostream &,
                         const fqrp::aggregators::averageCount &);
std::istream &operator>>(std::istream &, fqrp::aggregators::averageCount &);

#endif