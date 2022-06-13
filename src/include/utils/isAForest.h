#ifndef UTILS_ISAFOREST_H
#define UTILS_ISAFOREST_H

#include <fqrp/types.h>
#include <vector>

namespace fqrp {

namespace utils {

forest_info_t
isAForest(const std::vector<std::pair<vehicle_t, vehicle_t>> &edges);

} // namespace utils

} // namespace fqrp

#endif