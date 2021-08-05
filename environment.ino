#include "NullLogger.h"
#include "Display.h"
#include "RealTimeClock.h"
#include "Wifi.h"
#include "Barometer.h"
#include "History.h"
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include "secrets.h"

#include "StateStore.h"

NullLogger logger;

Display display(&logger);
StateStore stateStore(&logger);

Wifi wifi(SECRET_SSID, SECRET_PASSWORD, &logger);
RealTimeClock rtc(&wifi, &logger, &stateStore);
Barometer barometer(&logger, &stateStore);

WiFiSSLClient wifinina;
History history(new HttpClient(wifinina, "url", 443), String("token"), &logger);

void setup() {
  display.boot();
  wifi.boot();
  rtc.boot();
  barometer.boot();

  stateStore.subscribe(&display);
  //stateStore.subscribe(&history);
}

void loop() {
  unsigned long timestamp = millis();
  barometer.tick(timestamp);
  rtc.tick(timestamp);
}
