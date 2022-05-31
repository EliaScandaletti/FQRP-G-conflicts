#include <algorithm>

#include <fqrp/instance.h>
#include <fqrp/types.h>

using namespace fqrp;

Instance::Instance(std::vector<vehicle_t> perm)
    : size(perm.size()), permutation(perm) {
}

vehicle_t Instance::getSize() const { return size; }

vehicle_t Instance::sigma(vehicle_t vehicle) const {
  return permutation[vehicle];
}
