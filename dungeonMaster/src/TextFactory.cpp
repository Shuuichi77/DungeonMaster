#include "../include/TextFactory.hpp"

TextFactory::TextFactory(GLuint &vao, GLint &uModelMatrix, GLint &uTexture, Program &program,
                         const glimac::FilePath &applicationPath, unsigned int windowWidth, unsigned int windowHeight)
        : _vao(vao)
        , _uModelMatrix(uModelMatrix)
        , _uTexture(uTexture)
        , _program(program)
        , _applicationPath(applicationPath)
        , windowWidth(windowWidth)
        , windowHeight(windowHeight) {}

Text TextFactory::createText(const TextType &textType, const std::string &text)
{
    switch (textType)
    {
        case MONEY_QTY_MESSAGE:return createMoneyQtyText(text);
        case MONSTERS_KILLED_QTY_MESSAGE:return createMonsterKilledQty(text);
    }
}

Text TextFactory::createMoneyQtyText(const std::string &text)
{
    return Text(text, { 255, 255, 255 }, _vao, _uModelMatrix, _uTexture, _program,
                _applicationPath, FONT_FILE_NAME, windowWidth, windowHeight,
                windowWidth * 0.03, 0.0655, 0.0825, TextAlignement::LEFT);
}

Text TextFactory::createMonsterKilledQty(const std::string &text)
{
    return Text(text, { 255, 255, 255 }, _vao, _uModelMatrix, _uTexture, _program,
                _applicationPath, FONT_FILE_NAME, windowWidth, windowHeight,
                windowWidth * 0.03, 0.0655, 0.13, TextAlignement::LEFT);
}