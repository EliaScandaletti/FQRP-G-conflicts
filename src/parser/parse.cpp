#include <parser/parse.h>

using fqrp::vehicle_t;
using fqrp::aggregators::c_graph_dist_t;
using fqrp::aggregators::dist_count;
using fqrp::aggregators::forest_dist_t;
using fqrp::utils::distribution;

std::istream &operator>>(std::istream &is, distribution &dist) {
  vehicle_t size;
  is >> size;
  if (!is)
    throw "Bad input!";
  dist = distribution(size);

  for (vehicle_t i = 0; i < size; i++) {
    size_t freq;
    is >> freq;
    if (!is)
      throw "Bad input!";
    dist.add(i, freq);
  }
  return is;
}

std::istream &operator>>(std::istream &is, c_graph_dist_t &graph_dist) {
  is >> graph_dist.max_length;
  is >> graph_dist.tree_num;
  is >> graph_dist.arcs_num;
  is >> graph_dist.chain_num;
  is >> graph_dist.vehicles_num;
  return is;
}

std::istream &operator>>(std::istream &is, forest_dist_t &forest_dist) {
  is >> forest_dist.is_forest;
  is >> forest_dist.tree_num;
  is >> forest_dist.max_tree_size;
  is >> forest_dist.nodes_num;
  is >> forest_dist.edges_num;
  return is;
}

std::istream &operator>>(std::istream &is, dist_count &count) {
  is >> count.arcType;
  is >> count.AType;
  is >> count.BType;
  is >> count.c_graph_dist;
  is >> count.mixed_forest_dist;
  return is;
}

std::vector<std::tuple<vehicle_t, dist_count>> parser::parse(std::istream &is) {
  std::vector<std::tuple<vehicle_t, dist_count>> ret;
  vehicle_t size;
  is >> size;
  while (is) {
    dist_count count;
    is >> count;
    ret.push_back({size, count});
    is >> size;
  }
  return ret;
}