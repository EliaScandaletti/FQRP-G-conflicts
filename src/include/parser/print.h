#ifndef PARSER_PRINT_TABLE_H
#define PARSER_PRINT_TABLE_H

#include <ostream>
#include <vector>

#include <fqrp/aggregators/distribution_aggregator.h>
#include <utils/distribution.h>

namespace parser {

void print_table(
    const std::string &os,
    const std::vector<std::tuple<fqrp::vehicle_t, fqrp::utils::distribution>>
        &counts);

void print_tables(
    const std::string &dir,
    const std::vector<
        std::tuple<fqrp::vehicle_t, fqrp::aggregators::dist_count>> &counts);

} // namespace parser

#endif