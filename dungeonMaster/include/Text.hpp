#pragma once

#include <iostream>
#include <SDL/SDL_ttf.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glimac/FilePath.hpp"
#include "glimac/Program.hpp"

#include "../include/FreeflyCamera.hpp"

using namespace glm;
using namespace glimac;

enum TextAlignement
{
    LEFT,
    CENTER,
    RIGHT
};

class Text
{
private:
    GLuint      _texture;
    std::string _text;
    float       _sx;
    float       _sy;
    float       _tx;
    float       _ty;

    GLuint                 &_vao;
    Program                &_program;
    GLint                  &_uModelMatrix;
    GLint                  &_uTexture;
    SDL_Color              _color;
    const unsigned int     _windowWidth;
    const unsigned int     _windowHeight;
    const glimac::FilePath _applicationPath;
    const std::string      _fontPath;
    const TextAlignement   _textAlignement;
    const float            _x;
    const float            _y;
    const float            _size;

    void initText(const std::string &text);

public:
    Text(const std::string &text, const SDL_Color &color, GLuint &vao, GLint &uModelMatrix, GLint &uTexture,
         Program &program, const glimac::FilePath &applicationPath, const std::string &fontPath,
         unsigned int windowWidth, unsigned int windowHeight, int size, float x, float y,
         const TextAlignement &textAlignement);

    ~Text() = default;

    void draw();

    void update(const std::string &text);
};