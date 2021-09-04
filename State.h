#ifndef STATE_H
#define STATE_H

#define MIN_PRESSURE 9200
#define MAX_PRESSURE 10850

#include <Arduino.h>

class State
{
  public:
    unsigned short int pressures[800] = { };
    unsigned short int lastPressureSinceDelta = 0;
    short int deltas[23] = { };
    unsigned short int minPressure;
    unsigned short int maxPressure;

    void addPressure(unsigned short int pressure);
    void addDelta(unsigned short int pressure);
};

#endif
