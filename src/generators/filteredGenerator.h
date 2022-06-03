#ifndef FQRP_GENERATORS_FILTERED_H
#define FQRP_GENERATORS_FILTERED_H

#include <vector>

#include <core/generator.h>

#include "../filter.h"

namespace fqrp {

namespace generators {

template <typename raw_t>
class FilteredGenerator : public core::Generator<raw_t> {
  core::Generator<raw_t> &generator;
  Filter<raw_t> &filter;
  raw_t buf;

  void cacheNext();

public:
  FilteredGenerator(core::Generator<raw_t> &generator, Filter<raw_t> &filter);
  virtual ~FilteredGenerator() = default;
  raw_t next() override;
  bool finished() override;
};

} // namespace generators

} // namespace fqrp

template <typename raw_t>
fqrp::generators::FilteredGenerator<raw_t>::FilteredGenerator(
    core::Generator<raw_t> &generator, Filter<raw_t> &filter)
    : generator(generator), filter(filter), buf() {}

template <typename raw_t>
void fqrp::generators::FilteredGenerator<raw_t>::cacheNext() {
  while (!static_cast<bool>(buf) && !generator.finished()) {
    raw_t temp = generator.next();
    if (filter.operator()(temp)) {
      buf = temp;
    }
  }
}

template <typename raw_t>
raw_t fqrp::generators::FilteredGenerator<raw_t>::next() {
  cacheNext();
  raw_t ret = std::move(buf);
  buf = raw_t();
  return ret;
}

template <typename raw_t>
bool fqrp::generators::FilteredGenerator<raw_t>::finished() {
  cacheNext();
  return !static_cast<bool>(buf);
}

#endif