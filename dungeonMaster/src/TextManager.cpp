#include "../include/TextManager.hpp"

TextManager::TextManager(unsigned int windowWidth, unsigned int windowHeight,
                         const glimac::FilePath &applicationPath, std::string fontFileName, const Player &player)
        : _windowState(GAME)
        , _windowWidth(windowWidth)
        , _windowHeight(windowHeight)
        , _applicationPath(applicationPath)
        , _fontFileName(std::move(fontFileName))
        , _program(loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
                               applicationPath.dirPath() + "shaders/tex2D.fs.glsl"))
        , _textFactory(_vao, _uModelMatrix, _uTexture, _program, applicationPath, windowWidth, windowHeight)
{
    _uModelMatrix = glGetUniformLocation(_program.getGLId(), "uModelMatrix");
    _uTexture     = glGetUniformLocation(_program.getGLId(), "uTexture");

    loadVBO();
    loadIBO();
    loadVAO();

    initMessages(player);
}

void TextManager::loadVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    Vertex2DUV vertices[] = {
            Vertex2DUV(glm::vec2(-1, 1), glm::vec2(0, 0)),
            Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)),
            Vertex2DUV(glm::vec2(1, -1), glm::vec2(1, 1)),
            Vertex2DUV(glm::vec2(1, 1), glm::vec2(1, 0)),
    };

    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TextManager::loadIBO()
{
    uint32_t indices[] = {
            0, 1, 2, 0, 2, 3
    };

    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TextManager::loadVAO()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COULEUR);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV),
                          (const GLvoid *) (offsetof(Vertex2DUV, position)));
    glVertexAttribPointer(VERTEX_ATTR_COULEUR, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV),
                          (const GLvoid *) (offsetof(Vertex2DUV, color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TextManager::initMessages(const Player &player)
{
    _texts.emplace(TextType::MONEY_QTY_MESSAGE,
                   _textFactory.createText(TextType::MONEY_QTY_MESSAGE, std::to_string(player.getMoney())));
}

void TextManager::setWindowState()
{
    switch (_windowState)
    {
        case MENU:_windowState = MENU;
            break;
        case GAME:_windowState = GAME;
            break;
        case LOSE:_windowState = LOSE;
            break;
        case WIN:_windowState = WIN;
            break;
        default:std::cerr << "Error: window state not found" << std::endl;
            break;
    }
}

void TextManager::draw()
{
    switch (_windowState)
    {
        case MENU:drawMenu();
            break;
        case GAME:drawGame();
            break;
        case LOSE:drawLose();
            break;
        case WIN:drawWin();
            break;
        default:std::cerr << "Error: window state not found" << std::endl;
            break;
    }
}

void TextManager::updatePlayerTexts(const Player &player)
{
    try
    {
        std::cout << "player.getMoney() = " << player.getMoney() << std::endl;
        _texts.at(TextType::MONEY_QTY_MESSAGE).update(std::to_string(player.getMoney()));
    } catch (std::out_of_range &e)
    {
        std::cerr << "TextType " << TextType::MONEY_QTY_MESSAGE << " not found" << std::endl;
    }

}

void TextManager::drawMenu()
{

}

void TextManager::drawGame()
{
    _texts.at(TextType::MONEY_QTY_MESSAGE).draw();
}

void TextManager::drawLose()
{

}

void TextManager::drawWin()
{

}





