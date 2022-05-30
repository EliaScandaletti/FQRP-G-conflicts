#include <algorithm>
#include <cmath>

#include "conflicts.h"

using namespace fqrp;

vehicle_t absDiff(vehicle_t a, vehicle_t b) { return a < b ? b - a : a - b; }

// PRE(1 <= vehicleA < vehicleB <= instance.size)
// PRE((vehicleB - vehicleA) % 2 == 1)
bool fqrp::checkArcConflict(const Instance &instance, vehicle_t vehicleA,
                            vehicle_t vehicleB) {
  return (vehicleA < instance.sigma(vehicleA) &&
          vehicleB > instance.sigma(vehicleB) &&
          2 * instance.sigma(vehicleB) < vehicleA + vehicleB &&
          vehicleA + vehicleB < 2 * instance.sigma(vehicleA));
}

// PRE(1 <= vehicleA < vehicleB <= instance.size)
bool fqrp::checkAConflict(const Instance &instance, vehicle_t vehicleA,
                          vehicle_t vehicleB) {

  vehicle_t diff = absDiff(vehicleA, instance.sigma(vehicleA)) -
                   absDiff(vehicleB, instance.sigma(vehicleA));
  if (diff == 0) {
    return false;
  }
  if (diff < 0) {
    std::swap(vehicleA, vehicleB);
  }
  // assert(abs(vehicleA - sigma(vehicleA)) < abs(vehicleB - sigma(vehicleA)))

  vehicle_t lower, upper;
  if (vehicleB > instance.sigma(vehicleB)) {
    lower = instance.sigma(vehicleB);
    upper = vehicleB;
  } else {
    lower = vehicleB;
    upper = instance.sigma(vehicleB);
  }
  return (lower < instance.sigma(vehicleA) && instance.sigma(vehicleA) < upper);
}

// assert(1 <= vehicleA < vehicleB <= instance.size)
// assert((vehicleB - vehicleA) % 2 == 0)
bool fqrp::checkBConflict(const Instance &instance, vehicle_t vehicleA,
                          vehicle_t vehicleB) {
  return (vehicleA < instance.sigma(vehicleA) &&
          vehicleB > instance.sigma(vehicleB) &&
          instance.sigma(vehicleB) < (vehicleA + vehicleB) / 2 &&
          (vehicleA + vehicleB) / 2 < instance.sigma(vehicleA));
}

// assert(1 <= vehicle <= instance.size)
vehicle_t fqrp::getCConflict(const Instance &instance, vehicle_t vehicle) {

  if (vehicle == instance.sigma(vehicle)) {
    return fqrp::null_vehicle;
  }

  vehicle_t target = 2 * instance.sigma(vehicle) - vehicle;
  if (1 <= target <= instance.getSize()) {
    if (vehicle < instance.sigma(vehicle)) {
      if (instance.sigma(target) < instance.sigma(vehicle)) {
        return target;
      } else {
        return fqrp::null_vehicle;
      }
    } else {
      if (instance.sigma(target) > instance.sigma(vehicle)) {
        return target;
      } else {
        return fqrp::null_vehicle;
      }
    }
  }
}

// assert(1 <= vehicleA <= instance.size)
// assert(1 <= vehicleB <= instance.size)
bool fqrp::checkSameConflictChain(const Instance &instance, vehicle_t vehicleA,
                                  vehicle_t vehicleB) {
  vehicle_t diff = absDiff(vehicleA, instance.sigma(vehicleA)) -
                   absDiff(vehicleB, instance.sigma(vehicleB));
  if (diff > 0) {
    std::swap(vehicleA, vehicleB);
    diff = -diff;
  }

  while (vehicleA != fqrp::null_vehicle && diff < 0) {
    vehicleA = getCConflict(instance, vehicleA);
    if (vehicleA != fqrp::null_vehicle)
      diff = absDiff(vehicleA, instance.sigma(vehicleA)) -
             absDiff(vehicleB, instance.sigma(vehicleB));
  }

  return vehicleA == vehicleB;
}
