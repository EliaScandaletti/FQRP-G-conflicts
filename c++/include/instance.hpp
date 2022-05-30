#ifndef INSTANCE_HPP
#define INSTANCE_HPP

class Instance {
  const int size;

protected:
  Instance(const int &size);

public:
  static const int nullVehicle = -1;

  const int &getSize() const;
  virtual int sigma(const int &vehicle) const;
};

#endif