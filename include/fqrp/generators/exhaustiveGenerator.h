#ifndef FQRP_GENERATORS_EXHAUSTIVE_H
#define FQRP_GENERATORS_EXHAUSTIVE_H

#include <vector>

#include "../generator.h"
#include "../instance.h"

namespace fqrp {

namespace generators {

// Implements Heap's algorithm
// https://en.wikipedia.org/wiki/Heap%27s_algorithm#cite_ref-3
class ExhaustiveGenerator : public Generator {
  vehicle_t size;
  std::vector<vehicle_t> perm;
  std::vector<vehicle_t> buf;
  std::vector<vehicle_t> c;
  vehicle_t i;

  std::vector<vehicle_t> cacheNext();

public:
  ExhaustiveGenerator(vehicle_t size);
  virtual ~ExhaustiveGenerator() = default;
  Instance next() override;
  bool finished() override;
};

} // namespace generators

} // namespace fqrp

#endif