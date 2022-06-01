#ifndef FQRP_FILTER_H
#define FQRP_FILTER_H

namespace fqrp {

template <typename _value_t> class Filter {
public:
  typedef _value_t value_t;

  virtual ~Filter() = default;
  virtual bool operator()(const _value_t &instance) = 0;
};

} // namespace fqrp

#endif