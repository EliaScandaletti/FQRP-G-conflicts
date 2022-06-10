#ifndef FQRP_TYPES_H
#define FQRP_TYPES_H

#include <cstdint>
#include <iostream>
#include <vector>

namespace fqrp {
class Instance;
} // namespace fqrp

std::ostream &operator<<(std::ostream &, const fqrp::Instance &);
std::istream &operator>>(std::istream &, fqrp::Instance &);

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

class Instance {
  friend std::ostream & ::operator<<(std::ostream &, const fqrp::Instance &);
  friend std::istream & ::operator>>(std::istream &, fqrp::Instance &);

  std::vector<vehicle_t> permutation;

public:
  Instance(std::vector<vehicle_t> perm = std::vector<vehicle_t>());
  virtual ~Instance() = default;

  vehicle_t size() const;
  // index of vehicles start at 1
  vehicle_t sigma(vehicle_t vehicle) const;

  explicit operator bool() const;
};

} // namespace fqrp

std::ostream &operator<<(std::ostream &, const fqrp::conflictCount &);
std::istream &operator>>(std::istream &, fqrp::conflictCount &);

#endif