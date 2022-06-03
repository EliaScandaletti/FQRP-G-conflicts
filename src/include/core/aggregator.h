#ifndef CORE_AGGREGATOR_H
#define CORE_AGGREGATOR_H

namespace core {

template <typename _value_t, typename _result_t> class Aggregator {
public:
  typedef _value_t value_t;
  typedef _result_t result_t;

  virtual ~Aggregator() = default;
  virtual void aggregate(const _value_t &) = 0;
  virtual _result_t result() const = 0;
};

} // namespace core

#endif