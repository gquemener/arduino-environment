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

  unsigned short int maxScale = state->maxPressure;
  unsigned short int minScale = state->minPressure;
  unsigned short int interval = maxScale - minScale;
  signed short int deltaInterval = MIN_SCALE_INTERVAL - interval;
  if (deltaInterval > 0) {
    if (deltaInterval % 2 == 1) {
      deltaInterval--;
    }
    maxScale += (deltaInterval) / 2;
    minScale -= (deltaInterval) / 2;
  }

  for (int i = 0; i < 800; i++) {
    unsigned short current = state->pressures[i];
    this->logger->info(String("pressures[" + String(i) + "]" + current));

    if (current == 0) {
        break;
    }

    int x = 800 - i;
    int y = map(current, minScale, maxScale, MIN_HISTO_Y, MAX_HISTO_Y);
    int height = map(current, minScale, maxScale, MIN_HISTO_HEIGHT, MAX_HISTO_HEIGHT);

    unsigned short int color = COLOR_HISTOGRAM_LOW;
    if (current > 10100) {
        color = COLOR_HISTOGRAM_AVERAGE;
    }
    if (current > 10160) {
        color = COLOR_HISTOGRAM_HIGH;
    }

    this->tft.drawFastVLine(x, y, height, color);
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

    unsigned short int x = 775 - i * COLS_GAP;
    this->write(deltaStr, x - 50, deltaY, 1, deltaColor);
  }

  char pressureStr[23];

  sprintf(
    pressureStr,
    "%.1f [%.1f, %.1f]",
    state->pressures[0] / 10.0F,
    state->minPressure / 10.0F,
    state->maxPressure / 10.0F
  );
  this->write(pressureStr, 10, 10, 4, COLOR_PRESSURE);

  sprintf(pressureStr, "%.1f", minScale / 10.0F);
  this->write(pressureStr, 10, 450, 1, COLOR_PRESSURE_LIMIT);

  sprintf(pressureStr, "%.1f", maxScale / 10.0F);
  this->write(pressureStr, 10, 210, 1, COLOR_PRESSURE_LIMIT);
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
