#include <algorithm>
#include <cmath>
#include <tuple>

#include <fqrp/conflicts.h>
#include <utils/isAForest.h>

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
bool fqrp::conflicts::checkSameConflictChain(
    const std::vector<vehicle_t> &conflicts, vehicle_t vehicleA,
    vehicle_t vehicleB) {

  auto sigma = [&conflicts](vehicle_t vehicle) -> vehicle_t {
    if (vehicle == null_vehicle)
      return null_vehicle;
    return conflicts[vehicle - 1];
  };

  vehicle_t diffA = absDiff(vehicleA, sigma(vehicleA));
  vehicle_t diffB = absDiff(vehicleB, sigma(vehicleB));
  if (diffA > diffB) {
    std::swap(vehicleA, vehicleB);
  }

  while (vehicleA != null_vehicle && diffA < diffB) {
    vehicleA = sigma(vehicleA);
    diffA = absDiff(vehicleA, sigma(vehicleA));
  }

  return vehicleA == vehicleB;
}

std::tuple<fqrp::c_graph_info_t, fqrp::forest_info_t>
fqrp::conflicts::getConflictsInfo(
    const std::vector<std::pair<vehicle_t, vehicle_t>> &BConflicts,
    const std::vector<vehicle_t> &CConflicts, vehicle_t size) {

  // leaves have height 0
  std::vector<size_t> c_height(size, 0);
  size_t max_height = 0;
  for (size_t subj = 1; subj <= size; subj++) {
    vehicle_t v = subj;

    size_t height = 0;
    while (v != null_vehicle && c_height[v - 1] < height) {
      c_height[v - 1] = height;
      height++;
      v = CConflicts[v - 1];
    }
    max_height = std::max(max_height, height);
  }

  size_t arcs_num = 0;
  size_t roots_num = 0;
  size_t leaves_num = 0;
  for (size_t subj = 1; subj <= size; subj++) {
    vehicle_t obj = CConflicts[subj - 1];
    if (obj != null_vehicle) {
      arcs_num++;
      if (c_height[subj - 1] == 0) {
        leaves_num++;
      }
    } else if (c_height[subj - 1] > 0) {
      roots_num++;
    }
  }

  std::vector<std::pair<vehicle_t, vehicle_t>> mixedConflicts;
  for (const std::pair<vehicle_t, vehicle_t> &conflict : BConflicts) {
    if (CConflicts[conflict.first - 1] != null_vehicle &&
        c_height[conflict.first - 1] > 0 &&
        CConflicts[conflict.second - 1] != null_vehicle &&
        c_height[conflict.second - 1] > 0 &&
        !conflicts::checkSameConflictChain(CConflicts, conflict.first,
                                           conflict.second)) {
      mixedConflicts.push_back(conflict);
    }
  }

  return {{.max_length = max_height + 1,
           .tree_num = roots_num,
           .arcs_num = arcs_num,
           .chain_num = leaves_num,
           .vehicles_num = arcs_num + roots_num},
          utils::isAForest(mixedConflicts)};
}

std::ostream &operator<<(std::ostream &os, const fqrp::c_graph_info_t &info) {
  return os << info.max_length << " " << info.tree_num << " " << info.arcs_num
            << " " << info.vehicles_num;
}
std::istream &operator>>(std::istream &is, fqrp::c_graph_info_t &info) {
  return is >> info.max_length >> info.tree_num >> info.arcs_num >>
         info.vehicles_num;
}

std::ostream &operator<<(std::ostream &os, const fqrp::forest_info_t &info) {
  os << info.is_a_forest;
  if (info.is_a_forest)
    os << " " << info.tree_num << " " << info.max_tree_size << " "
       << info.nodes_num << " " << info.edges_num;
  return os;
}

std::istream &operator>>(std::istream &is, fqrp::forest_info_t &info) {
  is >> info.is_a_forest;
  if (info.is_a_forest)
    is >> info.tree_num >> info.max_tree_size >> info.nodes_num >>
        info.edges_num;
  return is;
}

std::ostream &operator<<(std::ostream &os, const fqrp::conflictCount &count) {
  os << count.arcType << " " << count.AType << " " << count.BType << " "
     << count.c_graph_info << " " << count.mixed_forest_info << " "
     << count.mixed_forest_info;
  return os;
}

std::istream &operator>>(std::istream &is, fqrp::conflictCount &count) {
  is >> count.arcType >> count.AType >> count.BType >> count.c_graph_info >>
      count.mixed_forest_info >> count.mixed_forest_info;
  return is;
}