#include <utils/isAForest.h>
#include <utils/unionFind.h>

fqrp::forest_info_t fqrp::utils::isAForest(
    const std::vector<std::pair<vehicle_t, vehicle_t>> &edges) {
  UnionFind uf;
  size_t max_tree_size = 0;

  for (const std::pair<vehicle_t, vehicle_t> &e : edges) {
    uf.make_set(e.first);
    uf.make_set(e.second);

    if (uf.find_set(e.first) == uf.find_set(e.second)) {
      return forest_info_t(false);
    }

    uf.union_set(e.first, e.second);
    max_tree_size = std::max(uf.set_size(e.first), max_tree_size);
  }

  return forest_info_t(true, uf.sets_num(), max_tree_size, uf.nodes_num(),
                       uf.edges_num());
}