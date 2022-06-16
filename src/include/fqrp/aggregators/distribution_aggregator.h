#ifndef FQRP_AGGREGATOR_AVERAGE_H
#define FQRP_AGGREGATOR_AVERAGE_H

#include <iostream>

#include <core/aggregator.h>
#include <fqrp/conflicts.h>
#include <fqrp/types.h>
#include <utils/distribution.h>

namespace fqrp {

namespace aggregators {

struct c_graph_dist_t {
  utils::distribution max_length;
  utils::distribution tree_num;
  utils::distribution arcs_num;
  utils::distribution chain_num;
  utils::distribution vehicles_num;
  void add(const c_graph_info_t &v, size_t freq = 1);
};

struct forest_dist_t {
  utils::distribution tree_num;
  utils::distribution max_tree_size;
  utils::distribution nodes_num;
  utils::distribution edges_num;
  void add(const forest_info_t &v, size_t freq = 1);
};

struct dist_count {
  utils::distribution arcType;
  utils::distribution AType;
  utils::distribution BType;
  c_graph_dist_t c_graph_dist;
  forest_dist_t mixed_forest_dist;
};

class DistAggregator : public core::Aggregator<conflictCount, dist_count> {
  dist_count cumulative;

public:
  virtual ~DistAggregator() = default;

  void aggregate(const conflictCount &value) override;
  dist_count result() const override;
};

} // namespace aggregators

} // namespace fqrp

std::ostream &operator<<(std::ostream &,
                         const fqrp::aggregators::c_graph_dist_t &);

std::ostream &operator<<(std::ostream &,
                         const fqrp::aggregators::forest_dist_t &);

std::ostream &operator<<(std::ostream &, const fqrp::aggregators::dist_count &);

#endif