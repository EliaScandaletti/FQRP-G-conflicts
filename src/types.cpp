#include <fqrp/types.h>

fqrp::Instance::Instance(std::vector<fqrp::vehicle_t> perm)
    : permutation(perm) {}

fqrp::vehicle_t fqrp::Instance::size() const { return permutation.size(); }

fqrp::vehicle_t fqrp::Instance::sigma(vehicle_t vehicle) const {
  return permutation[vehicle - 1];
}

fqrp::Instance::operator bool() const { return !permutation.empty(); }

std::ostream &operator<<(std::ostream &os, const fqrp::Instance &instance) {
  if (instance.permutation.size() > 0) {
    os << instance.permutation[0];
    for (fqrp::vehicle_t i = 1; i < instance.permutation.size(); i++) {
      os << " " << instance.permutation[i];
    }
  }
  return os;
}

std::istream &operator>>(std::istream &is, fqrp::Instance &instance) {
  instance.permutation.clear();
  fqrp::vehicle_t next;
  while (is >> next) {
    instance.permutation.push_back(next);
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, const fqrp::c_graph_info_t &info) {
  return os << info.tree_num << " " << info.max_depth << " " << info.arcs_num
            << " " << info.vertices_num;
}
std::istream &operator>>(std::istream &is, fqrp::c_graph_info_t &info) {
  return is >> info.tree_num >> info.max_depth >> info.arcs_num >>
         info.vertices_num;
}

std::ostream &operator<<(std::ostream &os, const fqrp::forest_info_t &info) {
  os << info.is_a_forest;
  if (info.is_a_forest)
    return os << " " << info.tree_num << " " << info.max_tree_size << " "
              << info.nodes_num << " " << info.edges_num;
}

std::istream &operator>>(std::istream &is, fqrp::forest_info_t &info) {
  is >> info.is_a_forest;
  if (info.is_a_forest)
    return is >> info.tree_num >> info.max_tree_size >> info.nodes_num >>
           info.edges_num;
}

std::ostream &operator<<(std::ostream &os, const fqrp::conflictCount &count) {
  os << count.arcType << " " << count.AType << " " << count.BType << " "
     << count.c_graph_info << " " << count.mixed_forest_info << " "
     << count.mixed_forest_info;
  return os;
}

std::istream &operator>>(std::istream &is, fqrp::conflictCount &count) {
  is >> count.arcType >> count.AType >> count.BType >> count.c_graph_info >>
      count.mixed_forest_info >> count.mixed_forest_info;
  return is;
}