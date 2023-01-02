#include <iostream>

#include "../include/DrawingProgram.hpp"
#include "../include/TextureManager.hpp"
#include "../include/ModelType.hpp"

DrawingProgram::DrawingProgram(const FilePath &applicationPath, const std::string &vertexShader,
                               const std::string &fragmentShader, FreeflyCamera &camera, int windowWidth,
                               int windowHeight, const TextureManager &textureManager,
                               glimac::SDLWindowManager &windowManager, Player &player,
                               std::vector<std::unique_ptr<Monster>> &monsters,
                               std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
        : _program(loadProgram(applicationPath.dirPath() + "shaders/" + vertexShader,
                               applicationPath.dirPath() + "shaders/" + fragmentShader))
        , _camera(camera)
        , _windowWidth(windowWidth)
        , _windowHeight(windowHeight)
        , _textureManager(textureManager)
        , _modelManager(applicationPath, camera, monsters, interactableObjects)
        , _windowManager(windowManager)
        , _interface(player, windowWidth, windowHeight, _modelManager, _textureManager, _program, camera,
                     _projMatrix, _uMVPMatrix, _uMVMatrix, _uNormalMatrix, _uTexture, _vao)
{
    _projMatrix        = perspective(radians(70.f), (float) (windowWidth / windowHeight), 0.1f, 100.f);
    _uMVPMatrix        = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
    _uMVMatrix         = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
    _uNormalMatrix     = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
    _uTexture          = glGetUniformLocation(_program.getGLId(), "uTexture");
    _uLightPosition_vs = glGetUniformLocation(_program.getGLId(), "_uLightPosition_vs");
}

void DrawingProgram::use()
{
    _program.use();
}

void DrawingProgram::loadVaoVboForQuads()
{
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
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

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
}

void DrawingProgram::init()
{
    loadVaoVboForQuads();
    use();
}


void DrawingProgram::drawFixModel(const ModelType &modelType)
{
    drawModel(modelType, vec3(0.f), DirectionType::NEUTRAL);
}

void DrawingProgram::drawModel(const ModelType &modelType, const vec3 &position, const DirectionType &directionType)
{
    _modelManager.drawModel(modelType, position, directionType, _program, _projMatrix, _uMVPMatrix, _uMVMatrix,
                            _uNormalMatrix);
}

bool DrawingProgram::canChangeAgain()
{
    std::chrono::time_point<std::chrono::system_clock> now             = std::chrono::system_clock::now();
    std::chrono::duration<double>                      elapsed_seconds = now - _timeChanged;
    if (elapsed_seconds.count() > 0.15)
    {
        return true;
    }
    return false;
}

void DrawingProgram::changeAttributes()
{
    if (!_attributesCanChange && canChangeAgain())
    {
        _attributesCanChange = true;
    }
    bool change = false;
    if (_attributesCanChange)
    {
        if (_windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT))
        {
            vec2 mousePosition = _windowManager.getMousePosition();

            std::cout << mousePosition.x << ", " << +mousePosition.y << std::endl;
            std::cout << std::setprecision(6) <<
                    mousePosition.x / (float) _windowWidth << ", " <<
                    mousePosition.y / (float) _windowHeight << std::endl;
            std::cout << "" << std::endl;

            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
        }

        if (_windowManager.isKeyPressed(SDLK_DELETE))
        {
            _x = 4.f;
            _y = 0.25f * 0.75f;
            _z = 5.f;

            _pas_transi = 1.f;
            _tx         = 0.f;
            _ty         = 0.f;
            _tz         = 0.f;

            _rx = 0.f;
            _ry = 0.f;
            _rz = 0.f;

            _pas_scale = 1.f;
            _scaled    = 1.f;

        }
        // x
        if (_windowManager.isKeyPressed(SDLK_r))
        {
            _x++;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_f))
        {
            _x--;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // y
        if (_windowManager.isKeyPressed(SDLK_t))
        {
            _y++;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_g))
        {
            _y--;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // z
        if (_windowManager.isKeyPressed(SDLK_y))
        {
            _z++;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_h))
        {
            _z--;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // tx
        if (_windowManager.isKeyPressed(SDLK_u))
        {
            _tx += _pas_transi;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_j))
        {
            _tx -= _pas_transi;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // ty
        if (_windowManager.isKeyPressed(SDLK_i))
        {
            _ty += _pas_transi;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_k))
        {
            _ty -= _pas_transi;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // tz
        if (_windowManager.isKeyPressed(SDLK_o))
        {
            _tz += _pas_transi;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_l))
        {
            _tz -= _pas_transi;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // rx
        if (_windowManager.isKeyPressed(SDLK_w))
        {
            _rx++;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_x))
        {
            _rx--;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // ry
        if (_windowManager.isKeyPressed(SDLK_c))
        {
            _ry++;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_v))
        {
            _ry--;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // rz
        if (_windowManager.isKeyPressed(SDLK_b))
        {
            _rz++;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_n))
        {
            _rz--;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // scaled
        if (_windowManager.isKeyPressed(SDLK_m))
        {
            _scaled += _pas_scale;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_p))
        {
            if (_scaled - _pas_scale > 0)
            {
                _scaled -= _pas_scale;
            }
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // Scaled fort
        if (_windowManager.isKeyPressed(SDLK_F1))
        {
            if (_scaled - 10.f > 0)
            {
                _scaled = _scaled - 10.f;
            }
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_F2))
        {
            if (_scaled - 20.f > 0)
            {
                _scaled = _scaled - 20.f;
            }
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_F3))
        {
            if (_scaled - 30.f > 0)
            {
                _scaled = _scaled - 30.f;
            }
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // pas_transi
        if (_windowManager.isKeyPressed(SDLK_F5))
        {
            if (_pas_transi > 0.1f)
            {
                _pas_transi -= 0.1f;
            }
            else
            {
                _pas_transi -= 0.01f;
            }
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
        if (_windowManager.isKeyPressed(SDLK_F6))
        {
            if (_pas_transi - 0.1f < 0.005f)
            {
                _pas_transi += 0.01f;
            }
            else
            {
                _pas_transi += 0.1f;
            }
            _pas_transi += 0.1f;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        // pas_scale
        if (_windowManager.isKeyPressed(SDLK_F7))
        {
            if (_pas_scale > 0.1f)
            {
                _pas_scale -= 0.1f;
            }
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        if (_windowManager.isKeyPressed(SDLK_F8))
        {
            _pas_scale += 0.1f;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }


        // Scaled fort
        if (_windowManager.isKeyPressed(SDLK_F10))
        {
            _scaled              = _scaled + 10.f;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        if (_windowManager.isKeyPressed(SDLK_F11))
        {
            _scaled              = _scaled + 20.f;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }

        if (_windowManager.isKeyPressed(SDLK_F12))
        {
            _scaled              = _scaled + 30.f;
            _attributesCanChange = false;
            _timeChanged         = std::chrono::system_clock::now();
            change               = true;
        }
    }

    if (change)
    {
        std::cout << "----------------------------------" << std::endl;
        std::cout << std::setprecision(6) << "pas_transi = " << _pas_transi << std::endl;
        std::cout << std::setprecision(6) << "(x, y, z)\t\t=\t\t(" << _x << ", " << _y << ", " << _z << ")"
                << std::endl;

        std::cout << std::setprecision(6) << "(tx, ty, tz)\t=\t\t(" << _tx << ", " << _ty << ", " << _tz << ")"
                << std::endl;

        std::cout << std::setprecision(6) << "(rx, ry, rz)\t=\t\t(" << _rx << ", " << _ry << ", " << _rz << ")"
                << std::endl;

        std::cout << std::setprecision(6) << "pas_scale = " << _pas_scale << std::endl;
        std::cout << std::setprecision(6) << "scaled\t\t\t=\t\t" << _scaled << std::endl;
        std::cout << "----------------------------------" << std::endl;
    }
}

void DrawingProgram::drawModelDebug()
{
    changeAttributes();
    // -------------------------------------------------------------------------------------
    mat4 MVMMatrix = mat4(1.0f);

//     // Modèle fixe
//    MVMMatrix = translate(MVMMatrix, vec3(
//            _x + _tx,
//            _y + _ty,
//            _z + _tz
//    ) - ModelTransformations::getGlobalTranslate());

//    // Modèle fixe mais MOBILE en fait
//    MVMMatrix = translate(MVMMatrix, vec3(
//            _x + _tx,
//            _y + _ty,
//            _z + _tz
//    ) - ModelTransformations::getGlobalTranslate());
//
    // Modèle mobile
    vec3 camPos = _camera.getPosition();
    MVMMatrix = translate(MVMMatrix, vec3(
            camPos.x + _tx,
            camPos.y + _ty,
            camPos.z + _tz
    ) - ModelTransformations::getGlobalTranslate());

    MVMMatrix = rotate(MVMMatrix, radians(_rx), vec3(1, 0, 0));
    MVMMatrix = rotate(MVMMatrix, radians(_ry), vec3(0, 1, 0));
    MVMMatrix = rotate(MVMMatrix, radians(_rz), vec3(0, 0, 1));

//    vec3 scaleVec = vec3(1. / _scaled) * ModelTransformations::getGlobalScale();
//    MVMMatrix = scale(MVMMatrix, scaleVec);

    MVMMatrix = scale(MVMMatrix, vec3(1. * _scaled));
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);

    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::MENU_WIN_TEXTURE));
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

//    _modelManager.drawModelDebug(KEY_MODEL, _camera.getPosition(), _program,
//                                 _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix, _uNormalMatrix,
//                                 MVMMatrix);

}

