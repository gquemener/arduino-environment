#ifndef STATE_STORE_H
#define STATE_STORE_H

#define CLOCK_HAS_TICKED 'A'
#define ATMOS_PRESSURE_WAS_MEASURED 'B'
#define TEMPERATURE_WAS_MEASURED 'C'

#include "State.h"
#include "Subscriber.h"
#include "Logger.h"

class StateStore
{
  private:
    State *state;
    Logger *logger;
    Subscriber* subscribers[2];
    int subscribersIndex = 0;

  public:
    StateStore(Logger *logger);

    void dispatch(char type, String data);
    void subscribe(Subscriber *subscriber);
};

#endif
