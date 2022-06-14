#ifndef FQRP_FILTER_SYMMETRIC_H
#define FQRP_FILTER_SYMMETRIC_H

#include <fqrp/filter.h>
#include <fqrp/types.h>

namespace fqrp {

namespace filters {

class ExcludeSymmetric : public Filter<Instance> {
public:
  bool operator()(const Instance &value) override;
};

} // namespace filters

} // namespace fqrp

#endif