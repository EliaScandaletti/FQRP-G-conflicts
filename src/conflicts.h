#ifndef FQRP_CONFLICTS_HPP
#define FQRP_CONFLICTS_HPP

#include <fqrp/instance.h>
#include <fqrp/types.h>

namespace fqrp {

bool checkArcConflict(const Instance &instance, vehicle_t vehicleA,
                      vehicle_t vehicleB);

bool checkAConflict(const Instance &instance, vehicle_t vehicleA,
                    vehicle_t vehicleB);

bool checkBConflict(const Instance &instance, vehicle_t vehicleA,
                    vehicle_t vehicleB);

vehicle_t getCConflict(const Instance &instance, vehicle_t vehicle);

bool checkSameConflictChain(const Instance &instance, vehicle_t vehicleA,
                            vehicle_t vehicleB);

} // namespace fqrp

#endif