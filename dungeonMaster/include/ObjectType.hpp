#pragma once

#include <glm/glm.hpp>

enum ObjectType
{
    EMPTY,
    WALL,
    DOOR,
    KEY,
    CHEST,
    PLAYER,
    ENEMY,
    EXIT,
};

/*
    (1, 0, -3)  -> [3][1]
    (1, 0, -2)  -> [2][1]
    (1, 0, -1)  -> [1][1]
    (1, 0, 0)   -> [0][1]


*/