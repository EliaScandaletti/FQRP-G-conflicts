#include <fqrp/filters/not_partitioned.h>

using namespace fqrp;
using namespace fqrp::filters;

bool IsNotPartitioned::operator()(const Instance &instance) {
  return !IsPartitioned::operator()(instance);
}
