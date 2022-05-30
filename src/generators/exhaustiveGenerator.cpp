#include <fqrp/generators/exhaustiveGenerator.h>

using namespace fqrp;

// assert(i == -1 || i < size)
vehicle_t *ExhaustiveGenerator::cacheNext() {
  while (!buf && i < size) {
    if (c[i] < i) {
      if ((i % 2) == 0) {
        std::swap(perm[0], perm[i]);
      } else {
        std::swap(perm[c[i]], perm[i]);
      }
      buf = new vehicle_t[size];
      std::copy(perm, perm + size, buf);
      c[i] += 1;
      i = 0;
    } else {
      c[i] = 0;
      i += 1;
    }
  }

  return buf;
}

ExhaustiveGenerator::ExhaustiveGenerator(vehicle_t size)
    : size(size), perm(new vehicle_t[size]), buf(new vehicle_t[size]),
      c(new vehicle_t[size]), i(0) {
  for (vehicle_t i = 0; i < size; i += 1) {
    perm[i] = buf[i] = i + 1;
    c[i] = 0;
  }
}

ExhaustiveGenerator::~ExhaustiveGenerator() {
  delete[] perm;
  delete[] buf;
  delete[] c;
}

// assert(!finished())
// assert(buf || cacheNext())
Instance ExhaustiveGenerator::next() {
  Instance ret = Instance(buf ? buf : cacheNext(), size);
  delete[] buf;
  buf = nullptr;
  return ret;
}

bool ExhaustiveGenerator::finished() { return !buf && !cacheNext(); }
