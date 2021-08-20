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
}

void Display::handle(State *state)
{
  this->logger->info(String(state->minPressure) + " " + String(state->maxPressure) + " " + String(state->pressures[0]));
  
  double minHistoValue = min(9900, state->minPressure) / 10.0F;
  double maxHistoValue = max(10100, state->maxPressure) / 10.0F;

  this->logger->info(String(minHistoValue) + " " + String(maxHistoValue));

  for (int i = 0; i < 24; i++) {
    double current = state->pressures[i] / 10.0F;
    this->logger->info(String("pressures[" + String(i) + "]" + current));

    if (current == 0.0) {
      continue;
    }

    int x = 769 - i * (HISTO_WIDTH + HISTO_GAP);
    int y = MIN_HISTO_Y - ((minHistoValue - pressure)/(maxHistoValue - minHistoValue) * (MAX_HISTO_Y - MIN_HISTO_Y));
    int height = MAX_HISTO_HEIGHT - ((maxHistoValue - pressure)/(maxHistoValue - minHistoValue) * (MAX_HISTO_HEIGHT - MIN_HISTO_HEIGHT));

    this->tft.graphicsMode();
    this->tft.fillRect(x, MAX_HISTO_Y, HISTO_WIDTH, MAX_HISTO_HEIGHT, RA8875_BLACK);
    this->tft.fillRect(x, y, HISTO_WIDTH, height, RA8875_GREEN);

    if (i == 23) {
      continue;
    }
    double previous = state->pressures[i + 1] / 10.0F;
    if (previous == 0.0) {
      continue;
    }
    double delta = current - previous;
    char deltaStr[7];
    uint16_t deltaColor = RA8875_WHITE;
    sprintf(deltaStr, "%+.1f", delta);
    if (deltaStr[0] == '-') {
      deltaColor = RA8875_RED;
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

    this->write(deltaStr, x - 50, deltaY, 1, deltaColor);
  }
  
  char currentStr[6];
  sprintf(currentStr, "%.1f", state->pressures[0] / 10.0F);
  this->write(currentStr, 10, 10, 4, RA8875_GREEN);
}

void Display::write(String text, int x, int y, int size, uint16_t color)
{
  char textChar[text.length() + 1];
  text.toCharArray(textChar, text.length() + 1);
  
  this->tft.textMode();
  this->tft.textSetCursor(x, y);
  this->tft.textEnlarge(size);
  this->tft.textColor(color, RA8875_BLACK);
  this->tft.textWrite(textChar);
}
