#ifndef FQRP_UTILS_DISTRIBUTION_H
#define FQRP_UTILS_DISTRIBUTION_H

#include <ostream>
#include <vector>

#include <fqrp/types.h>

namespace fqrp {

namespace utils {

class distribution {
  std::vector<size_t> _dist;
  size_t _sum;
  size_t _size;
  vehicle_t _min;
  vehicle_t _max;

public:
  distribution(size_t range = 0);
  void add(vehicle_t v, size_t freq = 1);
  long double avg() const;
  vehicle_t min() const;
  vehicle_t max() const;
  vehicle_t size() const;
  const std::vector<size_t> &get() const;
};

} // namespace utils

} // namespace fqrp

std::ostream &operator<<(std::ostream &os,
                         const fqrp::utils::distribution &dist);

#endif