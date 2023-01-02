#include "../include/Menu.hpp"

Menu::Menu(unsigned int windowWidth, unsigned int windowHeight, const glimac::FilePath &applicationPath,
           std::unique_ptr<DrawingProgram> &drawingProgram, SDLWindowManager &windowManager)
        : _drawingProgram(drawingProgram)
        , _textManager(windowWidth, windowHeight, applicationPath)
        , _windowWidth(windowWidth)
        , _windowHeight(windowHeight)
        , _windowManager(windowManager) {}


void Menu::drawMenuStarting(bool &gameInterrupted)
{
    bool startGame = false;
    _drawingProgram->programUse();
    while (!startGame && !gameInterrupted)
    {
        SDL_Event e;
        while (_windowManager.pollEvent(e))
        {
            switch (e.type)
            {
                case SDL_QUIT:gameInterrupted = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        startGame = true;
                    }
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _drawingProgram->drawMenuStarting();
        _windowManager.swapBuffers();
    }
}

void Menu::drawMenuInGame(const Player &player)
{
    _textManager.drawMenuInGame(player);
}

bool Menu::drawMenuEnding(bool gameWin, bool gameLost, bool &gameInterrupted)
{
    if (gameInterrupted)
    {
        return false;
    }

    bool replay   = false;
    bool quitLoop = false;
    _drawingProgram->programUse();
    while (!quitLoop && !gameInterrupted)
    {
        SDL_Event e;
        while (_windowManager.pollEvent(e))
        {
            switch (e.type)
            {
                case SDL_QUIT:gameInterrupted = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (gameWin)
                        {
                            quitLoop        = true;
                            gameInterrupted = true;
                        }
                        else if (gameLost)
                        {
                            if (isButtonClicked(e.button.x, e.button.y, BUTTONS_LEFT_BORDER, BUTTONS_RIGHT_BORDER,
                                                RETRY_BUTTON_TOP_BORDER, RETRY_BUTTON_BOTTOM_BORDER))
                            {
                                quitLoop = true;
                                replay   = true;
                            }
                            else if (isButtonClicked(e.button.x, e.button.y, BUTTONS_LEFT_BORDER, BUTTONS_RIGHT_BORDER,
                                                     QUIT_BUTTON_TOP_BORDER, QUIT_BUTTON_BOTTOM_BORDER))
                            {
                                quitLoop        = true;
                                gameInterrupted = true;
                            }
                        }

                    }
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (gameWin)
        {
            _drawingProgram->drawMenuWin();
        }
        else
        {
            _drawingProgram->drawMenuLose();
        }

        _windowManager.swapBuffers();
    }

    return replay;
}

bool Menu::isButtonClicked(float x, float y, float leftBorder, float rightBorder, float topBorder, float bottomBorder)
{
    return x >= leftBorder * _windowWidth &&
           x <= rightBorder * _windowWidth &&
           y >= topBorder * _windowHeight &&
           y <= bottomBorder * _windowHeight;
}



