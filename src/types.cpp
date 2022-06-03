#include "types.h"

fqrp::conflictCount::conflictCount()
    : arcType(0), AType(0), BType(0), CType(0), mixedType(0) {}

fqrp::Instance::Instance(std::vector<fqrp::vehicle_t> perm)
    : permutation(perm) {}

fqrp::vehicle_t fqrp::Instance::size() const { return permutation.size(); }

fqrp::vehicle_t fqrp::Instance::sigma(vehicle_t vehicle) const {
  return permutation[vehicle - 1];
}

fqrp::Instance::operator bool() const { return !permutation.empty(); }