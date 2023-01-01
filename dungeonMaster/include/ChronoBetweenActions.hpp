#pragma once

#include <chrono>

class ChronoBetweenActions
{
private:
    unsigned int timeBetweenActions; // in milliseconds

    std::chrono::time_point<std::chrono::system_clock> _lastAction;
    std::chrono::milliseconds                          _timeBetweenActions {};

public:
    ChronoBetweenActions();

    explicit ChronoBetweenActions(unsigned int timeBetweenActions);

    void reset();

    bool isTimeElapsed();
};