#ifndef FQRP_GENERATOR_H
#define FQRP_GENERATOR_H

#include "instance.h"

namespace fqrp {

class Generator {
public:
  virtual ~Generator() = 0;
  virtual Instance next() = 0;
  virtual bool finished() = 0;
};

} // namespace fqrp

#endif