#include "../include/ChronoBetweenActions.hpp"
#include <iostream>

ChronoBetweenActions::ChronoBetweenActions()
{
    timeBetweenActions = 1000;
}


ChronoBetweenActions::ChronoBetweenActions(unsigned int timeBetweenActions)
        : timeBetweenActions(timeBetweenActions) {}

void ChronoBetweenActions::reset()
{
    _lastAction         = std::chrono::system_clock::now();
    _timeBetweenActions = std::chrono::milliseconds(static_cast<int>(timeBetweenActions));
}

bool ChronoBetweenActions::isTimeElapsed()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

    std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastAction);

    if (elapsed > _timeBetweenActions)
    {
        reset();
        return true;
    }

    return false;
}





