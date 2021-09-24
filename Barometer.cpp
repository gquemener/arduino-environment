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
  if (!this->bmp.performReading()) {
    this->logger->warn("Failed to perform reading :(");
  }
  double pressure = this->bmp.pressure;
  delay(2000);
}

void Barometer::tick(unsigned long timestamp)
{
  if (this->lastUpdateTimestamp == 0 || timestamp - this->lastUpdateTimestamp > 1000) {
    this->lastUpdateTimestamp = timestamp;
    int pressure = this->measure();

    this->stateStore->dispatch(
      ATMOS_PRESSURE_WAS_MEASURED,
      timestamp,
      String(pressure)
    );
  }
}

int Barometer::measure()
{
  if (!this->bmp.performReading()) {
    this->logger->warn("Failed to perform reading :(");

    return 0;
  }

  return (int) round(this->bmp.pressure / 10.0F);
}
