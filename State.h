#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

class State
{
  private:
    String _datetime;
    String _atmosPressure;

  public:
    State(String datetime, String atmosPressure);
    String datetime();
    String atmosPressure();
};

#endif
