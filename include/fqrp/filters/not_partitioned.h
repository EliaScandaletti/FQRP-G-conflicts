#ifndef FQRP_FILTER_NOT_PARTITIONED_H
#define FQRP_FILTER_NOT_PARTITIONED_H

#include "partitioned.h"

namespace fqrp {

namespace filters {

class IsNotPartitioned : public IsPartitioned {

public:
  virtual ~IsNotPartitioned() = default;
  bool operator()(const Instance &instance) override;
};

} // namespace filters

} // namespace fqrp

#endif