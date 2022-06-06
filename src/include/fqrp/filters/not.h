#ifndef FQRP_FILTER_NOT_H
#define FQRP_FILTER_NOT_H

#include "../filter.h"

namespace fqrp {

namespace filters {

template <typename filter_t> class Not : public filter_t {

public:
  template <typename... args_t> Not(args_t... args);
  bool operator()(const typename filter_t::value_t &value) override;
};

} // namespace filters

} // namespace fqrp

template <typename filter_t>
template <typename... args_t>
fqrp::filters::Not<filter_t>::Not(args_t... args) : filter_t(args...) {}

template <typename filter_t>
bool fqrp::filters::Not<filter_t>::operator()(
    const typename filter_t::value_t &value) {
  return !filter_t::operator()(value);
}

#endif