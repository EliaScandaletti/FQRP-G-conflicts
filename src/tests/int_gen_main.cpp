#include <core/algorithms.h>

#include <fqrp/aggregators/averageAggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/generators/intervalGenerator.h>
#include <fqrp/types.h>

#include <chrono>
#include <iostream>
#include <sstream>

using namespace fqrp;
using namespace fqrp::generators;
using namespace fqrp::counters;
using namespace fqrp::aggregators;
using std::cerr;
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main(int argc, char const *argv[]) {

  if (argc != 4) {
    cerr << "Error in usage." << endl;
    cerr << "Usage " << argv[0] << " min_size max_size max_limit" << endl;
    return 1;
  }

  cout << "# Executing " << argv[0] << " " << argv[1] << " " << argv[2] << " "
       << argv[3] << endl;
  std::istringstream ss1(argv[1]);
  vehicle_t min_size;
  if (!(ss1 >> min_size)) {
    cerr << "Invalid number: " << argv[1] << '\n';
    return 1;
  } else if (!ss1.eof()) {
    cerr << "Trailing characters after number: " << argv[1] << '\n';
    return 1;
  }
  std::istringstream ss2(argv[2]);
  vehicle_t max_size;
  if (!(ss2 >> max_size)) {
    cerr << "Invalid number: " << argv[2] << '\n';
    return 1;
  } else if (!ss2.eof()) {
    cerr << "Trailing characters after number: " << argv[2] << '\n';
    return 1;
  }
  std::istringstream ss3(argv[3]);
  vehicle_t max_limit;
  if (!(ss3 >> max_limit)) {
    cerr << "Invalid number: " << argv[3] << '\n';
    return 1;
  } else if (!ss3.eof()) {
    cerr << "Trailing characters after number: " << argv[3] << '\n';
    return 1;
  }

  for (vehicle_t size = min_size; size <= max_size; size++) {
    count_t limit = std::min<double>(max_limit, std::pow(size, 6));

    auto t1s = high_resolution_clock::now();
    IntervalGenerator g(size);
    conflictCounter c;
    AverageAggregator agg;
    averageCount res = core::getEstimatedCount(limit, g, c, agg);
    auto t1e = high_resolution_clock::now();

    cout << "n: " << size;
    cout << "\tT: " << duration_cast<milliseconds>(t1e - t1s).count();
    cout << res << endl;
  }

  return 0;
}
