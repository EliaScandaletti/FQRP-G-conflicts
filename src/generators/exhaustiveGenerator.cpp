#include "exhaustiveGenerator.h"

// assert(i == -1 || i < size)
std::vector<fqrp::vehicle_t>
fqrp::generators::ExhaustiveGenerator::cacheNext() {
  while (buf.empty() && i < perm.size()) {
    if (c[i] < i) {
      if ((i % 2) == 0) {
        std::swap(perm[0], perm[i]);
      } else {
        std::swap(perm[c[i]], perm[i]);
      }
      buf = perm;
      c[i] += 1;
      i = 0;
    } else {
      c[i] = 0;
      i += 1;
    }
  }

  return buf;
}

fqrp::generators::ExhaustiveGenerator::ExhaustiveGenerator(vehicle_t size)
    : perm(size), buf(size), c(size), i(0) {
  for (vehicle_t i = 0; i < size; i += 1) {
    perm[i] = buf[i] = i + 1;
  }
}

// assert(!finished())
// assert(buf || cacheNext())
fqrp::Instance fqrp::generators::ExhaustiveGenerator::next() {
  cacheNext();
  Instance ret = Instance(buf);
  buf.clear();
  return ret;
}

bool fqrp::generators::ExhaustiveGenerator::finished() {
  cacheNext();
  return buf.empty();
}
