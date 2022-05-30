#ifndef ALG1_CPP
#define ALG1_CPP

#include <utility>
#include <vector>

#include "alg1.hpp"
#include "conflicts.hpp"
#include "instance.hpp"

conflictCount alg1(const Instance &instance) {
  const int &size = instance.getSize();

  // memo
  bool outgoingCConflict[size];
  bool incomingCConflict[size];
  std::vector<std::pair<int, int>> potentialMixedConflicts;
  // memo.init
  for (int i = 0; i < size; i++)
    outgoingCConflict[i] = incomingCConflict[i] = false;

  // accumulator
  conflictCount count = {
      .arcType = 0, .AType = 0, .BType = 0, .CType = 0, .mixedType = 0};

  for (int vehicle = 0; vehicle <= size; vehicle++) {

    int CConflict = getCConflict(instance, vehicle);
    if (CConflict != Instance::nullVehicle) {
      count.CType++;
      outgoingCConflict[vehicle - 1] = true;
      incomingCConflict[CConflict - 1] = true;
    }
    
    for (int otherVehicle = vehicle + 1; otherVehicle <= size; otherVehicle++) {
      if (checkAConflict(instance, vehicle, otherVehicle)) {
        count.AType++;
      }
      if ((otherVehicle - vehicle) & 0b1 == 0) {
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

  for (std::pair<int, int> &conflict : potentialMixedConflicts) {
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

#endif