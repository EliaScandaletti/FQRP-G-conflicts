#include <cmath>
#include <fstream>

#include <core/algorithms.h>
#include <fqrp/aggregators/distribution_aggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/filters/not.h>
#include <fqrp/filters/partitioned.h>
#include <fqrp/generators/filteredGenerator.h>
#include <fqrp/generators/randomGenerator.h>
#include <fqrp/types.h>

using fqrp::conflictCount;
using fqrp::Instance;
using fqrp::vehicle_t;
using fqrp::aggregators::dist_count;
using fqrp::aggregators::DistAggregator;
using fqrp::counters::conflictCounter;
using fqrp::counters::logger_t;
using fqrp::filters::IsPartitioned;
using fqrp::filters::Not;
using fqrp::generators::FilteredGenerator;
using fqrp::generators::RandomGenerator;
using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {

  if (argc != 4) {
    cerr << "Error in usage." << endl;
    cerr << "Usage " << argv[0] << " min_size max_size limit" << endl;
    return 1;
  }

  // cout << "# Executing " << argv[0] << " " << argv[1] << " " << argv[2]
  //      << " " << argv[3] << "" << endl;
  vehicle_t min_size;
  vehicle_t max_size;
  vehicle_t limit;
  try {
    min_size = std::stoi(argv[1]);
    max_size = std::stoi(argv[2]);
    limit = std::stoi(argv[3]);
  } catch (const std::exception &e) {
    cerr << "Invalid input: conversion error" << endl;
  }

  for (vehicle_t size = min_size; size <= max_size; size++) {
    RandomGenerator g(size);
    Not<IsPartitioned> part_filter;
    FilteredGenerator<Instance> fg(g, part_filter);
    conflictCounter c;
    DistAggregator agg;
    dist_count res = core::getEstimatedCount(limit, fg, c, agg);

    cout << size << " " << res << endl;
  }

  return 0;
}
