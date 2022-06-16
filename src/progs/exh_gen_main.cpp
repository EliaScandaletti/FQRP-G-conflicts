#include <core/algorithms.h>

#include <fqrp/aggregators/distribution_aggregator.h>
#include <fqrp/counters/conflictCounter.h>
#include <fqrp/generators/exhaustiveGenerator.h>
#include <fqrp/types.h>

using fqrp::Instance;
using fqrp::vehicle_t;
using fqrp::aggregators::dist_count;
using fqrp::aggregators::DistAggregator;
using fqrp::counters::conflictCounter;
using fqrp::generators::ExhaustiveGenerator;
using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char const *argv[]) {

  if (argc != 3) {
    cerr << "Error in usage." << endl;
    cerr << "Usage " << argv[0] << " min_size max_size" << endl;
    return 1;
  }

  // cout << "# Executing " << argv[0] << " " << argv[1] << " " << argv[2] <<
  // endl;
  vehicle_t min_size;
  vehicle_t max_size;
  try {
    min_size = std::stoi(argv[1]);
    max_size = std::stoi(argv[2]);
  } catch (const std::exception &e) {
    cerr << "Invalid input: conversion error" << endl;
  }

  for (vehicle_t size = min_size; size <= max_size; size++) {
    ExhaustiveGenerator g(size);
    conflictCounter c;
    DistAggregator agg;
    dist_count res = core::getExactCount(g, c, agg);

    cout << size << " " << res << endl;
  }

  return 0;
}
