#include <fqrp/generators/randomGenerator.h>

using namespace fqrp;
using namespace fqrp::generators;

RandomGenerator::RandomGenerator(vehicle_t size)
    : base(size), random_real(0, 1), source() {
  for (vehicle_t i = 0; i < size; i += 1) {
    base[i] = i + 1;
  }
}

vehicle_t RandomGenerator::next_random(vehicle_t min, vehicle_t max) {
  return min + random_real(source) * (max - min);
}

Instance RandomGenerator::next() {
  for (vehicle_t i = 0; i < base.size(); i++) {
    vehicle_t j = next_random(i, base.size());
    std::swap(base[i], base[j]);
  }

  return Instance(base);
}

bool RandomGenerator::finished() { return false; }
