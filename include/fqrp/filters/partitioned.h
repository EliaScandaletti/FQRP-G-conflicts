#ifndef FQRP_FILTER_PARTITIONED_H
#define FQRP_FILTER_PARTITIONED_H

#include "../filter.h"

namespace fqrp {

namespace filters {

class IsPartitioned : public Filter {
public:
  bool operator()(const Instance &instance) override;
};

class IsNotPartitioned : public Filter {
  IsPartitioned filter;

public:
  bool operator()(const Instance &instance) override;
};

} // namespace filters

} // namespace fqrp

#endif