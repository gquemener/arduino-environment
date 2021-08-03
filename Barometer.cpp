#include "Barometer.h"

Barometer::Barometer(Logger *logger, StateStore *stateStore)
{
    this->logger = logger;
    this->stateStore = stateStore;
}

void Barometer::boot()
{
  if (!this->bmp.begin()) {
    this->logger->info("Could not find a valid BMP3 sensor, check wiring!");
    while (true);
  }
  this->bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  this->bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  this->bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);

  // First reading is always wrong
  this->measure();
  this->measure();
}

void Barometer::tick(unsigned long timestamp)
{
  if (this->lastUpdateTimestamp == 0 || timestamp - this->lastUpdateTimestamp > 3600000) {
    this->lastUpdateTimestamp = timestamp;
    this->measure();
  }
}

void Barometer::measure()
{
  if (!this->bmp.performReading()) {
    this->logger->info("Failed to perform reading :(");
  }

  this->stateStore->dispatch(ATMOS_PRESSURE_WAS_MEASURED, String(this->bmp.pressure / 100.0));
  this->stateStore->dispatch(TEMPERATURE_WAS_MEASURED, String(this->bmp.temperature));
}
