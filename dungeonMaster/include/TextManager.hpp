#pragma once

#include <iostream>
#include <vector>
#include "Text.hpp"
#include "Player.hpp"
#include "TextFactory.hpp"


class TextManager
{
private:
    struct Vertex2DUV
    {
        glm::vec2 position;
        glm::vec2 color;

        Vertex2DUV(const glm::vec2 &p, const glm::vec2 &c)
        {
            position = p;
            color    = c;
        }
    };

    static const GLuint VERTEX_ATTR_POSITION = 0;
    static const GLuint VERTEX_ATTR_COULEUR  = 1;

    std::unordered_map<TextType, Text> _texts;

    const unsigned int _windowWidth;
    const unsigned int _windowHeight;
    const std::string  _fontFileName;
    TextFactory        _textFactory;

    GLuint  _vao;
    GLuint  _vbo;
    GLuint  _ibo;
    Program _program;
    GLint   _uModelMatrix;
    GLint   _uTexture;

    void loadVBO();

    void loadIBO();

    void loadVAO();

    void drawMenuInGame(const Player &player);
    
    void initMessages();

    friend class Menu;

public:
    TextManager(unsigned int windowWidth, unsigned int windowHeight,
                const glimac::FilePath &applicationPath);
};


