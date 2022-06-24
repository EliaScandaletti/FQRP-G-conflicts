#ifndef FQRP_UTILS_DISTRIBUTION_H
#define FQRP_UTILS_DISTRIBUTION_H

#include <ostream>
#include <vector>

#include <fqrp/types.h>

namespace fqrp {

namespace utils {

class distribution {
  std::vector<size_t> _freqs;
  size_t _sum;
  size_t sample;
  vehicle_t _min;
  vehicle_t _max;
  vehicle_t _most_freq;
  size_t _highest_freq;

public:
  distribution(size_t range = 0);
  void add(vehicle_t v, size_t freq = 1);
  long double avg() const;
  vehicle_t min() const;
  vehicle_t max() const;
  vehicle_t most_freq() const;
  size_t size() const;
  long double quantile(double part) const;
  size_t get(vehicle_t v) const;
};

} // namespace utils

} // namespace fqrp

std::ostream &operator<<(std::ostream &os,
                         const fqrp::utils::distribution &dist);

#endif