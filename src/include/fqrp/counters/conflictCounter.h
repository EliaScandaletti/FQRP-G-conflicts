#ifndef FQRP_CONFLICT_COUNTER_H
#define FQRP_CONFLICT_COUNTER_H

#include <ostream>

#include <core/counter.h>
#include <fqrp/conflicts.h>
#include <fqrp/types.h>

namespace fqrp {

namespace counters {

class logger_t {
  typedef bool (*condition_t)(const Instance &, const conflictCount &);
  condition_t test;
  std::ostream &os;

public:
  logger_t(condition_t test, std::ostream &os = std::cout);
  void operator()(const Instance &instance, const conflictCount &count);
};

class conflictCounter : public core::Counter<Instance, conflictCount> {
public:
private:
  std::vector<logger_t> loggers;

public:
  conflictCounter(const std::vector<logger_t> &loggers = {});
  conflictCount count(const Instance &instance) override;
};

} // namespace counters

} // namespace fqrp

#endif