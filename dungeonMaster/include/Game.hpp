#pragma one

#include <glm/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "TextureManager.hpp"
#include "DrawingProgram.hpp"
#include "CameraManager.hpp"

using namespace glimac;
using namespace glm;
using namespace std;

class Game
{
private:
    bool                                 _done = false;
    FreeflyCamera                        _camera;
    glimac::FilePath                     _filePath;
    float                                _windowWidth;
    float                                _windowHeight;
    std::vector<std::vector<ObjectType>> _map;

    glimac::SDLWindowManager        _windowManager;
    CameraManager                   _cameraManager;
    std::unique_ptr<TextureManager> _textureManager;
    std::unique_ptr<DrawingProgram> _drawingProgram;
    std::unique_ptr<ModelManager>   _modelManager;

public:
    explicit Game(glimac::FilePath filePath, float windowWidth, float windowHeight);

    ~Game() = default;;

    int run();

    void createMap();

    void exitGame();
};