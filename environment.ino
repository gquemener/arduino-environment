#include "NullLogger.h"
#include "SerialLogger.h"
#include "Display.h"
#include "Barometer.h"

#include "StateStore.h"

NullLogger logger;
//SerialLogger logger(9600);

Display display(&logger);
StateStore stateStore(&display, &logger);

Barometer barometer(&logger, &stateStore);

void setup() {
  display.boot();
  barometer.boot();
}

void loop() {
  unsigned long timestamp = millis();
  barometer.tick(timestamp);
}
