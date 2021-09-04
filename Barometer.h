#ifndef BAROMETER_H
#define BAROMETER_H

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include "Logger.h"
#include "StateStore.h"

class Barometer
{
  private:
    Adafruit_BMP3XX bmp;
    Logger *logger;
    StateStore *stateStore;
    unsigned long lastUpdateTimestamp = 0;
    int measure();

  public:
    Barometer(Logger *logger, StateStore *stateStore);

    void boot();
    void tick(unsigned long timestamp);
};

#endif
