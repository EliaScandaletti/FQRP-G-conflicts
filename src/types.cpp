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