#include <core/algorithms.h>

#include <fqrp/aggregators/averageAggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/filters/not.h>
#include <fqrp/filters/partitioned.h>
#include <fqrp/filters/symmetric.h>
#include <fqrp/generators/exhaustiveGenerator.h>
#include <fqrp/generators/filteredGenerator.h>
#include <fqrp/types.h>

#include <chrono>
#include <cmath>
#include <iostream>

using namespace fqrp;
using namespace fqrp::generators;
using namespace fqrp::counters;
using namespace fqrp::filters;
using namespace fqrp::aggregators;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main() {
  vehicle_t min_size = 1;
  vehicle_t max_size = 25;

  for (vehicle_t size = min_size; size <= max_size; size++) {

    auto t1s = high_resolution_clock::now();
    ExhaustiveGenerator g(size);
    ExcludeSymmetric sym_filter;
    FilteredGenerator<Instance> sg(g, sym_filter);
    Not<IsPartitioned> part_filter;
    FilteredGenerator<Instance> fg(sg, part_filter);
    conflictCounter c;
    AverageAggregator agg;
    averageCount res = core::getExactCount(fg, c, agg);
    auto t1e = high_resolution_clock::now();

    cout << "n: " << size;
    cout << "\tT: " << duration_cast<milliseconds>(t1e - t1s).count() << " ";
    cout << res << endl;
  }

  return 0;
}
