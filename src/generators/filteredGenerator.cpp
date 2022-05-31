#include <fqrp/generators/filteredGenerator.h>

using namespace fqrp;
using namespace fqrp::generators;

FilteredGenerator::FilteredGenerator(Generator *generator, Filter *filter)
    : generator(generator), filter(filter), buf() {}

void FilteredGenerator::cacheNext() {
  while (buf.getSize() == 0 && !generator->finished()) {
    Instance temp = generator->next();
    if(filter->operator()(temp)) {
      buf = temp;
    }
  }
}

Instance FilteredGenerator::next() {
  cacheNext();
  Instance ret = buf;
  buf = Instance();
  return ret;
}

bool FilteredGenerator::finished() {
  cacheNext();
  return buf.getSize() == 0;
}