void DrawingProgram::drawMap(const std::vector<std::vector<MapElement>> &map, int width, int height)
{
    _program.use();
    glUniform3fv(_uLightPosition_vs, 1, value_ptr(_camera.getViewMatrix() * vec4(_camera.getPosition(), 1)));
    _interface.drawInterface();
    _modelManager.drawAllModels(_program, _projMatrix, _uMVPMatrix, _uMVMatrix, _uNormalMatrix);
    drawQuads(map, width, height);
    drawModelDebug();
}

void DrawingProgram::drawQuads(const std::vector<std::vector<MapElement>> &map, int width, int height)
{
    int numWall = 0;

    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[i].size(); ++j)
        {
            if (map[i][j] == MapElement::WALL)
            {
                drawWalls(i, j, width, height, map, numWall);
            }

            else if (map[i][j] == MapElement::WATER)
            {
                drawFloorAndCeiling((float) j, 0, (float) i, TextureManager::WATER_TEXTURE);
            }

            else
            {
                drawWallAroundMapBorder((float) j, 0, (float) i, width, height, numWall);
                drawFloorAndCeiling((float) j, 0, (float) i, TextureManager::FLOOR_TEXTURE);

                if (map[i][j] == MapElement::ENTRY || map[i][j] == MapElement::EXIT)
                {
                    drawLadder((float) j, 0, (float) i);
                }
            }
        }
    }
}

