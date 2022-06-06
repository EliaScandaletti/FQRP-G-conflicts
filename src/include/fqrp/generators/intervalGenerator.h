#ifndef FQRP_GENERATORS_INTERVAL_H
#define FQRP_GENERATORS_INTERVAL_H

#include <random>
#include <vector>

#include <core/generator.h>

#include "../types.h"

namespace fqrp {

namespace generators {

class IntervalGenerator : public core::Generator<Instance> {
  vehicle_t size;
  std::uniform_real_distribution<double> random_real;
  std::random_device source;

  vehicle_t random_in_interval(vehicle_t min, vehicle_t max);
  vehicle_t pop_random(std::vector<vehicle_t> &vec);

public:
  IntervalGenerator(vehicle_t size);
  virtual ~IntervalGenerator() = default;
  Instance next() override;
  bool finished() override;
};

} // namespace generators

} // namespace fqrp

#endif