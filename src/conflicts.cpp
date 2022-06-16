#include <algorithm>
#include <cmath>

#include <fqrp/conflicts.h>
#include <utils/isAForest.h>

fqrp::c_graph_info_t::c_graph_info_t(size_t max_length, size_t tree_num,
                                     size_t arcs_num, size_t chain_num,
                                     size_t vehicles_num)
    : max_length(max_length), tree_num(tree_num), arcs_num(arcs_num),
      chain_num(chain_num), vehicles_num(vehicles_num){};

fqrp::forest_info_t::forest_info_t(bool is_a_forest, size_t tree_num,
                                   size_t max_tree_size, size_t nodes_num,
                                   size_t edges_num)
    : is_a_forest(is_a_forest), tree_num(tree_num),
      max_tree_size(max_tree_size), nodes_num(nodes_num),
      edges_num(edges_num){};

fqrp::conflictCount::conflictCount(count_t arcType, count_t AType,
                                   count_t BType, c_graph_info_t c_graph_info,
                                   forest_info_t mixed_forest_info)
    : arcType(arcType), AType(AType), BType(BType), c_graph_info(c_graph_info),
      mixed_forest_info(mixed_forest_info){};

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
  c_graph_info_t c_graph_info;

  // leaves have height 0
  std::vector<size_t> c_height(size, 0);
  for (size_t subj = 1; subj <= size; subj++) {
    vehicle_t v = subj;

    size_t chain_length = 0;
    while (v != null_vehicle && (c_height[v - 1] < chain_length ||
                                 // c_height[v - 1] == 0 && chain_length == 0
                                 c_height[v - 1] + chain_length == 0)) {
      c_height[v - 1] = chain_length;
      chain_length++;
      v = CConflicts[v - 1];
    }

    c_graph_info.max_length = std::max(c_graph_info.max_length, chain_length);
  }

  for (size_t subj = 1; subj <= size; subj++) {
    vehicle_t obj = CConflicts[subj - 1];
    if (obj != null_vehicle) {
      c_graph_info.arcs_num++;
      if (c_height[subj - 1] == 0) {
        c_graph_info.chain_num++;
      }
    } else if (c_height[subj - 1] > 0) {
      c_graph_info.tree_num++;
    }
  }
  c_graph_info.vehicles_num = c_graph_info.arcs_num + c_graph_info.tree_num;

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

  forest_info_t mixed_forest_info = utils::isAForest(mixedConflicts);

  return {c_graph_info, mixed_forest_info};
}

std::ostream &operator<<(std::ostream &os, const fqrp::c_graph_info_t &info) {
  os << info.max_length << " ";
  os << info.tree_num << " ";
  os << info.arcs_num << " ";
  os << info.vehicles_num;
  return os;
}

std::ostream &operator<<(std::ostream &os, const fqrp::forest_info_t &info) {
  os << info.is_a_forest << " ";
  os << info.tree_num << " ";
  os << info.max_tree_size << " ";
  os << info.nodes_num << " ";
  os << info.edges_num;
  return os;
}

std::ostream &operator<<(std::ostream &os, const fqrp::conflictCount &count) {
  os << count.arcType << " ";
  os << count.AType << " ";
  os << count.BType << " ";
  os << count.c_graph_info << " ";
  os << count.mixed_forest_info << " ";
  os << count.mixed_forest_info;
  return os;
}
