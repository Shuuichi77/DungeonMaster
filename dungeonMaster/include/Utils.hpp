#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Utils
{
public:
    static int floatToInt(float a)
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

    static bool cmpVec4(const glm::vec4 &A, const glm::vec4 &B, float epsilon = 0.0005f)
    {
        return (cmpff(A.x, B.x, epsilon) && cmpff(A.y, B.y, epsilon) && cmpff(A.z, B.z, epsilon) &&
                cmpff(A.w, B.w, epsilon));
    }

    static std::vector<std::string> splitStringByDelimiter(const std::string stringToSplit,
                                                           const std::string &delimiter)
    {
        size_t                   pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string              token;
        std::vector<std::string> res;

        while ((pos_end = stringToSplit.find(delimiter, pos_start)) != std::string::npos)
        {
            token     = stringToSplit.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(stringToSplit.substr(pos_start));
        return res;
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
