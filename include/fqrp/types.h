#ifndef FQRP_TYPES_H
#define FQRP_TYPES_H

#include <cstdint>

namespace fqrp {

typedef std::uint32_t vehicle_t;
typedef std::uint64_t count_t;

constexpr vehicle_t null_vehicle = 0;

struct conflictCount {
  count_t arcType;
  count_t AType;
  count_t BType;
  count_t CType;
  count_t mixedType;
  conflictCount();
};

} // namespace fqrp

#endif