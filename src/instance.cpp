#include <algorithm>

#include <fqrp/instance.h>
#include <fqrp/types.h>

using namespace fqrp;

Instance::Instance(std::vector<vehicle_t> perm)
    : size(perm.size()), permutation(new vehicle_t[perm.size()]) {
  std::copy(perm.begin(), perm.end(), this->permutation);
}

Instance::Instance(const vehicle_t *const perm, vehicle_t size)
    : size(size), permutation(new vehicle_t[size]) {
  std::copy(perm, perm + size, permutation);
}

Instance::~Instance() { delete[] permutation; }

vehicle_t Instance::sigma(vehicle_t vehicle) const {
  return permutation[vehicle];
}
