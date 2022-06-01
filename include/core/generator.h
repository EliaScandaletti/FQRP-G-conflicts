#ifndef CORE_GENERATOR_H
#define CORE_GENERATOR_H

namespace core {

template <typename _raw_t> class Generator {
public:
  typedef _raw_t raw_t;

  virtual ~Generator() = default;
  virtual _raw_t next() = 0;
  virtual bool finished() = 0;
};

} // namespace core

#endif