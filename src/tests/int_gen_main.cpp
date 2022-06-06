#include <core/algorithms.h>

#include <fqrp/aggregators/averageAggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/generators/intervalGenerator.h>
#include <fqrp/types.h>

#include <chrono>
#include <iostream>

using namespace fqrp;
using namespace fqrp::generators;
using namespace fqrp::counters;
using namespace fqrp::aggregators;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

void print(const averageCount &c) {
  cout << "\tarcType: " << c.arcType;
  cout << "\tAType: " << c.AType;
  cout << "\tBType: " << c.BType;
  cout << "\tCType: " << c.CType;
  cout << "\tmixedType: " << c.mixedType;
  cout << "\tsize: " << c.sample_size;
  cout << endl;
}

int main() {
  vehicle_t max_size = 20;
  count_t max_limit = 10000000;

  for (vehicle_t size = 1; size < max_size; size++) {
    count_t limit = std::min<double>(max_limit, std::pow(size, 6));

    auto t1s = high_resolution_clock::now();
    IntervalGenerator g(size);
    conflictCounter c;
    AverageAggregator agg;
    averageCount res = core::getEstimatedCount(limit, g, c, agg);
    auto t1e = high_resolution_clock::now();

    cout << "n: " << size;
    cout << "\tT: " << duration_cast<milliseconds>(t1e - t1s).count();
    print(res);
  }

  return 0;
}
