#include "RealTimeClock.h"

RealTimeClock::RealTimeClock(Wifi *wifi, Logger *logger, StateStore *stateStore)
{
  this->wifi = wifi;
  this->logger = logger;
  this->stateStore = stateStore;
}

void RealTimeClock::boot()
{
  this->logger->info("Booting RTC...");

  while (!this->wifi->isConnected()) {
    this->wifi->connect();
  }

  this->rtc.begin();
  this->rtc.setEpoch(this->wifi->getCurrentTimestamp());
}

void RealTimeClock::tick(unsigned long timestamp)
{
  if (timestamp - lastUpdateTimestamp > 1000) {
    lastUpdateTimestamp = timestamp;
    char date[25];

    sprintf(
      date,
      "%4d-%02d-%02dT%02d:%02d:%02d+00:00",
      this->rtc.getYear() + 2000,
      this->rtc.getMonth(),
      this->rtc.getDay(),
      this->rtc.getHours(),
      this->rtc.getMinutes(),
      this->rtc.getSeconds()
    );

    stateStore->dispatch(CLOCK_HAS_TICKED, String(date));
  }
}