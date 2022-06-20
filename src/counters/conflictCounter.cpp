#include <tuple>

#include <fqrp/counters/conflictCounter.h>

#include <fqrp/conflicts.h>

fqrp::counters::logger_t::logger_t(condition_t test, std::ostream &os)
    : test(test), os(os) {}

void fqrp::counters::logger_t::operator()(const Instance &instance,
                                          const conflictCount &count) {
  if (test(instance, count)) {
    os << instance << std::endl;
  }
}

fqrp::counters::conflictCounter::conflictCounter(
    const std::vector<logger_t> &loggers)
    : loggers(loggers) {}

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

  for (auto &&logger : loggers) {
    logger(instance, count);
  }

  return count;
}