#ifndef FQRP_INSTANCE_H
#define FQRP_INSTANCE_H

#include <vector>

#include "types.h"

namespace fqrp {

class Instance {
  std::vector<vehicle_t> permutation;

public:
  Instance(std::vector<vehicle_t> perm = std::vector<vehicle_t>());
  virtual ~Instance() = default;

  vehicle_t getSize() const;
  vehicle_t sigma(vehicle_t vehicle) const;
};

} // namespace fqrp

#endif