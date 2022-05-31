#include <fqrp/aggregators/averageAggregator.h>

using namespace fqrp;
using namespace fqrp::aggregators;

AverageAggregator::AverageAggregator() : cumulative(), size(0) {}

void AverageAggregator::aggregate(const value_t &value) {
  cumulative.arcType += value.arcType;
  cumulative.AType += value.AType;
  cumulative.BType += value.BType;
  cumulative.CType += value.CType;
  cumulative.mixedType += value.mixedType;
  size += 1;
}

AverageAggregator::result_t AverageAggregator::result() const {
  result_t res;
  res.arcType = static_cast<long double>(cumulative.arcType) / size;
  res.AType = static_cast<long double>(cumulative.AType) / size;
  res.BType = static_cast<long double>(cumulative.BType) / size;
  res.CType = static_cast<long double>(cumulative.CType) / size;
  res.mixedType = static_cast<long double>(cumulative.mixedType) / size;
  res.sample_size = size;
  return res;
}

AverageAggregator::result_t
AverageAggregator::merge(const AverageAggregator &other) {
  cumulative.arcType += other.cumulative.arcType;
  cumulative.AType += other.cumulative.AType;
  cumulative.BType += other.cumulative.BType;
  cumulative.CType += other.cumulative.CType;
  cumulative.mixedType += other.cumulative.mixedType;
  size += other.size;
  return result();
}