#include <algorithm>

#include <fqrp/instance.h>
#include <fqrp/types.h>

using namespace fqrp;

Instance::Instance(std::vector<vehicle_t> perm) : permutation(perm) {}

vehicle_t Instance::getSize() const { return permutation.size(); }

vehicle_t Instance::sigma(vehicle_t vehicle) const {
  return permutation[vehicle-1];
}
