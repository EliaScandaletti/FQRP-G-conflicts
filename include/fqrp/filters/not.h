#ifndef FQRP_FILTER_NOT_H
#define FQRP_FILTER_NOT_H

#include "../filter.h"

namespace fqrp {

namespace filters {

template <typename T> class Not : public Filter {
  T filter;

public:
  bool operator()(const Instance &instance) override;
};

} // namespace filters

} // namespace fqrp

template <typename T>
bool fqrp::filters::Not<T>::operator()(const Instance &instance) {
  return !filter(instance);
}

#endif