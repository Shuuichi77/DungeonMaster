#include "../include/FreeflyCamera.hpp"

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
    _position = glm::vec3(position.x, position.y, -position.z);
}

void FreeflyCamera::setCameraDirection(DirectionType directionType)
{
    _cameraDirection = directionType;
}

