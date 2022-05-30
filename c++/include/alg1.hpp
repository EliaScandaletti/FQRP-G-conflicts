#ifndef ALG1_HPP
#define ALG1_HPP

#include "instance.hpp"

struct conflictCount {
  int arcType;
  int AType;
  int BType;
  int CType;
  int mixedType;
};

conflictCount alg1(const Instance &instance);

#endif