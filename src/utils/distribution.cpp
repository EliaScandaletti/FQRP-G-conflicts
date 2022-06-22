#include <utils/distribution.h>

#include <limits>

fqrp::utils::distribution::distribution(size_t range)
    : _freqs(range, 0), _sum(0), sample(0),
      _min(std::numeric_limits<vehicle_t>::max()),
      _max(std::numeric_limits<vehicle_t>::min()), _most_freq(0),
      _highest_freq(0) {}

void fqrp::utils::distribution::add(vehicle_t v, size_t freq) {
  if (v >= _freqs.size()) {
    _freqs.insert(_freqs.end(), v - _freqs.size() + 1, 0);
  }
  _freqs[v] += freq;
  _sum += v * freq;
  sample += freq;
  if (freq > 0)
    _min = std::min(_min, v);
  _max = std::max(_max, v);
  if (_freqs[v] > _highest_freq) {
    _most_freq = v;
    _highest_freq = _freqs[v];
  }
}

long double fqrp::utils::distribution::avg() const {
  return static_cast<long double>(_sum) / sample;
}

fqrp::vehicle_t fqrp::utils::distribution::min() const { return _min; }

fqrp::vehicle_t fqrp::utils::distribution::max() const { return _max; }

fqrp::vehicle_t fqrp::utils::distribution::most_freq() const {
  return _most_freq;
}

fqrp::vehicle_t fqrp::utils::distribution::size() const { return sample; }

size_t fqrp::utils::distribution::get(vehicle_t v) const { return _freqs[v]; }

std::ostream &operator<<(std::ostream &os,
                         const fqrp::utils::distribution &dist) {
  os << dist.max();
  for (size_t i = 0; i < dist.max(); i++) {
    os << " " << dist.get(i);
  }
  return os;
}