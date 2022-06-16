#include <utils/distribution.h>

#include <limits>

fqrp::utils::distribution::distribution(size_t range)
    : _dist(range, 0), sum(0), size(0),
      _min(std::numeric_limits<size_t>::max()),
      _max(std::numeric_limits<size_t>::min()) {}

void fqrp::utils::distribution::add(vehicle_t v) {
  if (v >= _dist.size()) {
    _dist.insert(_dist.end(), v - _dist.size() + 1, 0);
  }
  _dist[v]++;
  sum += v;
  size++;
  _min = std::min(_min, v);
  _max = std::max(_max, v);
}

long double fqrp::utils::distribution::avg() const {
  return static_cast<long double>(sum) / size;
}

fqrp::vehicle_t fqrp::utils::distribution::min() const { return _min; }

fqrp::vehicle_t fqrp::utils::distribution::max() const { return _max; }

const std::vector<size_t> &fqrp::utils::distribution::dist() const {
  return _dist;
}