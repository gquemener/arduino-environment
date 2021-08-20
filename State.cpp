#include "State.h"

void State::addPressure(int pressure)
{
  if (pressure < MIN_PRESSURE || pressure > MAX_PRESSURE) {
    return;
  }
  
  for (int i = 23; i >= 0; i--) {
    this->pressures[i] = this->pressures[i - 1];
  }
  this->pressures[0] = pressure;

  this->minPressure = this->pressures[0];
  this->maxPressure = this->pressures[0];
  for (int i = 1; i < 24; i++) {
    if (this->pressures[i] == 0) {
      continue;
    }
    
    this->minPressure = min(this->minPressure, this->pressures[i]);
    this->maxPressure = max(this->maxPressure, this->pressures[i]);
  }
}
