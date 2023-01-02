#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>

#include <chrono>
#include <vector>

#include "DirectionType.hpp"
#include "FreeflyCamera.hpp"
#include "MapElement.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "ModelManager.hpp"
#include "Interface.hpp"
#include "Text.hpp"

using namespace glm;
using namespace glimac;


class DrawingProgram
{
private:
    const TextureManager &_textureManager;
    ModelManager         _modelManager;
    Interface            _interface;
    glimac::Program      _program;
    FreeflyCamera        &_camera;
    unsigned int         _windowWidth;
    unsigned int         _windowHeight;

    GLuint _vao;
    mat4   _projMatrix;
    GLint  _uMVPMatrix;
    GLint  _uMVMatrix;
    GLint  _uNormalMatrix;
    GLint  _uTexture;
    GLint  _uLightPosition_vs;

    bool                                               _attributesCanChange = true;
    std::chrono::time_point<std::chrono::system_clock> _timeChanged         = std::chrono::system_clock::now();

    void loadVaoVboForQuads();

    void use();

    void drawModel(const ModelType &modelType, const vec3 &position, const DirectionType &directionType);

    void drawFixModel(const ModelType &modelType);

    void drawQuads(const std::vector<std::vector<MapElement>> &map, int width, int height);

    void drawWalls(int i, int j, int width, int height, const std::vector<std::vector<MapElement>> &map,
                   int &numWall);

    void drawWall(float x, float y, float z, DirectionType wallOrientation, int nbWall);

    void drawFloorAndCeiling(float x, float y, float z, const std::string &floorTextureName);

    void drawWallAroundMapBorder(float x, float y, float z, int width, int height, int numWall);

    void drawLadder(float x, float y, float z);

    void programUse() { _program.use(); }

    friend class Menu;

    // ------------------------------ Debug ------------------------------
    float _x = 4.f;
    float _y = 0.f;
    float _z = 4.f;

    float _pas_transi = 1.f;
    float _tx         = 0.f;
    float _ty         = 0.f;
    float _tz         = 0.f;

    float _rx = 0.f;
    float _ry = 0.f;
    float _rz = 0.f;

    float _pas_scale = 1.f;
    float _scaled    = 1.f;

    glimac::SDLWindowManager &_windowManager;

    bool canChangeAgain();

    void changeAttributes();

    void drawModelDebug();
    // ------------------------------ Debug ------------------------------

public:
    explicit DrawingProgram(const FilePath &applicationPath, const std::string &vertexShader,
                            const std::string &fragmentShader, FreeflyCamera &camera, int windowWidth,
                            int windowHeight, const TextureManager &textureManager,
                            glimac::SDLWindowManager &windowManager, Player &player,
                            std::vector<std::unique_ptr<Monster>> &monsters,
                            std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    ~DrawingProgram() = default;

    void init();

    void drawMap(const std::vector<std::vector<MapElement>> &map, int width, int height);

    void drawMenuStarting();

    void drawMenuWin();

    void drawMenuLose();
};
