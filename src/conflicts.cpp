#include <algorithm>
#include <cmath>

#include "conflicts.h"

fqrp::vehicle_t absDiff(fqrp::vehicle_t a, fqrp::vehicle_t b) {
  return a < b ? b - a : a - b;
}

// PRE(1 <= vehicleA < vehicleB <= instance.size)
// PRE((vehicleB - vehicleA) % 2 == 1)
bool fqrp::conflicts::checkArcConflict(const Instance &instance,
                                       vehicle_t vehicleA, vehicle_t vehicleB) {
  return (vehicleA < instance.sigma(vehicleA) &&
          vehicleB > instance.sigma(vehicleB) &&
          2 * instance.sigma(vehicleB) < vehicleA + vehicleB &&
          vehicleA + vehicleB < 2 * instance.sigma(vehicleA));
}

// PRE(1 <= vehicleA < vehicleB <= instance.size)
bool fqrp::conflicts::checkAConflict(const Instance &instance,
                                     vehicle_t vehicleA, vehicle_t vehicleB) {

  vehicle_t diffA = absDiff(vehicleA, instance.sigma(vehicleA));
  vehicle_t diffB = absDiff(vehicleB, instance.sigma(vehicleA));
  if (diffA == diffB) {
    return false;
  }
  if (diffB < diffA) {
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
bool fqrp::conflicts::checkBConflict(const Instance &instance,
                                     vehicle_t vehicleA, vehicle_t vehicleB) {
  return (vehicleA < instance.sigma(vehicleA) &&
          vehicleB > instance.sigma(vehicleB) &&
          instance.sigma(vehicleB) < (vehicleA + vehicleB) / 2 &&
          (vehicleA + vehicleB) / 2 < instance.sigma(vehicleA));
}

// assert(1 <= vehicle <= instance.size)
fqrp::vehicle_t fqrp::conflicts::getCConflict(const Instance &instance,
                                              vehicle_t vehicle) {

  if (vehicle == instance.sigma(vehicle)) {
    return null_vehicle;
  }

  vehicle_t target = 2 * instance.sigma(vehicle) - vehicle;
  if (1 <= target && target <= instance.size()) {
    if (vehicle < instance.sigma(vehicle)) {
      if (instance.sigma(target) < instance.sigma(vehicle)) {
        return target;
      }
    } else {
      if (instance.sigma(target) > instance.sigma(vehicle)) {
        return target;
      }
    }
  }
  return null_vehicle;
}

// assert(1 <= vehicleA <= instance.size)
// assert(1 <= vehicleB <= instance.size)
bool fqrp::conflicts::checkSameConflictChain(const Instance &instance,
                                             vehicle_t vehicleA,
                                             vehicle_t vehicleB) {
  vehicle_t diffA = absDiff(vehicleA, instance.sigma(vehicleA));
  vehicle_t diffB = absDiff(vehicleB, instance.sigma(vehicleB));
  if (diffA > diffB) {
    std::swap(vehicleA, vehicleB);
  }

  while (vehicleA != null_vehicle && diffA < diffB) {
    vehicleA = getCConflict(instance, vehicleA);
    if (vehicleA != null_vehicle) {
      diffA = absDiff(vehicleA, instance.sigma(vehicleA));
      diffB = absDiff(vehicleB, instance.sigma(vehicleB));
    }
  }

  return vehicleA == vehicleB;
}
