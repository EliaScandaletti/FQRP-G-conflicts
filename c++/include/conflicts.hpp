#ifndef CONFLICTS_HPP
#define CONFLICTS_HPP

#include "instance.hpp"

bool checkArcConflict(const Instance &instance, const int &vehicleA,
                    const int &vehicleB);

bool checkAConflict(const Instance &instance, const int &vehicleA,
                    const int &vehicleB);

bool checkBConflict(const Instance &instance, const int &vehicleA,
                    const int &vehicleB);

int getCConflict(const Instance &instance, const int &vehicle);

bool checkSameConflictChain(const Instance &instance, const int &vehicleA,
                    const int &vehicleB);

#endif