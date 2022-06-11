#include <utils/isAForest.h>
#include <utils/unionFind.h>

fqrp::utils::forest_info_t::operator bool() const { return is_a_forest; }

fqrp::utils::forest_info_t fqrp::utils::isAForest(
    const std::vector<std::pair<vehicle_t, vehicle_t>> &edges) {
  UnionFind uf;
  size_t max_set_size;

  for (const std::pair<vehicle_t, vehicle_t> &e : edges) {
    uf.make_set(e.first);
    uf.make_set(e.second);

    if (uf.find_set(e.first) == uf.find_set(e.second)) {
      return {.is_a_forest = false};
    }

    uf.union_set(e.first, e.second);
    max_set_size = std::max(uf.set_size(e.first), max_set_size);
  }

  return {.is_a_forest = true,
          .set_num = uf.sets_num(),
          .max_set_size = max_set_size,
          .nodes_num = uf.nodes_num(),
          .edges_num = uf.edges_num()};
}