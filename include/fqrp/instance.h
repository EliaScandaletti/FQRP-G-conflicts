#ifndef FQRP_INSTANCE_H
#define FQRP_INSTANCE_H

#include <vector>

#include "types.h"

namespace fqrp {

class Instance {
  const vehicle_t size;
  vehicle_t *const permutation;

public:
  Instance(std::vector<vehicle_t> perm);
  Instance(const vehicle_t *const perm, vehicle_t size);
  ~Instance();

  vehicle_t getSize() const;
  vehicle_t sigma(vehicle_t vehicle) const;
};

} // namespace fqrp

#endif