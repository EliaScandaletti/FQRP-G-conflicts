#include <utils/unionFind.h>

fqrp::vehicle_t fqrp::utils::UnionFind::_trash_vehicle = 0;

size_t fqrp::utils::UnionFind::_trash_size = 0;

fqrp::utils::UnionFind::UnionFind(vehicle_t g_size)
    : _parent(g_size, null_vehicle), _size(g_size, 0), _edges_num(0),
      _nodes_num(0) {}

fqrp::vehicle_t &fqrp::utils::UnionFind::parent(vehicle_t v) {
  _trash_vehicle = null_vehicle;
  return v == null_vehicle || v > _parent.size() ? _trash_vehicle
                                                 : _parent[v - 1];
}

const fqrp::vehicle_t &fqrp::utils::UnionFind::parent(vehicle_t v) const {
  return v == null_vehicle || v > _parent.size() ? null_vehicle
                                                 : _parent[v - 1];
}

size_t &fqrp::utils::UnionFind::size(vehicle_t v) {
  _trash_size = 0;
  return v == null_vehicle || v > _size.size() ? _trash_size : _size[v - 1];
}

const size_t &fqrp::utils::UnionFind::size(vehicle_t v) const {
  _trash_size = 0;
  return v == null_vehicle || v > _size.size() ? _trash_size : _size[v - 1];
}

void fqrp::utils::UnionFind::make_set(vehicle_t v) {
  if (!contains(v)) {
    while (_parent.size() < v) {
      _parent.push_back(null_vehicle);
      _size.push_back(0);
    }
    parent(v) = v;
    size(v) = 1;
    _nodes_num++;
  }
}

void fqrp::utils::UnionFind::union_set(vehicle_t a, vehicle_t b) {
  a = find_set(a);
  b = find_set(b);

  if (a != b) {
    if (size(a) < size(b)) {
      std::swap(a, b);
    }
    size(a) += size(b);
    parent(b) = a;
    _edges_num++;
  }
}

fqrp::vehicle_t fqrp::utils::UnionFind::find_set(vehicle_t v) const {
  while (v != parent(v)) {
    v = const_cast<vehicle_t &>(parent(v)) = parent(parent(v));
  }
  return v;
}

bool fqrp::utils::UnionFind::contains(vehicle_t v) const {
  return parent(v) != null_vehicle;
}

size_t fqrp::utils::UnionFind::set_size(vehicle_t v) const {
  v = find_set(v);
  return size(v);
}

size_t fqrp::utils::UnionFind::sets_num() const {
  return _nodes_num - _edges_num;
}

size_t fqrp::utils::UnionFind::edges_num() const { return _edges_num; }

size_t fqrp::utils::UnionFind::nodes_num() const { return _nodes_num; }