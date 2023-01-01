#include "../include/Game.hpp"
#include "../include/Utils.hpp"

#include <SDL/SDL_ttf.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <iostream>
#include <glimac/common.hpp>
#include <utility>


Game::Game(glimac::FilePath filePath, unsigned int windowHeight)
        :
        _camera()
        , _applicationPath(std::move(filePath))
        , _windowWidth(windowHeight * 4 / 3)
        , _windowHeight(windowHeight)
        , _windowManager(windowHeight * 4 / 3, windowHeight, "Dungeon Master")
        , _cameraManager(_camera, _windowManager, _gameWin) {}

int Game::initGlew()
{
    srand(time(nullptr));

    // Initialize glew for OpenGL3+ support
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

void Game::initMap()
{
    _textureManager = Utils::make_unique<TextureManager>(_applicationPath);


    // TODO: Read files to add ennemies

    // TODO: Camera direction en fonction d'ENTRY
    DirectionType startingDir = DirectionType::NORTH;
    _camera.setCameraDirection(startingDir);

    _map = {
            { WALL, EMPTY, ENTRY, EMPTY, WALL,  WALL },
            { WALL, WALL,  EMPTY, WALL,  EMPTY, WALL },
            { WALL, WALL,  EMPTY, EMPTY, EMPTY, WALL },
            { WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
            { WALL, WALL,  EMPTY, EMPTY, EMPTY, WALL },
            { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
            { WALL, EMPTY, WALL,  WALL,  EMPTY, WALL },
            { WALL, WALL,  WALL,  WALL,  EXIT,  WALL },
    };

    int      nbMaxWall = _map.size() * _map.size();
    for (int i         = 0; i < nbMaxWall; ++i)
    {
        _textureManager->addRandomWallTexture();
    }
    for (int i         = 0; i < _map.size(); ++i)
    {
        for (int j = 0; j < _map[i].size(); ++j)
        {
            if (_map[i][j] == ENTRY)
            {
                _camera.setPosition(vec3(j, 0.25f, i));
                break;
            }
        }
    }

    _characterManager = Utils::make_unique<CharacterManager>(_camera.getPosition(), _camera.getCameraDirection(),
                                                             _windowWidth,
                                                             _windowHeight);

    _characterManager->addMonster(Utils::make_unique<Monster>(MonsterType::ARMOGOHMA,
                                                              vec3(3, 0, -2),
                                                              DirectionType::WEST));

    _characterManager->addMonster(Utils::make_unique<Monster>(MonsterType::DARKRAI,
                                                              vec3(4, 0, -5),
                                                              DirectionType::SOUTH));

    _characterManager->addMonster(Utils::make_unique<Monster>(MonsterType::KING_BOO,
                                                              vec3(2, 0, -5),
                                                              DirectionType::SOUTH));

    _characterManager->addInteractableObject(
            Utils::make_unique<InteractableObject>(InteractableObjectType::INTERACTABLE_CHEST_KEY,
                                                   vec3(1, 0, -3),
                                                   DirectionType::EAST));

//    _characterManager->addInteractableObject(
//            Utils::make_unique<InteractableObject>(InteractableObjectType::INTERACTABLE_CHEST_WEAPON_02,
//                                                   vec3(2, 0, -3),
//                                                   DirectionType::NORTH));

    _characterManager->addInteractableObject(
            Utils::make_unique<InteractableObject>(InteractableObjectType::INTERACTABLE_CHEST_FAIRY,
                                                   vec3(3, 0, -3),
                                                   DirectionType::SOUTH));

    _characterManager->addInteractableObject(
            Utils::make_unique<InteractableObject>(InteractableObjectType::INTERACTABLE_CHEST_WEAPON_03,
                                                   vec3(3, 0, -4),
                                                   DirectionType::WEST));

    _characterManager->addInteractableObject(
            Utils::make_unique<InteractableObject>(InteractableObjectType::INTERACTABLE_DOOR,
                                                   vec3(4, 0, -6),
                                                   DirectionType::SOUTH));
}

void Game::initPtr()
{
    _drawingProgram = Utils::make_unique<DrawingProgram>(_applicationPath, "tex3D.vs.glsl", "tex3D.fs.glsl", _camera,
                                                         _windowWidth, _windowHeight, *_textureManager, _windowManager,
                                                         _characterManager->getPlayer(),
                                                         _characterManager->getMonsters(),
                                                         _characterManager->getInteractableObjects());
    _drawingProgram->init();
    std::cout << "Ptr initialized" << std::endl;
}

void Game::updatePlayer()
{
    // TODO: _characterManager.updatePlayer();
    _drawingProgram->updatePlayer(_characterManager->getPlayer());
}

void Game::loop()
{
    while (!_gameWin && !_gamelLost)
    {
        SDL_Event e;
        while (_windowManager.pollEvent(e))
        {
            switch (e.type)
            {
                case SDL_QUIT:_gameWin = true;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_LEFT)
                    {
                        if (_characterManager->leftClick(_camera.getPosition(), _camera.getCameraDirection(),
                                                         _windowManager.getMousePosition()))
                        {
                            updatePlayer();
                        }
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
            std::cout << "LOST" << std::endl;
            _gamelLost = true;
            continue;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _drawingProgram->drawMap(_map, (int) _map[0].size(), (int) _map.size());
        _windowManager.swapBuffers();
    }
}

int Game::run()
{
    if (initGlew() == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    initMap();
    initPtr();
    loop();

    // TODO: menu.displayEndingScreen(_gamelLost, _gameWin);

    _textureManager->freeTextures();

    return EXIT_SUCCESS;
}


