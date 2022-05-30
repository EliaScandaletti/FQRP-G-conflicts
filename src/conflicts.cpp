#ifndef CONFLICTS_HPP
#define CONFLICTS_HPP

#include <algorithm>
#include <cmath>

#include "fqrp.h"

using namespace fqrp;

vehicle_t absDiff(vehicle_t a, vehicle_t b) { return a < b ? b - a : a - b; }

// PRE(1 <= vehicleA < vehicleB <= instance.size)
// PRE((vehicleB - vehicleA) % 2 == 1)
bool checkArcConflict(const Instance &instance, vehicle_t vehicleA,
                      vehicle_t vehicleB) {
  return (vehicleA < instance.sigma(vehicleA) &&
          vehicleB > instance.sigma(vehicleB) &&
          2 * instance.sigma(vehicleB) < vehicleA + vehicleB &&
          vehicleA + vehicleB < 2 * instance.sigma(vehicleA));
}

// PRE(1 <= vehicleA < vehicleB <= instance.size)
bool checkAConflict(const Instance &instance, vehicle_t vehicleA,
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

bool checkBConflict(const Instance &instance, vehicle_t vehicleA,
                    vehicle_t vehicleB) {}

vehicle_t getCConflict(const Instance &instance, vehicle_t vehicle_t) {}

bool checkSameConflictChain(const Instance &instance, vehicle_t vehicleA,
                            vehicle_t vehicleB) {}

#endif