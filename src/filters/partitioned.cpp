#include <fqrp/filters/partitioned.h>

bool fqrp::filters::IsPartitioned::operator()(const Instance &instance) {
  vehicle_t i = 0;
  vehicle_t maxSigma = 1;

  while (i < instance.size() && maxSigma > i) {
    i++;
    maxSigma = std::max(maxSigma, instance.sigma(i));
  }

  return i < instance.size();
}
