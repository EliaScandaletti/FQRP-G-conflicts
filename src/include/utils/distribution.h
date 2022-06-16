#ifndef FQRP_UTILS_DISTRIBUTION_H
#define FQRP_UTILS_DISTRIBUTION_H

#include <vector>

#include <fqrp/types.h>

namespace fqrp {

namespace utils {

class distribution {
  std::vector<size_t> _dist;
  size_t sum;
  size_t size;
  vehicle_t _min;
  vehicle_t _max;

public:
  distribution(size_t range = 0);
  void add(vehicle_t v);
  long double avg() const;
  vehicle_t min() const;
  vehicle_t max() const;
  const std::vector<size_t> &dist() const;
};

} // namespace utils

} // namespace fqrp

#endif