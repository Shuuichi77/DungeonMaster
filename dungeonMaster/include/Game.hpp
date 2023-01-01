#pragma one

#include <glm/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "TextureManager.hpp"
#include "DrawingProgram.hpp"
#include "CameraManager.hpp"
#include "Interface.hpp"
#include "CharacterManager.hpp"

using namespace glimac;
using namespace glm;
using namespace std;


class Game
{
private:
    bool                                 _gameWin   = false;
    bool                                 _gamelLost = false;
    FreeflyCamera                        _camera;
    glimac::FilePath                     _applicationPath;
    unsigned int                         _windowWidth;
    unsigned int                         _windowHeight;
    std::vector<std::vector<MapElement>> _map;

    glimac::SDLWindowManager          _windowManager;
    CameraManager                     _cameraManager;
    std::unique_ptr<TextureManager>   _textureManager;
    std::unique_ptr<DrawingProgram>   _drawingProgram;
    std::unique_ptr<CharacterManager> _characterManager;

    int initGlew();

    void initPtr();

    void initMap();

    void loop();

public:
    explicit Game(glimac::FilePath filePath, unsigned int windowHeight);

    ~Game() = default;;

    int run();

    void updatePlayer();
};