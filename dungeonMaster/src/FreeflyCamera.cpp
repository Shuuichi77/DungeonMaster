#include "../include/FreeflyCamera.hpp"
#include "../include/Utils.hpp"

#include <iostream>

void FreeflyCamera::computeDirectionVectors()
{
    _frontVector = glm::vec3(cos(_fTheta) * sin(_fPhi), sin(_fTheta), cos(_fTheta) * cos(_fPhi));
    _leftVector  = glm::vec3(sin(_fPhi + M_PI / 2), 0, cos(_fPhi + M_PI / 2));
    _upVector    = glm::cross(_frontVector, _leftVector);
}

FreeflyCamera::FreeflyCamera()
{
    _position        = glm::vec3(0, 0, 0);
    _fPhi            = M_PI;
    _fTheta          = 0;
    _cameraDirection = DirectionType::NORTH;

    computeDirectionVectors();
}

void FreeflyCamera::moveLeft(float t)
{
    _position += t * _leftVector;
}

void FreeflyCamera::moveFront(float t)
{
    _position += t * _frontVector;
}

void FreeflyCamera::rotateLeft(float degrees)
{
    _fPhi += glm::radians(degrees);
    computeDirectionVectors();

    if (degrees > 0.f)
    {
        --_cameraDirection;
    }
    else
    {
        ++_cameraDirection;
    }
}

void FreeflyCamera::rotateUp(float degrees)
{
    _fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const
{
    return glm::lookAt(_position, _position + _frontVector, _upVector);
}

glm::vec3 FreeflyCamera::getPosition() const
{
    return _position;
}

DirectionType FreeflyCamera::getCameraDirection() const
{
    return _cameraDirection;
}

void FreeflyCamera::setPosition(glm::vec3 position)
{
    _position = glm::vec3(position.x, position.y, position.z);
}

bool FreeflyCamera::setDirectionTypeWithMap(const std::vector<std::vector<MapElement>> &map)
{
    int i = Utils::floatToAbsInt(_position.z);
    int j = Utils::floatToAbsInt(_position.x);

    if (i == 0)
    {
        if (map[i + 1][j] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::NORTH;
        }
        else if (map[i][j + 1] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::EAST;
        }
        else if (map[i][j - 1] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::WEST;
        }
        else
        {
            return false;
        }

        return true;
    }

    else if (i == map.size() - 1)
    {
        if (map[i - 1][j] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::SOUTH;
        }
        else if (map[i][j + 1] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::EAST;
        }
        else if (map[i][j - 1] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::WEST;
        }
        else
        {
            return false;
        }
    }

    else if (j == 0)
    {
        if (map[i + 1][j] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::NORTH;
        }
        else if (map[i - 1][j] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::SOUTH;
        }
        else if (map[i][j + 1] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::EAST;
        }
        else
        {
            return false;
        }
    }

    else if (j == map[i].size() - 1)
    {
        if (map[i + 1][j] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::NORTH;
        }
        else if (map[i - 1][j] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::SOUTH;
        }
        else if (map[i][j - 1] != MapElement::WALL)
        {
            _cameraDirection = DirectionType::WEST;
        }
        else
        {
            return false;
        }

        return true;
    }

    return false;
}

