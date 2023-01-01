#pragma once

#include <glm/glm.hpp>

enum DirectionType : unsigned int
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NEUTRAL // For fix model, like health bar
};

inline DirectionType &operator++(DirectionType &type)
{
    type = static_cast<DirectionType>((static_cast<unsigned int>(type) + 1) % 4);
    return type;
}

inline DirectionType &operator--(DirectionType &type)
{
    if (type == NORTH)
    {
        type = WEST;
    }
    else
    {
        type = static_cast<DirectionType>((static_cast<int>(type) - 1) % 4);
    }

    return type;
}