#ifndef DISPLAY_H
#define DISPLAY_H

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9
#define COLOR_HISTOGRAM_LOW 0xF201 // red
#define COLOR_HISTOGRAM_AVERAGE 0x71FB // purple
#define COLOR_HISTOGRAM_HIGH 0x02B9 // blue
#define COLOR_PRESSURE 0xFC00 // orange
#define COLOR_PRESSURE_LIMIT 0x36C0 // green
#define COLOR_DELTA_POSITIVE 0xFFFF // white
#define COLOR_DELTA_NEGATIVE 0xE000 // red
#define COLOR_BACKGROUND 0x0000 // black

#define MIN_HISTO_Y 480
#define MAX_HISTO_Y 210
#define MIN_HISTO_HEIGHT 1
#define MAX_HISTO_HEIGHT 270
#define COLS_GAP 33
#define MIN_SCALE_INTERVAL 100

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
