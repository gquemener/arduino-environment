#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "State.h"

class Subscriber
{
  public:
    virtual void handle(State *state) = 0;
};

#endif
