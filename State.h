#ifndef STATE_H
#define STATE_H

#define MIN_PRESSURE 920.0
#define MAX_PRESSURE 1085.0

#include <Arduino.h>

class State
{
  public:
    double pressures[24] = { };
    double minPressure;
    double maxPressure;

    void addPressure(double pressure);
};

#endif
