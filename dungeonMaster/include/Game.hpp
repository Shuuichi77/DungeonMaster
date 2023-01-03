#pragma one

#include <glm/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "TextureManager.hpp"
#include "DrawingProgram.hpp"
#include "CameraManager.hpp"
#include "Interface.hpp"
#include "CharacterManager.hpp"
#include "Menu.hpp"
#include "Music.hpp"

using namespace glimac;
using namespace glm;
using namespace std;


class Game
{
private:
    static constexpr const char *DEFAULT_MAP                     = "dungeon_02.txt";
    bool                        _gameInterrupted                 = false;
    bool                        _gameLost                        = false;
    bool                        _retryGame                       = false;
    unsigned int                _nbMoneyNeededToFinishGame       = 0;
    unsigned int                _nbMonsterKillNeededToFinishGame = 0;

    Music                                _music;
    FreeflyCamera                        _camera;
    glimac::FilePath                     _applicationPath;
    unsigned int                         _windowWidth;
    unsigned int                         _windowHeight;
    std::vector<std::vector<MapElement>> _map;
    glm::vec3                            _exitPosition;
    glimac::SDLWindowManager             _windowManager;
    const std::string                    _mapName;

    CameraManager                     _cameraManager;
    std::unique_ptr<Menu>             _menu;
    std::unique_ptr<TextureManager>   _textureManager;
    std::unique_ptr<DrawingProgram>   _drawingProgram;
    std::unique_ptr<CharacterManager> _characterManager;

    glm::vec3 WALL_COLOR  = glm::vec3(0, 0, 0);
    glm::vec3 EMPTY_COLOR = glm::vec3(255, 255, 255);
    glm::vec3 DOOR_COLOR  = glm::vec3(170, 119, 34);
    glm::vec3 WATER_COLOR = glm::vec3(0, 0, 255);
    glm::vec3 ENTRY_COLOR = glm::vec3(255, 0, 0);
    glm::vec3 EXIT_COLOR  = glm::vec3(0, 255, 0);

    static int initGlew();

    void initPtr();

    void initMap();

    MapElement getMapElementFromColor(const vec3 &color);

    std::vector<std::vector<MapElement>> readMap(const std::string &mapFile,
                                                 std::vector<std::unique_ptr<InteractableObject>> &doors);

    std::string readDungeonFile(const std::string &dungeonFile,
                                std::vector<std::unique_ptr<InteractableObject>> &interableObjects,
                                std::vector<std::unique_ptr<Monster>> &monsters);

    void loop();

    bool gameWin() const;

    void initMapElementColors(int maxColor);

public:
    explicit Game(glimac::FilePath filePath, unsigned int windowHeight);

    explicit Game(glimac::FilePath filePath, unsigned int windowHeight, std::string mapName);

    ~Game() = default;;

    int run();

    void createGame();
};