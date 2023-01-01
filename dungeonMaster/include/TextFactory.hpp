#pragma once

#include "Text.hpp"


enum TextType
{
    MENU_MESSAGE,
    MONEY_QTY_MESSAGE
};

class TextFactory
{
private:
    GLuint                 &_vao;
    GLint                  &_uModelMatrix;
    GLint                  &_uTexture;
    Program                &_program;
    const glimac::FilePath &_applicationPath;
    const unsigned int     windowWidth;
    const unsigned int     windowHeight;

    Text createMoneyQtyText(const std::string &text);

    Text createMenuText();

public:
    TextFactory(GLuint &vao, GLint &uModelMatrix, GLint &uTexture, Program &program,
                const glimac::FilePath &applicationPath, unsigned int windowWidth, unsigned int windowHeight);

    Text createText(const TextType &textType, const std::string &text);


};