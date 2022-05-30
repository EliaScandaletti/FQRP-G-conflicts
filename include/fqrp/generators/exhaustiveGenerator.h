#ifndef FQRP_GENERATORS_EXHAUSTIVE_H
#define FQRP_GENERATORS_EXHAUSTIVE_H

#include <vector>

#include "../generator.h"
#include "../instance.h"

namespace fqrp {

// Implements Heap's algorithm
// https://en.wikipedia.org/wiki/Heap%27s_algorithm#cite_ref-3
class ExhaustiveGenerator : public Generator {
  vehicle_t size;
  vehicle_t *perm;
  vehicle_t *buf;
  vehicle_t *c;
  vehicle_t i;

  vehicle_t *cacheNext();

public:
  ExhaustiveGenerator(vehicle_t size);
  ~ExhaustiveGenerator();
  Instance next() override;
  bool finished() override;
};

} // namespace fqrp

#endif