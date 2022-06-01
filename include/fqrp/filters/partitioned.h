#ifndef FQRP_FILTER_PARTITIONED_H
#define FQRP_FILTER_PARTITIONED_H

#include "../filter.h"
#include "../types.h"

namespace fqrp {

namespace filters {

class IsPartitioned : public Filter<Instance> {
public:
  bool operator()(const Instance &value) override;
};

} // namespace filters

} // namespace fqrp

#endif