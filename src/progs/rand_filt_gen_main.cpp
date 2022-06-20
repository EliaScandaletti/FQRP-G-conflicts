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

  std::ofstream nonMixedTreeOut("benchmark/non_mixed_tree.ins.dat",
                                std::ios_base::app);
  if (!nonMixedTreeOut) {
    cerr << "Unable to create file benchmark/non_mixed_tree.ins.dat" << endl;
    cerr << "Check if the directory exists" << endl;
    throw "Unable to create file benchmark/non_mixed_tree.ins.dat";
  }
  logger_t nonMixedTreeLogger(
      [](const Instance &instance, const conflictCount &count) {
        (void)(instance); // remove unused parameter warning
        return !count.mixed_forest_info.is_a_forest;
      },
      nonMixedTreeOut);

  std::ofstream longCChainOut("benchmark/long_C_chain.ins.dat",
                              std::ios_base::app);
  if (!longCChainOut) {
    cerr << "Unable to create file benchmark/long_C_chain.ins.dat" << endl;
    cerr << "Check if the directory exists" << endl;
    throw "Unable to create file benchmark/long_C_chain.ins.dat";
  }
  logger_t longCChainLogger(
      [](const Instance &instance, const conflictCount &count) {
        vehicle_t n = instance.size();
        size_t theoretical_min = n >= 3 ? 1 + std::floor((n - 1) / 4) : 0;
        return count.c_graph_info.max_length >=
               std::floor(0.8 * theoretical_min);
      },
      longCChainOut);

  std::ofstream mixedChainOut("benchmark/mixed_chain.ins.dat",
                              std::ios_base::app);
  if (!mixedChainOut) {
    cerr << "Unable to create file benchmark/mixed_chain.ins.dat" << endl;
    cerr << "Check if the directory exists" << endl;
    throw "Unable to create file benchmark/mixed_chain.ins.dat";
  }
  logger_t mixedChainLogger(
      [](const Instance &instance, const conflictCount &count) {
        (void)(instance); // remove unused parameter warning
        vehicle_t k = 3;
        return count.mixed_forest_info.max_tree_size >= k;
      },
      mixedChainOut);

  for (vehicle_t size = min_size; size <= max_size; size++) {
    RandomGenerator g(size);
    Not<IsPartitioned> part_filter;
    FilteredGenerator<Instance> fg(g, part_filter);
    conflictCounter c({nonMixedTreeLogger, longCChainLogger, mixedChainLogger});
    DistAggregator agg;
    dist_count res = core::getEstimatedCount(limit, fg, c, agg);

    cout << size << " " << res << endl;
  }

  return 0;
}
