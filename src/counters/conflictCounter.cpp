#include <tuple>

#include <fqrp/counters/conflictCounter.h>

#include <fqrp/conflicts.h>

fqrp::conflictCount
fqrp::counters::conflictCounter::count(const Instance &instance) {
  vehicle_t size = instance.size();

  std::vector<std::pair<vehicle_t, vehicle_t>> BConflicts;
  std::vector<vehicle_t> CConflicts(size, null_vehicle);

  // accumulator
  conflictCount count;

  for (vehicle_t vehicle = 1; vehicle <= size; vehicle++) {

    vehicle_t CConflict = conflicts::getCConflict(instance, vehicle);
    CConflicts[vehicle - 1] = CConflict;

    for (vehicle_t otherVehicle = vehicle + 1; otherVehicle <= size;
         otherVehicle++) {
      if (conflicts::checkAConflict(instance, vehicle, otherVehicle)) {
        count.AType++;
      }
      if (((otherVehicle - vehicle) & 0b1) == 0) {
        if (conflicts::checkBConflict(instance, vehicle, otherVehicle)) {
          BConflicts.push_back({vehicle, otherVehicle});
        }
      } else {
        if (conflicts::checkArcConflict(instance, vehicle, otherVehicle)) {
          count.arcType++;
        }
      }
    }
  }
  count.BType = BConflicts.size();

  std::tie(count.c_graph_info, count.mixed_forest_info) =
      conflicts::getConflictsInfo(BConflicts, CConflicts, size);

  return count;
}