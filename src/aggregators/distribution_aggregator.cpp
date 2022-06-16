#include <fqrp/aggregators/distribution_aggregator.h>

void fqrp::aggregators::c_graph_dist_t::add(const c_graph_info_t &info,
                                            size_t freq) {
  max_length.add(info.max_length);
  tree_num.add(info.tree_num);
  arcs_num.add(info.arcs_num);
  chain_num.add(info.chain_num);
  vehicles_num.add(info.vehicles_num);
}

void fqrp::aggregators::forest_dist_t::add(const forest_info_t &info,
                                           size_t freq) {
  tree_num.add(info.tree_num);
  max_tree_size.add(info.max_tree_size);
  nodes_num.add(info.nodes_num);
  edges_num.add(info.edges_num);
}

void fqrp::aggregators::DistAggregator::aggregate(const conflictCount &value) {
  cumulative.arcType.add(value.arcType);
  cumulative.AType.add(value.AType);
  cumulative.BType.add(value.BType);
  cumulative.c_graph_dist.add(value.c_graph_info);
  cumulative.mixed_forest_dist.add(value.mixed_forest_info);
}

fqrp::aggregators::dist_count
fqrp::aggregators::DistAggregator::result() const {
  return cumulative;
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::c_graph_dist_t &info) {
  os << info.max_length << " ";
  os << info.tree_num << " ";
  os << info.arcs_num << " ";
  os << info.chain_num << " ";
  os << info.vehicles_num;
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::forest_dist_t &info) {
  os << info.tree_num << " ";
  os << info.max_tree_size << " ";
  os << info.nodes_num << " ";
  os << info.edges_num;
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::dist_count &count) {
  os << count.arcType << " ";
  os << count.AType << " ";
  os << count.BType << " ";
  os << count.c_graph_dist << " ";
  os << count.mixed_forest_dist;
  return os;
}