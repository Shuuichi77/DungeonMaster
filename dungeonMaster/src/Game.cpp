#include "../include/Game.hpp"
#include "../include/Utils.hpp"

#include <fstream>
#include <string>
#include <SDL/SDL_ttf.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <iostream>
#include <glimac/common.hpp>

#include <glimac/Image.hpp>
#include <utility>

Game::Game(glimac::FilePath filePath, unsigned int windowHeight)
        : _camera()
        , _applicationPath(std::move(filePath))
        , _windowWidth(windowHeight * 4 / 3)
        , _windowHeight(windowHeight)
        , _windowManager(windowHeight * 4 / 3, windowHeight, "Dungeon Master")
        , _cameraManager(_camera, _windowManager)
        , _mapName { DEFAULT_MAP }
        , _music { filePath } {}


Game::Game(glimac::FilePath filePath, unsigned int windowHeight, std::string mapName)
        : _camera()
        , _applicationPath(std::move(filePath))
        , _windowWidth(windowHeight * 4 / 3)
        , _windowHeight(windowHeight)
        , _windowManager(windowHeight * 4 / 3, windowHeight, "Dungeon Master")
        , _cameraManager(_camera, _windowManager)
        , _mapName { std::move(mapName) }
        , _music { filePath } {}


int Game::initGlew()
{
    srand(time(nullptr));

    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return EXIT_SUCCESS;
}

void Game::initMapElementColors(int maxColor)
{
    if (maxColor != 255)
    {
        WALL_COLOR /= 255;
        EMPTY_COLOR /= 255;
        DOOR_COLOR /= 255;
        WATER_COLOR /= 255;
        ENTRY_COLOR /= 255;
        EXIT_COLOR /= 255;
    }
}

MapElement Game::getMapElementFromColor(const vec3 &color)
{
    if (ENTRY_COLOR == color)
    {
        return MapElement::ENTRY;
    }
    else if (EMPTY_COLOR == color)
    {
        return MapElement::EMPTY;
    }
    else if (WATER_COLOR == color)
    {
        return MapElement::WATER;
    }
    else if (EXIT_COLOR == color)
    {
        return MapElement::EXIT;
    }
    else if (WALL_COLOR == color)
    {
        _textureManager->addRandomWallTexture();
        return MapElement::WALL;
    }
    else if (DOOR_COLOR == color)
    {
        return MapElement::DOOR;
    }

    else
    {
        return MapElement::UNKNOWN_MAP_ELEMENT;
    }
}

