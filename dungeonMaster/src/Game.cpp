#include "../include/Game.hpp"

#include <glm/glm.hpp>
#include <algorithm>
#include <iostream>
#include <glimac/common.hpp>
#include <utility>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

Game::Game(glimac::FilePath filePath, float windowWidth, float windowHeight)
        :
        _camera()
        , _filePath(std::move(filePath))
        , _windowWidth(windowWidth)
        , _windowHeight(windowHeight)
        , _windowManager(windowWidth, windowHeight, "Dungeon Master")
        , _cameraManager(_camera, _windowManager, _map, &_done) {}


void Game::createMap()
{
    DirectionType startingDir = DirectionType::NORTH;
    _camera.setCameraDirection(startingDir);

    // Faire en sorte qu'en lisant la map, si un mur est entouré d'autres murs, on ne le met pas dans le tableau
    _map = {
            { WALL, WALL,  ENTRY, WALL,  WALL,  WALL },
            { WALL, WALL,  EMPTY, WALL,  EMPTY, WALL },
            { WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
            { WALL, WALL,  EMPTY, WALL,  EMPTY, WALL,  WALL },
            { WALL, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WALL },
            { WALL, EMPTY, WALL,  WALL,  EMPTY, WALL },
            { WALL, WALL,  WALL,  WALL,  EXIT,  WALL },
    };

    int nbMaxWall = _map.size() * _map.size();

    for (int i = 0; i < nbMaxWall; ++i)
    {
        _textureManager->addRandomWallTexture();
    }

    for (int i = 0; i < _map.size(); ++i)
    {
        for (int j = 0; j < _map[i].size(); ++j)
        {
            if (_map[i][j] == ENTRY)
            {
                _camera.setPosition(vec3(j, 0, i));
            }
        }
    }
}

int Game::run()
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

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    ShapeVertex vertices[] = {{ vec3(0.5f, 0.5f, 0.0f),   vec3(0.0f, 0.0f, 1.f), vec2(1.0f, 0.0f) },
                              { vec3(0.5f, -0.5f, 0.0f),  vec3(0.0f, 0.0f, 1.f), vec2(1.0f, 1.0f) },
                              { vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.f), vec2(0.0f, 1.0f) },

                              { vec3(0.5f, 0.5f, 0.0f),   vec3(0.0f, 0.0f, 1.f), vec2(1.0f, 0.0f) },
                              { vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.f), vec2(0.0f, 1.0f) },
                              { vec3(-0.5f, 0.5f, 0.0f),  vec3(0.0f, 0.0f, 1.f), vec2(0.0f, 0.0f) }
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(ShapeVertex) * 6, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // -------- VAO --------
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION  = 0;
    const GLuint VERTEX_ATTR_NORMAL    = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                          (const GLvoid *) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                          (const GLvoid *) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),
                          (const GLvoid *) offsetof(ShapeVertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _textureManager = make_unique<TextureManager>(_filePath);
    _modelManager   = make_unique<ModelManager>(_filePath);
    _drawingProgram = make_unique<DrawingProgram>(_filePath, "tex3D.vs.glsl", "tex3D.fs.glsl", _camera, _windowWidth,
                                                  _windowHeight, *_textureManager, *_modelManager);
    _drawingProgram->use();


    createMap();

    while (!_done)
    {
        _cameraManager.moveCamera();

        // Event loop:
        SDL_Event e;
        while (_windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                _done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao);

        // First Wall
        _drawingProgram->drawMap(_map, _map[0].size(), _map.size());

        glBindVertexArray(0);
        _windowManager.swapBuffers();
    }

    _textureManager->freeTextures();

    return EXIT_SUCCESS;
}

void Game::exitGame()
{
    _done = true;
}
