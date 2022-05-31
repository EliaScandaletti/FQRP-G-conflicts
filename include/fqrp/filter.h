#ifndef FQRP_FILTER_H
#define FQRP_FILTER_H

#include "instance.h"

namespace fqrp {

class Filter {
public:
  virtual ~Filter() = default;
  virtual bool operator()(const Instance &instance) = 0;
};

} // namespace fqrp

#endif