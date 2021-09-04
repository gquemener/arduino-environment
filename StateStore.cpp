#include "StateStore.h"

StateStore::StateStore(Subscriber *subscriber, Logger *logger)
{
    this->state = new State();
    this->subscriber = subscriber;
    this->logger = logger;
}

void StateStore::dispatch(char type, unsigned long timestamp, String data)
{
    this->logger->info(String(type) + " " + data);

    bool stateHasChanged = false;

    switch (type) {
        case ATMOS_PRESSURE_WAS_MEASURED:
            if (this->lastTimestamps[0] == 0 || timestamp - this->lastTimestamps[0] >= 108 * 1000) {
                this->state->addPressure(data.toInt());
                this->lastTimestamps[0] = timestamp;
                stateHasChanged = true;
            }
            if (timestamp - this->lastTimestamps[1] >= 3600 * 1000) {
                this->state->addDelta(data.toInt());
                this->lastTimestamps[1] = timestamp;
                stateHasChanged = true;
            }
            break;
    }
    if (stateHasChanged) {
        this->subscriber->handle(this->state);
    }
}
