#ifndef FQRP_AGGREGATOR_H
#define FQRP_AGGREGATOR_H

namespace fqrp {

template <typename value_t, typename result_t> class Aggregator {
public:
  virtual ~Aggregator() = default;
  virtual void aggregate(const value_t &) = 0;
  virtual result_t result() const = 0;
};

} // namespace fqrp

#endif