#ifndef INSTANCE_IMPL_HPP
#define INSTANCE_IMPL_HPP

#include <vector>

#include "instance.hpp"

class InstanceImpl : Instance {
  const int *const permutation;

public:
  InstanceImpl(std::vector<int> perm);
  InstanceImpl(const int *const perm, int size);

  int sigma(const int &vehicle) const override final;
};

#endif