void DrawingProgram::drawWallAroundMapBorder(float x, float y, float z, int width, int height, int numWall)
{
    if ((int) x == 0)
    {
        drawWall(x - 1, y, z, DirectionType::EAST, numWall);
    }

    if ((int) z == 0)
    {
        drawWall(x, y, z - 1, DirectionType::NORTH, numWall);
    }

    if ((((int) z) + 1) == height)
    {
        drawWall(x, y, z + 1, DirectionType::SOUTH, numWall);
    }

    if ((((int) x) + 1) == width)
    {
        drawWall(x + 1, y, z, DirectionType::WEST, numWall);
    }
}

void DrawingProgram::drawLadder(float x, float y, float z)
{
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::EXIT_TEXTURE));
    glUniform1i(_uTexture, 0);
    mat4 MVMMatrix = mat4(1);
    MVMMatrix = translate(MVMMatrix, vec3(x, y + 0.01, -z) - ModelTransformations::getGlobalTranslate());
    MVMMatrix = rotate(MVMMatrix, radians(90.f), vec3(1, 0, 0));
    MVMMatrix = scale(MVMMatrix, vec3(1. / 1.3) * ModelTransformations::getGlobalScale());
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    drawModel(LADDER_MODEL, vec3(x, y, -z), DirectionType::SOUTH);
}

