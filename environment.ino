#include "NullLogger.h"
#include "Display.h"
#include "RealTimeClock.h"
#include "Wifi.h"
#include "Barometer.h"
#include "secrets.h"

#include "StateStore.h"

NullLogger logger;

Display display(&logger);
StateStore stateStore(&display, &logger);

Wifi wifi(SECRET_SSID, SECRET_PASSWORD, &logger);
RealTimeClock rtc(&wifi, &logger, &stateStore);
Barometer barometer(&logger, &stateStore);

void setup() {
  display.boot();
  wifi.boot();
  rtc.boot();
  barometer.boot();
}

void loop() {
  unsigned long timestamp = millis();
  barometer.tick(timestamp);
  rtc.tick(timestamp);
}
