#include "../include/Text.hpp"
#include "../include/DrawUtils.hpp"

Text::Text(const std::string &text, const SDL_Color &color, GLuint &vao, GLint &uModelMatrix, GLint &uTexture,
           Program &program, const glimac::FilePath &applicationPath, const std::string &fontPath,
           unsigned int windowWidth, unsigned int windowHeight, int size, float x, float y,
           const TextAlignement &textAlignement)
        : _text(text)
        , _color(color)
        , _vao(vao)
        , _uModelMatrix(uModelMatrix)
        , _uTexture(uTexture)
        , _program(program)
        , _windowWidth(windowWidth)
        , _windowHeight(windowHeight)
        , _applicationPath(applicationPath)
        , _textAlignement(textAlignement)
        , _x(x)
        , _y(y)
        , _fontPath(fontPath)
        , _size(size)
{
    glGenTextures(1, &_texture);
    initText(text);
}

void Text::update(const std::string &text)
{
    initText(text);
}

void Text::initText(const std::string &text)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont((_applicationPath.dirPath() + "/assets/fonts/" + _fontPath).c_str(), _size);
    if (font == nullptr)
    {
        std::cerr << "Error while loading font" << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), _color);
    if (surface == nullptr)
    {
        std::cerr << "Error while creating surface" << std::endl;
        exit(EXIT_FAILURE);
    }

    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);

    _sx = (float) surface->w / float(_windowWidth);
    _sy = (float) surface->h / float(_windowHeight);

    int textWidth;
    int textHeight;
    switch (_textAlignement)
    {
        case LEFT: //
            TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
            _tx = (-1 + _x * 2) + ((float) textWidth / float(_windowWidth));
            _ty = 1 - (_y * 2);
            break;

        case RIGHT: //
            TTF_SizeText(font, text.c_str(), &textWidth, &textHeight);
            _tx = (-1 + _x * 2) - ((float) textWidth / float(_windowWidth));
            _ty = 1 - (_y * 2);
            break;

        case CENTER: //
            _tx = -1 + _x * 2;
            _ty = 1 - (_y * 2);
            break;

    }

    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
}

mat3 scale2D(const float sx, const float sy)
{
    return glm::mat3 { glm::vec3(sx, 0., 0.), glm::vec3(0., sy, 0.), glm::vec3(0., 0., 1.) };
}

mat3 translate2D(const float tx, const float ty)
{
    return glm::mat3 { glm::vec3(1., 0., 0.), glm::vec3(0., 1., 0.), glm::vec3(tx, ty, 1.) };
}

void Text::draw()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    _program.use();
    glBindVertexArray(_vao);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(_uTexture, 0);

    mat3 uModelMatrix = translate2D(_tx, _ty) * scale2D(_sx, _sy);
    glUniformMatrix3fv(_uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

