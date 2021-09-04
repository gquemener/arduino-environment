#ifndef STATE_STORE_H
#define STATE_STORE_H

#define ATMOS_PRESSURE_WAS_MEASURED 0

#include "State.h"
#include "Subscriber.h"
#include "Logger.h"

class StateStore
{
  private:
    State *state;
    Subscriber *subscriber;
    Logger *logger;
    unsigned long lastTimestamps[2] = { };

  public:
    StateStore(Subscriber *subscriber, Logger *logger);

    void dispatch(char type, unsigned long timestamp, String data);
};

#endif
