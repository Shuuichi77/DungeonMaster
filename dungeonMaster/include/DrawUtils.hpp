#pragma once

#include <glm/glm.hpp>
#include <glimac/common.hpp>

using namespace glm;
using namespace glimac;

class DrawUtils
{
private:

public:
    static void
    setUniformMatrix(const mat4 &MVMMatrix, const mat4 &viewMatrix, const mat4 &projMatrix, GLuint uMVPMatrix,
                     GLuint uMVMatrix, GLuint uNormalMatrix)
    {
        mat4 MVMatrix     = viewMatrix * MVMMatrix;
        mat4 NormalMatrix = transpose(inverse(MVMatrix));
        mat4 MVPMatrix    = projMatrix * MVMatrix;

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, value_ptr(MVPMatrix));
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, value_ptr(NormalMatrix));
    }
};