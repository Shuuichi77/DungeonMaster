#pragma once


#include "Player.hpp"
#include "ModelManager.hpp"

class TextureManager;

class Interface
{
private:
    const unsigned int   _windowWidth;
    const unsigned int   _windowHeight;
    ModelManager         &_modelManager;
    const TextureManager &_textureManager;

    Program       &_program;
    Player        &_player;
    FreeflyCamera &_camera;
    mat4          &_projMatrix;
    GLint         &_uMVPMatrix;
    GLint         &_uMVMatrix;
    GLint         &_uNormalMatrix;
    GLint         &_uTexture;
    GLuint        &_vao;

public:
    Interface(Player &player, unsigned int windowWidth, unsigned int windowHeight, ModelManager &modelManager,
              const TextureManager &textureManager, Program &program,
              FreeflyCamera &camera, mat4 &projMatrix, GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix,
              GLint &uTexture, GLuint &vao);

    void drawInterface();

    void drawInventoryBackground();
};