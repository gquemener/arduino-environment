#include "StateStore.h"

StateStore::StateStore(Subscriber *subscriber, Logger *logger)
{
    this->state = new State();
    this->subscriber = subscriber;
    this->logger = logger;
}

void StateStore::dispatch(char type, String data)
{
    this->logger->info(String(type) + " " + data);
    switch (type) {
      case ATMOS_PRESSURE_WAS_MEASURED:
        this->state->addPressure(data.toInt());
        break;
    }

    this->subscriber->handle(this->state);
}
