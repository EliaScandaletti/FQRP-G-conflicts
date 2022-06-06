#include <fqrp/generators/intervalGenerator.h>

fqrp::generators::IntervalGenerator::IntervalGenerator(vehicle_t size)
    : size(size), random_real(0, 1), source() {}

fqrp::vehicle_t
fqrp::generators::IntervalGenerator::random_in_interval(vehicle_t min,
                                                        vehicle_t max) {
  return min + random_real(source) * (max - min);
}

fqrp::vehicle_t
fqrp::generators::IntervalGenerator::pop_random(std::vector<vehicle_t> &vec) {
  vehicle_t idx = random_in_interval(0, vec.size());
  std::swap(vec[idx], vec[vec.size() - 1]);
  vehicle_t ret = vec[vec.size() - 1];
  vec.pop_back();
  return ret;
}

fqrp::Instance fqrp::generators::IntervalGenerator::next() {
  std::vector<vehicle_t> perm(size);
  vehicle_t maxInt = 0;
  std::vector<vehicle_t> freeVehicles(size);
  freeVehicles.clear();
  std::vector<vehicle_t> freeDestinations(size);
  freeDestinations.clear();

  vehicle_t pi_next = random_in_interval(2, size + 1);
  perm[0] = pi_next;
  maxInt = pi_next;
  for (vehicle_t i = 1; i < maxInt; i++) {
    freeDestinations.push_back(i);
    freeVehicles.push_back(i + 1);
  }

  while (maxInt < size) {
    bool dir = random_in_interval(0, 2);

    if (dir) {
      pi_next = random_in_interval(maxInt + 1, size + 1);
      vehicle_t k_next = pop_random(freeVehicles);
      perm[k_next - 1] = pi_next;
      for (vehicle_t i = maxInt + 1; i < pi_next; i++) {
        freeDestinations.push_back(i);
        freeVehicles.push_back(i);
      }
      freeVehicles.push_back(pi_next);
      maxInt = pi_next;

    } else {
      vehicle_t k_next = random_in_interval(maxInt + 1, size + 1);
      pi_next = pop_random(freeDestinations);
      perm[k_next - 1] = pi_next;
      for (vehicle_t i = maxInt + 1; i < k_next; i++) {
        freeDestinations.push_back(i);
        freeVehicles.push_back(i);
      }
      freeDestinations.push_back(k_next);
      maxInt = k_next;
    }
  }

  while (freeVehicles.size() > 0) {
    vehicle_t k_next = pop_random(freeVehicles);
    vehicle_t pi_next = pop_random(freeDestinations);
    perm[k_next - 1] = pi_next;
  }

  return perm;
}

bool fqrp::generators::IntervalGenerator::finished() { return false; }
