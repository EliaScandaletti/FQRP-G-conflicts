#include <fqrp/aggregators/averageAggregator.h>

fqrp::aggregators::avg_c_graph_info_t::avg_c_graph_info_t(
    long double max_length, long double tree_num, long double arcs_num,
    long double chain_num, long double vehicles_num)
    : max_length(max_length), tree_num(tree_num), arcs_num(arcs_num),
      chain_num(chain_num), vehicles_num(vehicles_num) {}

fqrp::aggregators::avg_forest_info_t::avg_forest_info_t(
    long double tree_num, long double max_tree_size, long double nodes_num,
    long double edges_num)
    : tree_num(tree_num), max_tree_size(max_tree_size), nodes_num(nodes_num),
      edges_num(edges_num) {}

fqrp::aggregators::averageCount::averageCount(
    long double arcType, long double AType, long double BType,
    const avg_c_graph_info_t &avg_c_graph_info,
    const c_graph_info_t &longest_c_graph_info,
    const c_graph_info_t &most_chains_c_graph_info,
    const avg_forest_info_t &avg_mixed_forest_info,
    const forest_info_t &biggest_tree_mixed_forest_info, count_t sample_size)
    : arcType(arcType), AType(AType), BType(BType),
      avg_c_graph_info(avg_c_graph_info),
      longest_c_graph_info(longest_c_graph_info),
      most_chains_c_graph_info(most_chains_c_graph_info),
      avg_mixed_forest_info(avg_mixed_forest_info),
      biggest_tree_mixed_forest_info(biggest_tree_mixed_forest_info),
      sample_size(sample_size) {}

fqrp::aggregators::AverageAggregator::AverageAggregator()
    : arcType_sum(0), AType_sum(0), BType_sum(0), c_graph_info_sum(),
      longest_c_graph_info(), most_chains_c_graph_info(),
      mixed_forest_info_sum(), biggest_tree_mixed_forest_info(), size(0) {}

void fqrp::aggregators::AverageAggregator::aggregate(
    const conflictCount &value) {
  arcType_sum += value.arcType;
  AType_sum += value.AType;
  BType_sum += value.BType;

  c_graph_info_sum.max_length += value.c_graph_info.max_length;
  c_graph_info_sum.tree_num += value.c_graph_info.tree_num;
  c_graph_info_sum.arcs_num += value.c_graph_info.arcs_num;
  c_graph_info_sum.chain_num += value.c_graph_info.chain_num;
  c_graph_info_sum.vehicles_num += value.c_graph_info.vehicles_num;

  if (value.c_graph_info.max_length > longest_c_graph_info.max_length) {
    longest_c_graph_info = value.c_graph_info;
  }

  if (value.c_graph_info.chain_num > most_chains_c_graph_info.chain_num) {
    most_chains_c_graph_info = value.c_graph_info;
  }

  if (value.mixed_forest_info.is_a_forest) {
    mixed_forest_info_sum.tree_num += value.mixed_forest_info.tree_num;
    mixed_forest_info_sum.max_tree_size +=
        value.mixed_forest_info.max_tree_size;
    mixed_forest_info_sum.nodes_num += value.mixed_forest_info.nodes_num;
    mixed_forest_info_sum.edges_num += value.mixed_forest_info.edges_num;

    if (value.mixed_forest_info.max_tree_size >
        biggest_tree_mixed_forest_info.max_tree_size) {
      biggest_tree_mixed_forest_info = value.mixed_forest_info;
    }
  }

  size += 1;
}