void DrawingProgram::drawWalls(int i, int j, int width, int height, const std::vector<std::vector<MapElement>> &map,
                               int &numWall)
{
    // Check North
    if (i + 1 < height && map[i + 1][j] != MapElement::WALL)
    {
        drawWall((float) j, 0, (float) i, DirectionType::NORTH, numWall++);
    }

    // Check South
    if (i - 1 >= 0 && map[i - 1][j] != MapElement::WALL)
    {
        drawWall((float) j, 0, (float) i, DirectionType::SOUTH, numWall++);
    }
    // Check East
    if (j + 1 < width && map[i][j + 1] != MapElement::WALL)
    {
        drawWall((float) j, 0, (float) i, DirectionType::EAST, numWall++);
    }
    // Check West
    if (j - 1 >= 0 && map[i][j - 1] != MapElement::WALL)
    {
        drawWall((float) j, 0, (float) i, DirectionType::WEST, numWall++);
    }
}

void DrawingProgram::drawWall(float x, float y, float z, DirectionType wallOrientation, int numWall)
{
    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);

    glBindTexture(GL_TEXTURE_2D, _textureManager.getWallTexture(numWall));
    glUniform1i(_uTexture, 0);

    mat4 MVMMatrix = mat4(1);

    if (wallOrientation == DirectionType::NORTH)
    {
        MVMMatrix = translate(MVMMatrix, vec3(x, y, -z - 0.5f) + ModelTransformations::getGlobalTranslate());
        MVMMatrix = rotate(MVMMatrix, radians(180.f), vec3(0, 1, 0));
    }
    if (wallOrientation == DirectionType::SOUTH)
    {
        MVMMatrix = translate(MVMMatrix, vec3(x, y, -z + 0.5f) + ModelTransformations::getGlobalTranslate());
    }
    else if (wallOrientation == DirectionType::WEST)
    {
        MVMMatrix = translate(MVMMatrix, vec3(x - 0.5f, y, -z) + ModelTransformations::getGlobalTranslate());
        MVMMatrix = rotate(MVMMatrix, radians(-90.f), vec3(0, 1, 0));
    }
    else if (wallOrientation == DirectionType::EAST)
    {
        MVMMatrix = translate(MVMMatrix, vec3(x + 0.5f, y, -z) + ModelTransformations::getGlobalTranslate());
        MVMMatrix = rotate(MVMMatrix, radians(90.f), vec3(0, 1, 0));
    }

    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void DrawingProgram::drawFloorAndCeiling(float x, float y, float z, const std::string &floorTextureName)
{

    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);

    // Floor
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(floorTextureName));
    glUniform1i(_uTexture, 0);
    mat4 MVMMatrix = mat4(1);
    MVMMatrix = translate(MVMMatrix, vec3(x, y - 0.5, -z) + ModelTransformations::getGlobalTranslate());
    MVMMatrix = rotate(MVMMatrix, radians(90.f + 180.f), vec3(1, 0, 0));
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // Ceiling
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::WALL_TEXTURE_3));
    glUniform1i(_uTexture, 0);
    MVMMatrix = mat4(1);
    MVMMatrix = translate(MVMMatrix, vec3(x, y + 0.5, -z) + ModelTransformations::getGlobalTranslate());
    MVMMatrix = rotate(MVMMatrix, radians(90.f), vec3(1, 0, 0));
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void DrawingProgram::drawMenuStarting()
{
    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::MENU_START_TEXTURE));
    glUniform1i(_uTexture, 0);

    ModelTransformation modelTransformation = _modelManager.getModelTransformations().getModelTransformation(
            MENU_MODEL);

    mat4 MVMMatrix = _modelManager.applyModelTransformation(modelTransformation, _camera.getPosition());
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void DrawingProgram::drawMenuWin()
{
    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::MENU_WIN_TEXTURE));
    glUniform1i(_uTexture, 0);

    ModelTransformation modelTransformation = _modelManager.getModelTransformations().getModelTransformation(
            MENU_MODEL);

    mat4 MVMMatrix = _modelManager.applyModelTransformation(modelTransformation, _camera.getPosition());
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void DrawingProgram::drawMenuLose()
{
    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);

    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::MENU_LOSE_TEXTURE));
    glUniform1i(_uTexture, 0);

    ModelTransformation modelTransformation = _modelManager.getModelTransformations().getModelTransformation(
            MENU_MODEL);
    
    mat4 MVMMatrix = _modelManager.applyModelTransformation(modelTransformation, _camera.getPosition());
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), _projMatrix, _uMVPMatrix, _uMVMatrix,
                                _uNormalMatrix);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}




