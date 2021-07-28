#ifndef REAL_TIME_CLOCK_H
#define REAL_TIME_CLOCK_H

#include "Wifi.h"
#include "Logger.h"
#include "StateStore.h"
#include <RTCZero.h>
#include <Arduino.h>

class RealTimeClock
{
  private:
    RTCZero rtc;
    Wifi *wifi;
    Logger *logger;
    StateStore *stateStore;
    unsigned long lastUpdateTimestamp = 0;

  public:
    RealTimeClock(Wifi *wifi, Logger *logger, StateStore *stateStore);

    void boot();
    void tick(unsigned long timestamp);
};

#endif
