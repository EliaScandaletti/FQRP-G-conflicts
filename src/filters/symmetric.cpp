#include <fqrp/filters/symmetric.h>

bool fqrp::filters::ExcludeSymmetric::operator()(const Instance &instance) {
  return instance.sigma(1) <= instance.sigma(instance.size());
}
