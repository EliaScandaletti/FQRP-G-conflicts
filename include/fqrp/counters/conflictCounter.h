#ifndef FQRP_CONFLICT_COUNTER_H
#define FQRP_CONFLICT_COUNTER_H

#include <core/counter.h>

#include "../types.h"

namespace fqrp {

namespace counters {

class conflictCounter : public core::Counter<Instance, conflictCount> {
public:
  conflictCount count(const Instance &instance) override;
};

} // namespace counters

} // namespace fqrp

#endif