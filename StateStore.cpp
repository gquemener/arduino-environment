#include "StateStore.h"

StateStore::StateStore(Subscriber *subscriber, Logger *logger)
{
    this->state = new State("", "");
    this->subscriber = subscriber;
    this->logger = logger;
}

void StateStore::dispatch(char type, String data)
{
    State* prev = this->state;
    switch (type) {
        case CLOCK_HAS_TICKED:
            this->state = new State(data, this->state->atmosPressure());
            delete prev;
            break;

        case ATMOS_PRESSURE_WAS_MEASURED:
            this->state = new State(this->state->datetime(), data);
            delete prev;
            break;
    }
    this->logger->info(String(type) + ": " + data);

    this->subscriber->handle(this->state);
}
