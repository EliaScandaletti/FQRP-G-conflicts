#include <fqrp/filters/partitioned.h>

using namespace fqrp;
using namespace fqrp::filters;

bool IsPartitioned::operator()(const Instance &instance) {
  vehicle_t i = 0;
  vehicle_t maxSigma = 1;

  while (i < instance.getSize() && maxSigma > i) {
    i++;
    maxSigma = std::max(maxSigma, instance.sigma(i));
  }

  return i < instance.getSize();
}

bool IsNotPartitioned::operator()(const Instance &instance) {
  return !filter(instance);
}
