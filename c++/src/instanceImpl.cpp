#include <algorithm>
#include <vector>

#include "instanceImpl.hpp"

InstanceImpl::InstanceImpl(std::vector<int> perm)
    : Instance(perm.size()), permutation(new int[perm.size()]) {
  std::copy(perm.begin(), perm.end(), this->permutation);
}

InstanceImpl::InstanceImpl(const int *const perm, int size)
    : Instance(size), permutation(new int[size]) {
  std::copy(perm, perm + size, permutation);
}

int InstanceImpl::sigma(const int &vehicle) const {
  return permutation[vehicle];
}
