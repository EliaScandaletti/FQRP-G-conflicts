#ifndef FQRP_GENERATORS_RANDOM_H
#define FQRP_GENERATORS_RANDOM_H

#include <random>
#include <vector>

#include "../generator.h"
#include "../instance.h"

namespace fqrp {

namespace generators {

// Implements Heap's algorithm
// https://en.wikipedia.org/wiki/Heap%27s_algorithm#cite_ref-3
class RandomGenerator : public Generator {
  std::vector<vehicle_t> base;
  std::uniform_real_distribution<double> random_real;
  std::random_device source;

  vehicle_t next_random(vehicle_t min, vehicle_t max);

public:
  RandomGenerator(vehicle_t size);
  virtual ~RandomGenerator() = default;
  Instance next() override;
  bool finished() override;
};

} // namespace generators

} // namespace fqrp

#endif