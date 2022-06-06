#include <core/algorithms.h>

#include <fqrp/aggregators/averageAggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/filters/not.h>
#include <fqrp/filters/partitioned.h>
#include <fqrp/generators/exhaustiveGenerator.h>
#include <fqrp/generators/filteredGenerator.h>
#include <fqrp/generators/intervalGenerator.h>
#include <fqrp/generators/randomGenerator.h>
#include <fqrp/types.h>

#include <chrono>
#include <iostream>

using namespace fqrp;
using namespace fqrp::generators;
using namespace fqrp::filters;
using namespace fqrp::counters;
using namespace fqrp::aggregators;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

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
  vehicle_t max_size = 20;
  count_t max_limit = 10000000;

  for (vehicle_t size = 1; size < max_size; size++) {
    count_t limit = std::min<double>(max_limit, std::pow(size, 6));

    auto t1s = high_resolution_clock::now();
    RandomGenerator g(size);
    Not<IsPartitioned> filter;
    FilteredGenerator<Instance> fg(g, filter);
    conflictCounter c;
    AverageAggregator agg;
    averageCount res = core::getEstimatedCount(limit, fg, c, agg);
    auto t1e = high_resolution_clock::now();

    cout << "Metodo casuale con filtro su istanza di " << size
         << " elementi:" << endl;
    cout << "Tempo: " << duration_cast<milliseconds>(t1e - t1s).count() << "ms"
         << endl;
    print(res);

    auto t2s = high_resolution_clock::now();
    IntervalGenerator ig(size);
    conflictCounter ic;
    AverageAggregator iagg;
    averageCount ires = core::getEstimatedCount(limit, ig, ic, iagg);
    auto t2e = high_resolution_clock::now();

    cout << "Metodo degli intervalli su istanza di " << size
         << " elementi:" << endl;
    cout << "Tempo: " << duration_cast<milliseconds>(t2e - t2s).count() << "ms"
         << endl;
    print(ires);
  }

  return 0;
}
