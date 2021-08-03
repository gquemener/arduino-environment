#include "StateStore.h"

StateStore::StateStore(Subscriber *subscriber, Logger *logger)
{
    this->state = new State();
    this->subscriber = subscriber;
    this->logger = logger;
}

void StateStore::dispatch(char type, String data)
{
  this->logger->info(data);
    switch (type) {
        case CLOCK_HAS_TICKED:
            this->state->datetime = data;
            break;

        case ATMOS_PRESSURE_WAS_MEASURED:
            this->state->atmosPressure = data;
            break;
            
        case TEMPERATURE_WAS_MEASURED:
            this->state->temperature = data;
            break;
    }

    this->subscriber->handle(this->state);
}
