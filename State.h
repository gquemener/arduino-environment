#ifndef STATE_H
#define STATE_H

#define MIN_PRESSURE 9200
#define MAX_PRESSURE 10850

#include <Arduino.h>

class State
{
  public:
    int pressures[24] = { };
    int minPressure;
    int maxPressure;

    void addPressure(int pressure);
};

#endif
