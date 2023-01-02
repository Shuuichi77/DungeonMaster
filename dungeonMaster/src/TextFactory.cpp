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
        case MENU_MESSAGE:return createMenuText();
        case MONEY_QTY_MESSAGE:return createMoneyQtyText(text);
    }
}

Text TextFactory::createMoneyQtyText(const std::string &text)
{
    return Text(text, { 255, 255, 255 }, _vao, _uModelMatrix, _uTexture, _program,
                _applicationPath, FONT_FILE_NAME, windowWidth, windowHeight,
                50, 0.0625, 0.0825, TextAlignement::LEFT);
}

Text TextFactory::createMenuText()
{
    return Text("TEMP", { 255, 255, 255 }, _vao, _uModelMatrix, _uTexture, _program,
                _applicationPath, FONT_FILE_NAME, windowWidth, windowHeight,
                windowWidth * 0.03, 0.0625, 0.0808, TextAlignement::LEFT);
}