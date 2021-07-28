#ifndef STATE_STORE_H
#define STATE_STORE_H

#define CLOCK_HAS_TICKED 'A'
#define ATMOS_PRESSURE_WAS_MEASURED 'B'

#include "State.h"
#include "Subscriber.h"
#include "Logger.h"

class StateStore
{
  private:
    State *state;
    Subscriber *subscriber;
    Logger *logger;

  public:
    StateStore(Subscriber *subscriber, Logger *logger);

    void dispatch(char type, String data);
};

#endif
