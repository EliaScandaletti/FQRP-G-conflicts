#include <utils/distribution.h>

#include <limits>

fqrp::utils::distribution::distribution(size_t range)
    : _dist(range, 0), _sum(0), _size(0),
      _min(std::numeric_limits<size_t>::max()),
      _max(std::numeric_limits<size_t>::min()) {}

void fqrp::utils::distribution::add(vehicle_t v, size_t freq) {
  if (v >= _dist.size()) {
    _dist.insert(_dist.end(), v - _dist.size() + 1, 0);
  }
  _dist[v] += freq;
  _sum += v * freq;
  _size += freq;
  _min = std::min(_min, v);
  _max = std::max(_max, v);
}

long double fqrp::utils::distribution::avg() const {
  return static_cast<long double>(_sum) / _size;
}

fqrp::vehicle_t fqrp::utils::distribution::min() const { return _min; }

fqrp::vehicle_t fqrp::utils::distribution::max() const { return _max; }

fqrp::vehicle_t fqrp::utils::distribution::size() const { return _size; }

const std::vector<size_t> &fqrp::utils::distribution::get() const {
  return _dist;
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::utils::distribution &dist) {
  const auto &_dist = dist.get();
  for (size_t i = 0; i < _dist.size(); i++) {
    if (i != 0) {
      os << " ";
    }
    os << _dist[i];
  }
}