#ifndef DISPLAY_H
#define DISPLAY_H

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
#define RA8875_GREY 0x7BEF

#define MIN_HISTO_Y 459
#define MAX_HISTO_Y 220
#define MIN_HISTO_HEIGHT 1
#define MAX_HISTO_HEIGHT 240
#define HISTO_WIDTH 21
#define HISTO_GAP 12
#define MIN_HISTO_VALUE 1000
#define MAX_HISTO_VALUE 1010

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
    String spaces(int count);
    void write(String text, int x, int y, int size, uint16_t color);

  public:
    Display(Logger *logger);

    void handle(State *state);
    void boot();
    void writeLine(String line);
};

#endif
