#include "../include/TrackballCamera.hpp"

TrackballCamera::TrackballCamera()
{
    m_fDistance = 5;
    m_fAngleX   = 0;
    m_fAngleY   = 0;
}

TrackballCamera::~TrackballCamera() = default;

void TrackballCamera::moveFront(float delta)
{
    m_fDistance += delta;
}

void TrackballCamera::rotateLeft(float degrees)
{
    m_fAngleY += degrees;
}

void TrackballCamera::rotateUp(float degrees)
{
    m_fAngleX += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const
{
    glm::mat4 matrixId         = glm::mat4(1);
    glm::mat4 matrixMoveFront  = glm::translate(matrixId, glm::vec3(0, 0, -m_fDistance));
    glm::mat4 matrixRotateLeft = glm::rotate(matrixId, glm::radians(m_fAngleX), glm::vec3(1, 0, 0));
    glm::mat4 matrixRotateUp   = glm::rotate(matrixId, glm::radians(m_fAngleY), glm::vec3(0, 1, 0));

    return matrixMoveFront * matrixRotateLeft * matrixRotateUp;
}