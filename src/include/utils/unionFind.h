#ifndef UTILS_UNIONFIND_H
#define UTILS_UNIONFIND_H

#include <fqrp/types.h>
#include <vector>

namespace fqrp {

namespace utils {

// 0-index
class UnionFind {
  std::vector<vehicle_t> parent;
  std::vector<size_t> size;
  size_t _edges_num;
  size_t _nodes_num;

public:
  UnionFind(vehicle_t g_size = 0);
  void make_set(vehicle_t v);
  void union_set(vehicle_t a, vehicle_t b);
  vehicle_t find_set(vehicle_t v) const;
  size_t set_size(vehicle_t v) const;
  size_t sets_num() const;
  size_t edges_num() const;
  size_t nodes_num() const;
};

} // namespace utils

} // namespace fqrp

#endif