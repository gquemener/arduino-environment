#ifndef DISPLAY_H
#define DISPLAY_H

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
#define RA8875_GREY 0x7BEF

#include "Subscriber.h"
#include "Logger.h"

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"

class Display: public Subscriber
{
  private:
    Logger *logger;
    Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
    String lines[24];
    void write(String text, int x, int y, int size);

  public:
    Display(Logger *logger);

    void handle(char type, State *state);
    void boot();
};

#endif
