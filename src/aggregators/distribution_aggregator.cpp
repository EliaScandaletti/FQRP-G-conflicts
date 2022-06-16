#include <fqrp/aggregators/distribution_aggregator.h>

void fqrp::aggregators::c_graph_dist_t::add(const c_graph_info_t &info,
                                            size_t freq) {
  max_length.add(info.max_length, freq);
  tree_num.add(info.tree_num, freq);
  arcs_num.add(info.arcs_num, freq);
  chain_num.add(info.chain_num, freq);
  vehicles_num.add(info.vehicles_num, freq);
}

void fqrp::aggregators::forest_dist_t::add(const forest_info_t &info,
                                           size_t freq) {
  tree_num.add(info.tree_num, freq);
  max_tree_size.add(info.max_tree_size, freq);
  nodes_num.add(info.nodes_num, freq);
  edges_num.add(info.edges_num, freq);
}

size_t fqrp::aggregators::dist_count::sample_size() const {
  return arcType.size();
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