fqrp::aggregators::averageCount
fqrp::aggregators::AverageAggregator::result() const {
  return averageCount(
      static_cast<long double>(arcType_sum) / size,
      static_cast<long double>(AType_sum) / size,
      static_cast<long double>(BType_sum) / size,

      avg_c_graph_info_t(
          static_cast<long double>(c_graph_info_sum.max_length) / size,
          static_cast<long double>(c_graph_info_sum.tree_num) / size,
          static_cast<long double>(c_graph_info_sum.arcs_num) / size,
          static_cast<long double>(c_graph_info_sum.chain_num) / size,
          static_cast<long double>(c_graph_info_sum.vehicles_num) / size),
      longest_c_graph_info, most_chains_c_graph_info,

      avg_forest_info_t(
          static_cast<long double>(mixed_forest_info_sum.tree_num) / size,
          static_cast<long double>(mixed_forest_info_sum.max_tree_size) / size,
          static_cast<long double>(mixed_forest_info_sum.nodes_num) / size,
          static_cast<long double>(mixed_forest_info_sum.edges_num) / size),
      biggest_tree_mixed_forest_info,

      size);
}

fqrp::aggregators::averageCount
fqrp::aggregators::AverageAggregator::merge(const AverageAggregator &other) {
  arcType_sum += other.arcType_sum;
  AType_sum += other.AType_sum;
  BType_sum += other.BType_sum;

  c_graph_info_sum.max_length += other.c_graph_info_sum.max_length;
  c_graph_info_sum.tree_num += other.c_graph_info_sum.tree_num;
  c_graph_info_sum.arcs_num += other.c_graph_info_sum.arcs_num;
  c_graph_info_sum.chain_num += other.c_graph_info_sum.chain_num;
  c_graph_info_sum.vehicles_num += other.c_graph_info_sum.vehicles_num;

  if (other.longest_c_graph_info.max_length > longest_c_graph_info.max_length) {
    longest_c_graph_info = other.longest_c_graph_info;
  }

  if (other.most_chains_c_graph_info.chain_num >
      most_chains_c_graph_info.chain_num) {
    most_chains_c_graph_info = other.most_chains_c_graph_info;
  }

  if (other.mixed_forest_info_sum.is_a_forest) {
    mixed_forest_info_sum.tree_num += other.mixed_forest_info_sum.tree_num;
    mixed_forest_info_sum.max_tree_size +=
        other.mixed_forest_info_sum.max_tree_size;
    mixed_forest_info_sum.nodes_num += other.mixed_forest_info_sum.nodes_num;
    mixed_forest_info_sum.edges_num += other.mixed_forest_info_sum.edges_num;

    if (other.biggest_tree_mixed_forest_info.max_tree_size >
        biggest_tree_mixed_forest_info.max_tree_size) {
      biggest_tree_mixed_forest_info = other.biggest_tree_mixed_forest_info;
    }
  }
  size += other.size;
  return result();
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::avg_c_graph_info_t &info) {
  return os << info.max_length << " " << info.tree_num << " " << info.arcs_num
            << " " << info.vehicles_num;
}

std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::avg_c_graph_info_t &info) {
  return is >> info.max_length >> info.tree_num >> info.arcs_num >>
         info.vehicles_num;
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::avg_forest_info_t &info) {
  return os << " " << info.tree_num << " " << info.max_tree_size << " "
            << info.nodes_num << " " << info.edges_num;
}

std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::avg_forest_info_t &info) {
  return is >> info.tree_num >> info.max_tree_size >> info.nodes_num >>
         info.edges_num;
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::averageCount &count) {
  os << count.arcType << " " << count.AType << " " << count.BType << " "
     << count.avg_c_graph_info << " " << count.longest_c_graph_info << " "
     << count.most_chains_c_graph_info << " " << count.avg_mixed_forest_info
     << " " << count.biggest_tree_mixed_forest_info << " " << count.sample_size;
  return os;
}

std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::averageCount &count) {
  is >> count.arcType >> count.AType >> count.BType >> count.avg_c_graph_info >>
      count.longest_c_graph_info >> count.most_chains_c_graph_info >>
      count.avg_mixed_forest_info >> count.biggest_tree_mixed_forest_info >>
      count.sample_size;
  return is;
}