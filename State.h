#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

class State
{
  public:
    String datetime;
    String atmosPressure;
    String temperature;
    State();
};

#endif
