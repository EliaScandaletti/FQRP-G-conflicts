#ifndef FQRP_CONFLICTS_HPP
#define FQRP_CONFLICTS_HPP

#include "instance.h"
#include "types.h"

namespace fqrp {

bool checkArcConflict(const fqrp::Instance &instance, fqrp::vehicle_t vehicleA,
                      fqrp::vehicle_t vehicleB);

bool checkAConflict(const fqrp::Instance &instance, fqrp::vehicle_t vehicleA,
                    fqrp::vehicle_t vehicleB);

bool checkBConflict(const fqrp::Instance &instance, fqrp::vehicle_t vehicleA,
                    fqrp::vehicle_t vehicleB);

fqrp::vehicle_t getCConflict(const fqrp::Instance &instance,
                             fqrp::vehicle_t vehicle_t);

bool checkSameConflictChain(const fqrp::Instance &instance,
                            fqrp::vehicle_t vehicleA, fqrp::vehicle_t vehicleB);

} // namespace fqrp

#endif