#ifndef UTILS_ISAFOREST_H
#define UTILS_ISAFOREST_H

#include <fqrp/types.h>
#include <vector>

namespace fqrp {

namespace utils {

struct forest_info_t {
  bool is_a_forest;
  size_t set_num;
  size_t max_set_size;
  size_t nodes_num;
  size_t edges_num;
  operator bool() const;
};

forest_info_t
isAForest(const std::vector<std::pair<vehicle_t, vehicle_t>> &edges);

} // namespace utils

} // namespace fqrp

#endif