std::vector<std::vector<MapElement>> Game::readMap(const std::string &mapFile,
                                                   std::vector<std::unique_ptr<InteractableObject>> &doors)
{
    std::ifstream input(_applicationPath.dirPath() + "/maps/" + mapFile);
    if (!input)
    {
        std::cerr << "Error while opening the map file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    getline(input, line);
    string ppmFormat = line;
    if (ppmFormat == "P6")
    {
        // TODO: handle P6 format
        std::cerr << "Error while reading the map file: P6 format not supported (P3 only)" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Needs to ignore my .ppm 2nd line in header which is "# Created by GIMP version 2.10.18 PNM plug-in"
    int      nbLineToIgnore = 1;
    for (int i              = 0; i < nbLineToIgnore; ++i)
    {
        getline(input, line);
    }

    getline(input, line);
    int mapWidth  = std::stoi(line.substr(0, line.find(' ')));
    int mapHeight = std::stoi(line.substr(line.find(' ') + 1, line.size()));

    getline(input, line);
    int maxColor                           = std::stoi(line);
    initMapElementColors(maxColor);

    std::vector<std::vector<MapElement>> map;
    for (int                             i = 0; i < mapHeight; ++i)
    {
        std::vector<MapElement> row;
        for (int                j = 0; j < mapWidth; ++j)
        {
            int color[3];
            getline(input, line);
            color[0] = std::stoi(line.substr(0, line.find(' ')));

            getline(input, line);
            color[1] = std::stoi(line.substr(0, line.find(' ')));

            getline(input, line);
            color[2] = std::stoi(line.substr(0, line.find(' ')));

            MapElement mapElement = getMapElementFromColor(vec3(color[0], color[1], color[2]));

            if (mapElement == UNKNOWN_MAP_ELEMENT)
            {
                std::cerr << "Error while reading the map file: unknown map element at pixel "
                        << i << ", " << j << "with color : " << color[0] << ", " << color[1] << ", " << color[2]
                        << std::endl;
                row.push_back(MapElement::EMPTY);
            }

            if (mapElement != MapElement::DOOR)
            {
                if (mapElement == MapElement::ENTRY)
                {
                    _camera.setPosition(vec3(j, 0.25f, -(mapHeight - i - 1)));
                }

                else if (mapElement == MapElement::EXIT)
                {
                    _exitPosition = vec3(j, 0., -(mapHeight - i - 1));
                }

                row.push_back(mapElement);
            }
            else
            {
                doors.emplace_back(Utils::make_unique<InteractableObject>(InteractableObjectType::INTERACTABLE_DOOR,
                                                                          vec3(j, 0, -(mapHeight - i - 1)),
                                                                          DirectionType::SOUTH));
                row.push_back(MapElement::EMPTY);
            }
        }
        map.insert(map.begin(), row);
    }

    return map;
}

std::string Game::readDungeonFile(const string &dungeonFile,
                                  vector<std::unique_ptr<InteractableObject>> &interactableObjects,
                                  vector<std::unique_ptr<Monster>> &monsters)
{
    std::fstream input;
    input.open(_applicationPath.dirPath() + "/maps/" + dungeonFile, ios::in);

    if (!input.is_open())
    {
        std::cerr << "Error while opening the dungeon file: " << _applicationPath.dirPath() + "/maps/" + dungeonFile
                << std::endl;
        exit(EXIT_FAILURE);
    }

    string line;
    getline(input, line); // ignore first line

    getline(input, line);
    string mapFile = line;

    getline(input, line);
    int nbChests = std::stoi(line);

    for (int i = 0; i < nbChests; ++i)
    {
        getline(input, line);
        InteractableObject::createInteractableObject(line, interactableObjects);
    }

    getline(input, line);
    int      nbMonsters = std::stoi(line);
    for (int i          = 0; i < nbMonsters; ++i)
    {
        getline(input, line);
        Monster::createMonster(line, monsters);
    }

    getline(input, line);
    _nbMoneyNeededToFinishGame = std::stoi(line);

    getline(input, line);
    _nbMonsterKillNeededToFinishGame = std::stoi(line);

    input.close();

    return mapFile;
}

void Game::initMap()
{
    if (!_retryGame)
    {
        _textureManager = Utils::make_unique<TextureManager>(_applicationPath);
    }


    std::vector<std::unique_ptr<InteractableObject>> interactableObjects;
    std::vector<std::unique_ptr<Monster>>            monsters;

    string mapFile = readDungeonFile(_mapName, interactableObjects, monsters);
    _map = readMap(mapFile, interactableObjects);

    glm::vec3 cameraPosition = _camera.getPosition();
    if (!_camera.setDirectionTypeWithMap(_map))
    {
        std::cerr << "Error: camera not in border or is stuck in a corner" << std::endl;
        exit(EXIT_FAILURE);
    }
    _characterManager = Utils::make_unique<CharacterManager>(_camera.getPosition(), _camera.getCameraDirection(),
                                                             _windowWidth, _windowHeight, interactableObjects,
                                                             monsters, _music);
}

void Game::initPtr()
{
    _drawingProgram = Utils::make_unique<DrawingProgram>(_applicationPath, "tex3D.vs.glsl", "tex3D.fs.glsl", _camera,
                                                         _windowWidth, _windowHeight, *_textureManager, _windowManager,
                                                         _characterManager->getPlayer(),
                                                         _characterManager->getMonsters(),
                                                         _characterManager->getInteractableObjects());
    _drawingProgram->init();
    _menu = Utils::make_unique<Menu>(_windowWidth, _windowHeight, _applicationPath, _drawingProgram, _windowManager);
}

bool Game::gameWin() const
{
    return Utils::cmpff(_camera.getPosition().x, _exitPosition.x) &&
           Utils::cmpff(_camera.getPosition().z, _exitPosition.z) &&
           _characterManager->getPlayer().hasEnoughMoneyAndMonsterKilled(_nbMoneyNeededToFinishGame,
                                                                         _nbMonsterKillNeededToFinishGame);
}

void Game::loop()
{
    while (!_gameInterrupted && (!gameWin() && !_gameLost))
    {
        SDL_Event e;
        while (_windowManager.pollEvent(e))
        {
            switch (e.type)
            {
                case SDL_QUIT:_gameInterrupted = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        _characterManager->leftClick(_camera.getCameraDirection(),
                                                     _windowManager.getMousePosition(), _camera);
                    }
                    break;

                case SDL_KEYDOWN:
                    _cameraManager.moveCamera(e.button, _map, _characterManager->getMonsters(),
                                              _characterManager->getInteractableObjects(),
                                              _characterManager->getPlayer());
            }
        }

        if (_characterManager->updateMonsters(_map))
        {
            _gameLost = true;
            continue;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _drawingProgram->drawMap(_map, (int) _map[0].size(), (int) _map.size());
        _menu->drawMenuInGame(_characterManager->getPlayer());
        _windowManager.swapBuffers();
    }
}

void Game::createGame()
{
    initMap();
    initPtr();

    _music.playMenuMusic();
    _menu->drawMenuStarting(_gameInterrupted);
    _music.playSoundStartGame();
    _music.playInGameMusic();

    if (_gameLost)
    {
        _gameLost  = false;
        _retryGame = true;
    }
}

int Game::run()
{

    if (initGlew())
    {
        return EXIT_FAILURE;
    }

    if (!_music.initMusic())
    {
        return false;
    }

    createGame();

    while (!_gameInterrupted)
    {
        loop();
        if (_menu->drawMenuEnding(gameWin(), _gameLost, _gameInterrupted, _music))
        {
            createGame();
        }
    }

    _music.freeMusics();
    _textureManager->freeTextures();

    return EXIT_SUCCESS;
}


