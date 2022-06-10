#include <fqrp/aggregators/averageAggregator.h>

fqrp::aggregators::AverageAggregator::AverageAggregator()
    : cumulative(), size(0) {}

void fqrp::aggregators::AverageAggregator::aggregate(
    const conflictCount &value) {
  cumulative.arcType += value.arcType;
  cumulative.AType += value.AType;
  cumulative.BType += value.BType;
  cumulative.CType += value.CType;
  cumulative.mixedType += value.mixedType;
  size += 1;
}

fqrp::aggregators::AverageAggregator::result_t
fqrp::aggregators::AverageAggregator::result() const {
  result_t res;
  res.arcType = static_cast<long double>(cumulative.arcType) / size;
  res.AType = static_cast<long double>(cumulative.AType) / size;
  res.BType = static_cast<long double>(cumulative.BType) / size;
  res.CType = static_cast<long double>(cumulative.CType) / size;
  res.mixedType = static_cast<long double>(cumulative.mixedType) / size;
  res.sample_size = size;
  return res;
}

fqrp::aggregators::AverageAggregator::result_t
fqrp::aggregators::AverageAggregator::merge(const AverageAggregator &other) {
  cumulative.arcType += other.cumulative.arcType;
  cumulative.AType += other.cumulative.AType;
  cumulative.BType += other.cumulative.BType;
  cumulative.CType += other.cumulative.CType;
  cumulative.mixedType += other.cumulative.mixedType;
  size += other.size;
  return result();
}

std::ostream &operator<<(std::ostream &os,
                         const fqrp::aggregators::averageCount &count) {
  os << count.arcType << " " << count.AType << " " << count.BType << " "
     << count.CType << " " << count.mixedType << " " << count.sample_size;
  return os;
}
std::istream &operator>>(std::istream &is,
                         fqrp::aggregators::averageCount &count) {
  is >> count.arcType >> count.AType >> count.BType >> count.CType >>
      count.mixedType >> count.sample_size;
  return is;
}