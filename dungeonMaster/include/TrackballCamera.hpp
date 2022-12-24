#pragma once

#include "glimac/glm.hpp"
#include <GL/glew.h>

class TrackballCamera
{
public:
    TrackballCamera();

    ~TrackballCamera();

    void moveFront(float delta);

    void rotateLeft(float degrees);

    void rotateUp(float degrees);

    glm::mat4 getViewMatrix() const;

private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
};
