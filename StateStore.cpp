#include "StateStore.h"

StateStore::StateStore(Logger *logger)
{
    this->state = new State();
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
    
    for (int i = 0; i < this->subscribersIndex; i++) {
      this->subscribers[i]->handle(type, this->state);
    }
}

void StateStore::subscribe(Subscriber *subscriber)
{
  this->subscribers[this->subscribersIndex++] = subscriber;
}
