#include <utility>
#include <vector>

#include "conflicts.h"
#include <fqrp/algorithms.h>

using namespace fqrp;

conflictCount fqrp::getConflictCount(const Instance &instance) {
  vehicle_t size = instance.getSize();

  // memo
  bool outgoingCConflict[size];
  bool incomingCConflict[size];
  std::vector<std::pair<vehicle_t, vehicle_t>> potentialMixedConflicts;
  // memo.init
  for (vehicle_t i = 0; i < size; i++)
    outgoingCConflict[i] = incomingCConflict[i] = false;

  // accumulator
  conflictCount count;

  for (vehicle_t vehicle = 1; vehicle <= size; vehicle++) {

    vehicle_t CConflict = getCConflict(instance, vehicle);
    if (CConflict != fqrp::null_vehicle) {
      count.CType++;
      outgoingCConflict[vehicle - 1] = true;
      incomingCConflict[CConflict - 1] = true;
    }

    for (vehicle_t otherVehicle = vehicle + 1; otherVehicle <= size;
         otherVehicle++) {
      if (checkAConflict(instance, vehicle, otherVehicle)) {
        count.AType++;
      }
      if (((otherVehicle - vehicle) & 0b1) == 0) {
        if (checkBConflict(instance, vehicle, otherVehicle)) {
          count.BType++;
          potentialMixedConflicts.push_back({vehicle, otherVehicle});
        }
      } else {
        if (checkArcConflict(instance, vehicle, otherVehicle)) {
          count.arcType++;
        }
      }
    }
  }

  for (const std::pair<vehicle_t, vehicle_t> &conflict :
       potentialMixedConflicts) {
    if (incomingCConflict[conflict.first] &&
        outgoingCConflict[conflict.first] &&
        incomingCConflict[conflict.second] &&
        outgoingCConflict[conflict.second] &&
        !checkSameConflictChain(instance, conflict.first, conflict.second)) {
      count.mixedType++;
    }
  }

  return count;
}
