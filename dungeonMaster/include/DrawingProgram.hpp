#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <vector>

#include "DirectionType.hpp"
#include "FreeflyCamera.hpp"
#include "ObjectType.hpp"

class TextureManager;

class DrawingProgram
{
public:
    explicit DrawingProgram(const glimac::FilePath &applicationPath, const std::string &vertexShader,
                            const std::string &fragmentShader, FreeflyCamera &camera, float _width,
                            float _height, const TextureManager &textureManager);

    ~DrawingProgram() = default;

    void use();

    void drawMap(const std::vector<std::vector<ObjectType>> &map, int width, int height);

    void drawWall(float x, float y, float z, DirectionType wallOrientation);

    void drawFloor(float x, float y, float z);

private:
    const TextureManager &_textureManager;
    glimac::Program      _program;
    FreeflyCamera        &_camera;
    glm::mat4            _projMatrix;
    GLint                _uMVPMatrix;
    GLint                _uMVMatrix;
    GLint                _uNormalMatrix;
    GLint                _uTexture;

    void setUniformMatrix(glm::mat4 MVMMatrix);


};
