#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <memory>

class Utils
{
public:
    static int floatToint(float a)
    {
        return static_cast<int>(std::round(a));
    }

    static int floatToAbsInt(float a)
    {
        return abs(static_cast<int>(std::round(a)));
    }

    static bool cmpff(float A, float B, float epsilon = 0.005f)
    {
        return (fabs(A - B) < epsilon);
    }

    static bool cmpNextPosAndPos(const glm::vec3 &A, const glm::vec3 &B, float epsilon = 0.005f)
    {
        return (cmpff(A.x, B.x, epsilon) && cmpff(A.z, B.z, epsilon));
    }

    template<typename T, typename... Args>
    static std::unique_ptr<T> make_unique(Args &&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    static glm::vec3
    getNextPosition(const glm::vec3 &pos, const DirectionType &currentDirection, const DirectionType &nextDirectionType)
    {
        switch (nextDirectionType)
        {
            case NORTH:
                switch (currentDirection)
                {
                    case NORTH:return glm::vec3 { pos.x, pos.y, pos.z - 1 };
                    case EAST:return glm::vec3 { pos.x + 1, pos.y, pos.z };
                    case SOUTH:return glm::vec3 { pos.x, pos.y, pos.z + 1 };
                    case WEST:return glm::vec3 { pos.x - 1, pos.y, pos.z };
                    case NEUTRAL:break;
                }

            case EAST:
                switch (currentDirection)
                {
                    case NORTH:return glm::vec3 { pos.x + 1, pos.y, pos.z };
                    case EAST:return glm::vec3 { pos.x, pos.y, pos.z + 1 };
                    case SOUTH:return glm::vec3 { pos.x - 1, pos.y, pos.z };
                    case WEST:return glm::vec3 { pos.x, pos.y, pos.z - 1 };
                    case NEUTRAL:break;
                }

            case SOUTH:
                switch (currentDirection)
                {
                    case NORTH:return glm::vec3 { pos.x, pos.y, pos.z + 1 };
                    case EAST:return glm::vec3 { pos.x - 1, pos.y, pos.z };
                    case SOUTH:return glm::vec3 { pos.x, pos.y, pos.z - 1 };
                    case WEST:return glm::vec3 { pos.x + 1, pos.y, pos.z };
                    case NEUTRAL:break;
                }

            case WEST:
                switch (currentDirection)
                {
                    case NORTH:return glm::vec3 { pos.x - 1, pos.y, pos.z };
                    case EAST:return glm::vec3 { pos.x, pos.y, pos.z - 1 };
                    case SOUTH:return glm::vec3 { pos.x + 1, pos.y, pos.z };
                    case WEST:return glm::vec3 { pos.x, pos.y, pos.z + 1 };
                    case NEUTRAL:break;
                }

            default:return pos;
        }
    }
};
