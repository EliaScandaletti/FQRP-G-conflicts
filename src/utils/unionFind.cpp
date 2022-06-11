#include <utils/unionFind.h>

fqrp::utils::UnionFind::UnionFind(vehicle_t g_size)
    : parent(g_size), size(g_size), _nodes_num(0), _edges_num(0) {}

void fqrp::utils::UnionFind::make_set(vehicle_t v) {
  while (parent.size() <= v) {
    parent.push_back(-1);
    size.push_back(1);
  }
  parent[v] = v;
  size[v] = 1;
  _nodes_num++;
}

void fqrp::utils::UnionFind::union_set(vehicle_t a, vehicle_t b) {
  a = find_set(a);
  b = find_set(b);

  if (a != b) {
    if (size[a] < size[b]) {
      std::swap(a, b);
    }
    size[a] += size[b];
    parent[b] = a;
    _edges_num++;
  }
}

fqrp::vehicle_t fqrp::utils::UnionFind::find_set(vehicle_t v) const {
  auto p = const_cast<std::vector<vehicle_t> &>(parent);
  while (v != p[v]) {
    v = p[v] = p[p[v]];
  }
  return v;
}

size_t fqrp::utils::UnionFind::set_size(vehicle_t v) const {
  v = find_set(v);
  return size[v];
}

size_t fqrp::utils::UnionFind::sets_num() const {
  return _nodes_num - _edges_num;
}

size_t fqrp::utils::UnionFind::edges_num() const { return _edges_num; }

size_t fqrp::utils::UnionFind::nodes_num() const { return _nodes_num; }