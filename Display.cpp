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
  this->tft.fillScreen(COLOR_BACKGROUND);
}

void Display::handle(State *state)
{
  this->tft.graphicsMode();
  this->tft.fillScreen(COLOR_BACKGROUND);
  this->logger->info(String(state->minPressure) + " " + String(state->maxPressure) + " " + String(state->pressures[0]));

  unsigned short minHistoValue = min(9900, state->minPressure);
  unsigned short maxHistoValue = max(10100, state->maxPressure);

  this->logger->info(String(minHistoValue) + " " + String(maxHistoValue));

  for (int i = 0; i < 800; i++) {
    unsigned short current = state->pressures[i];
    this->logger->info(String("pressures[" + String(i) + "]" + current));

    if (current == 0) {
        break;
    }

    int x = 800 - i;
    int y = map(current, minHistoValue, maxHistoValue, MIN_HISTO_Y, MAX_HISTO_Y);
    int height = map(current, minHistoValue, maxHistoValue, MIN_HISTO_HEIGHT, MAX_HISTO_HEIGHT);
    this->tft.drawFastVLine(x, y, height, COLOR_HISTOGRAM);
  }

  for (int i = 0; i < 23; i++) {
    double delta = state->deltas[i] / 10.0F;
    char deltaStr[7];
    uint16_t deltaColor = COLOR_DELTA_POSITIVE;
    sprintf(deltaStr, "%+.1f", delta);
    if (deltaStr[0] == '-') {
      deltaColor = COLOR_DELTA_NEGATIVE;
    }
    int deltaY;
    switch (i % 3) {
      case 0:
        deltaY = 70;
        break;

        case 1:
        deltaY = 120;
        break;

        case 2:
        deltaY = 170;
        break;
    }

    unsigned short int x = 769 - i * COLS_GAP;
    this->write(deltaStr, x - 50, deltaY, 1, deltaColor);
  }

  char currentStr[6];
  sprintf(currentStr, "%.1f", state->pressures[0] / 10.0F);
  this->write(currentStr, 10, 10, 4, COLOR_PRESSURE);
}

void Display::write(String text, int x, int y, int size, uint16_t color)
{
  char textChar[text.length() + 1];
  text.toCharArray(textChar, text.length() + 1);

  this->tft.textMode();
  this->tft.textSetCursor(x, y);
  this->tft.textEnlarge(size);
  this->tft.textTransparent(color);
  this->tft.textWrite(textChar);
}
