#ifndef FQRP_GENERATORS_FILTERED_H
#define FQRP_GENERATORS_FILTERED_H

#include <vector>

#include "../filter.h"
#include "../generator.h"
#include "../instance.h"

namespace fqrp {

namespace generators {

class FilteredGenerator : public Generator {
  Generator *generator;
  Filter *filter;
  Instance buf;

  void cacheNext();

public:
  FilteredGenerator(Generator *generator, Filter *filter);
  virtual ~FilteredGenerator() = default;
  Instance next() override;
  bool finished() override;
};

} // namespace generators

} // namespace fqrp

#endif