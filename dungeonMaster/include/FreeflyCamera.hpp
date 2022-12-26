#pragma once

#include "glimac/glm.hpp"
#include <GL/glew.h>
#include "DirectionType.hpp"

class FreeflyCamera
{
public:
    FreeflyCamera();

    ~FreeflyCamera() = default;

    void moveLeft(float t);

    void moveFront(float t);

    void rotateLeft(float degrees);

    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;

    glm::vec3 getPosition() const;

    DirectionType getCameraDirection() const;

private:
    DirectionType _cameraDirection;
    glm::vec3     _position;
    float         _fPhi;
    float         _fTheta;
    glm::vec3     _frontVector;
    glm::vec3     _leftVector;
    glm::vec3     _upVector;

    void computeDirectionVectors();

    void setPosition(glm::vec3 position);

    void setCameraDirection(DirectionType directionType);

    friend class Game;
};