#include <utils/isAForest.h>
#include <utils/unionFind.h>

fqrp::forest_info_t fqrp::utils::isAForest(
    const std::vector<std::pair<vehicle_t, vehicle_t>> &edges) {
  UnionFind uf;
  size_t max_tree_size;

  for (const std::pair<vehicle_t, vehicle_t> &e : edges) {
    uf.make_set(e.first);
    uf.make_set(e.second);

    if (uf.find_set(e.first) == uf.find_set(e.second)) {
      return {
          .is_a_forest = false,
          0,
          0,
          0,
          0,
      };
    }

    uf.union_set(e.first, e.second);
    max_tree_size = std::max(uf.set_size(e.first), max_tree_size);
  }

  return {.is_a_forest = true,
          .tree_num = uf.sets_num(),
          .max_tree_size = max_tree_size,
          .nodes_num = uf.nodes_num(),
          .edges_num = uf.edges_num()};
}