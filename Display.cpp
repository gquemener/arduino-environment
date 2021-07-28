#include "Display.h"

Display::Display(Logger *logger)
{
  this->logger = logger;
}

void Display::boot()
{
  this->logger->info("Booting Display...");

  if (!tft.begin(RA8875_800x480)) {
    this->logger->info("RA8875 Not Found!");
    while (true);
  }

  this->tft.displayOn(true);
  this->tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  this->tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  this->tft.PWM1out(255);

  this->tft.graphicsMode();
  this->tft.fillScreen(RA8875_BLACK);

  this->tft.fillRect(0, 315, 800, 10, RA8875_WHITE);
}

void Display::handle(State *state)
{
  this->tft.textMode();
  this->tft.setTextColor(RA8875_WHITE, RA8875_BLACK);

  this->write(state->atmosPressure() + " hPa", 10, 10, 3);
  this->write(state->datetime(), 10, 330, 2);
}

void Display::write(String text, int x, int y, int size)
{
  char textChar[text.length() + 1];
  text.toCharArray(textChar, text.length() + 1);
  this->tft.textSetCursor(x, y);
  this->tft.textEnlarge(size);
  this->tft.textWrite(textChar);
}
