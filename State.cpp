#include "State.h"

void State::addPressure(unsigned short int pressure)
{
    if (pressure < MIN_PRESSURE || pressure > MAX_PRESSURE) {
        return;
    }

    for (int i = 799; i > 0; i--) {
        this->pressures[i] = this->pressures[i - 1];
    }
    this->pressures[0] = pressure;

    if (this->minPressure == 0) {
        this->minPressure = pressure;
    }
    if (this->maxPressure) {
        this->maxPressure = pressure;
    }
    this->minPressure = min(this->minPressure, pressure);
    this->maxPressure = min(this->maxPressure, pressure);
}

void State::addDelta(unsigned short int pressure)
{
    for (int i = 23; i > 0; i--) {
        this->deltas[i] = this->deltas[i - 1];
    }
    if (this->lastPressureSinceDelta > 0) {
        this->deltas[0] = pressure - this->lastPressureSinceDelta;
    }
    this->lastPressureSinceDelta = pressure;
}
