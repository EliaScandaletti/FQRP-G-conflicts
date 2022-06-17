#ifndef PARSER_PARSE_H
#define PARSER_PARSE_H

#include <istream>
#include <tuple>
#include <vector>

#include <fqrp/aggregators/distribution_aggregator.h>

std::istream &operator>>(std::istream &is, fqrp::utils::distribution &dist);

std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::c_graph_dist_t &dist);

std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::forest_dist_t &dist);

std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::dist_count &count);

namespace parser {

std::vector<std::tuple<fqrp::vehicle_t, fqrp::aggregators::dist_count>>
parse(std::istream &is);

} // namespace parser

#endif