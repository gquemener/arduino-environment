#include "State.h"

State::State(String datetime, String atmosPressure)
{
    _datetime = datetime;
    _atmosPressure = atmosPressure;
}

String State::datetime()
{
    return _datetime;
}

String State::atmosPressure()
{
    return _atmosPressure;
}
