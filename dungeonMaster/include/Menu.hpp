#pragma once

#include <glm/glm.hpp>
#include "TextManager.hpp"
#include "glimac/FilePath.hpp"
#include "DrawingProgram.hpp"
#include "Music.hpp"

class Menu
{
private:
    static constexpr const float BUTTONS_LEFT_BORDER  = 0.412758f;
    static constexpr const float BUTTONS_RIGHT_BORDER = 0.590056f;

    static constexpr const float RETRY_BUTTON_TOP_BORDER    = 0.58625f;
    static constexpr const float RETRY_BUTTON_BOTTOM_BORDER = 0.65375;

    static constexpr const float QUIT_BUTTON_TOP_BORDER    = 0.7f;
    static constexpr const float QUIT_BUTTON_BOTTOM_BORDER = 0.7675f;

    std::unique_ptr<DrawingProgram> &_drawingProgram;
    SDLWindowManager                &_windowManager;
    TextManager                     _textManager;
    unsigned int                    _windowWidth;
    unsigned int                    _windowHeight;

public:
    Menu(unsigned int windowWidth, unsigned int windowHeight, const glimac::FilePath &applicationPath,
         std::unique_ptr<DrawingProgram> &drawingProgram, SDLWindowManager &windowManager,
         unsigned int nbMoneyNeededToFinishGame, unsigned int nbMonsterKillNeededToFinishGame);

    ~Menu() = default;

    void drawMenuStarting(bool &gameInterrupted);

    void drawMenuInGame(const Player &player);

    bool drawMenuEnding(bool gameWin, bool gameLost, bool &gameInterrupted, Music music);

    bool isButtonClicked(float x, float y, float leftBorder, float rightBorder, float topBorder, float bottomBorder);
};