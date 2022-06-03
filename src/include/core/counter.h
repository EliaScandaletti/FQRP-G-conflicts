#ifndef CORE_COUNTER_H
#define CORE_COUNTER_H

namespace core {

template <typename _raw_t, typename _value_t> class Counter {
public:
  typedef _raw_t raw_t;
  typedef _value_t value_t;

  virtual ~Counter() = default;
  virtual _value_t count(const _raw_t &input) = 0;
};

} // namespace core

#endif