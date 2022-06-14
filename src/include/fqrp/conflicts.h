#ifndef FQRP_CONFLICTS_HPP
#define FQRP_CONFLICTS_HPP

#include <fqrp/types.h>

namespace fqrp {

struct c_graph_info_t {
  size_t max_length;
  size_t tree_num;
  size_t arcs_num;
  size_t chain_num;
  size_t vehicles_num;
  explicit c_graph_info_t(size_t max_length = 0, size_t tree_num = 0,
                          size_t arcs_num = 0, size_t chain_num = 0,
                          size_t vehicles_num = 0);
};

struct forest_info_t {
  bool is_a_forest;
  size_t tree_num;
  size_t max_tree_size;
  size_t nodes_num;
  size_t edges_num;
  explicit forest_info_t(bool is_a_forest = false, size_t tree_num = 0,
                         size_t max_tree_size = 0, size_t nodes_num = 0,
                         size_t edges_num = 0);
};

struct conflictCount {
  count_t arcType;
  count_t AType;
  count_t BType;
  c_graph_info_t c_graph_info;
  forest_info_t mixed_forest_info;
  explicit conflictCount(
      count_t arcType = 0, count_t AType = 0, count_t BType = 0,
      c_graph_info_t c_graph_info = c_graph_info_t(),
      forest_info_t mixed_forest_info = forest_info_t());
};

namespace conflicts {

bool checkArcConflict(const Instance &instance, vehicle_t vehicleA,
                      vehicle_t vehicleB);

bool checkAConflict(const Instance &instance, vehicle_t vehicleA,
                    vehicle_t vehicleB);

bool checkBConflict(const Instance &instance, vehicle_t vehicleA,
                    vehicle_t vehicleB);

vehicle_t getCConflict(const Instance &instance, vehicle_t vehicle);

bool checkSameConflictChain(const std::vector<vehicle_t> &instance,
                            vehicle_t vehicleA, vehicle_t vehicleB);

std::tuple<c_graph_info_t, forest_info_t>
getConflictsInfo(const std::vector<std::pair<vehicle_t, vehicle_t>> &BConflicts,
                 const std::vector<vehicle_t> &CConflicts, vehicle_t size);

} // namespace conflicts

} // namespace fqrp

std::ostream &operator<<(std::ostream &, const fqrp::c_graph_info_t &);
std::istream &operator>>(std::istream &, fqrp::c_graph_info_t &);

std::ostream &operator<<(std::ostream &, const fqrp::forest_info_t &);
std::istream &operator>>(std::istream &, fqrp::forest_info_t &);

std::ostream &operator<<(std::ostream &, const fqrp::conflictCount &);
std::istream &operator>>(std::istream &, fqrp::conflictCount &);

#endif