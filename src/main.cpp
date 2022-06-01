#include <core/algorithms.h>
#include <fqrp/aggregators/averageAggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/filters/not.h>
#include <fqrp/filters/partitioned.h>
#include <fqrp/generators/exhaustiveGenerator.h>
#include <fqrp/generators/filteredGenerator.h>
#include <fqrp/generators/randomGenerator.h>
#include <fqrp/types.h>

#include <iostream>

using namespace fqrp;
using namespace fqrp::generators;
using namespace fqrp::filters;
using namespace fqrp::counters;
using namespace fqrp::aggregators;
using std::cout;
using std::endl;

void print(const Instance &ins) {
  for (size_t i = 1; i <= ins.size(); i++) {
    cout << ins.sigma(i) << "  ";
  }
  cout << endl;
}

void print(const conflictCount &c) {
  cout << " arcType: " << c.arcType;
  cout << " AType: " << c.AType;
  cout << " BType: " << c.BType;
  cout << " CType: " << c.CType;
  cout << " mixedType: " << c.mixedType;
  cout << endl;
}

void print(const fqrp::aggregators::averageCount &c) {
  cout << " arcType: " << c.arcType;
  cout << " AType: " << c.AType;
  cout << " BType: " << c.BType;
  cout << " CType: " << c.CType;
  cout << " mixedType: " << c.mixedType;
  cout << " size: " << c.sample_size;
  cout << endl;
}

int main() {

  ExhaustiveGenerator g(10);
  Not<IsPartitioned> filter;
  FilteredGenerator<Instance> fg(g, filter);
  conflictCounter c;
  AverageAggregator agg;

  averageCount res = core::getExactCount(fg, c, agg);

  print(res);

  return 0;
}
