#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "../include/DrawingProgram.hpp"
#include "../include/TextureManager.hpp"

DrawingProgram::DrawingProgram(const glimac::FilePath &applicationPath, const std::string &vertexShader,
                               const std::string &fragmentShader, FreeflyCamera &camera, float width,
                               float height, const TextureManager &textureManager, const ModelManager &modelManager)
        :
        _program(loadProgram(applicationPath.dirPath() + "shaders/" + vertexShader,
                             applicationPath.dirPath() + "shaders/" + fragmentShader))
        , _camera(camera)
        , _textureManager(textureManager)
        , _modelManager(modelManager)
{
    _projMatrix        = glm::perspective(glm::radians(70.f), width / height, 0.1f, 100.f);
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

void DrawingProgram::setUniformMatrix(glm::mat4 MVMMatrix)
{
    MVMMatrix = _camera.getViewMatrix() * MVMMatrix;
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(_projMatrix * MVMMatrix));
    glUniformMatrix4fv(_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMMatrix));
    glUniformMatrix4fv(_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMMatrix))));
}

void DrawingProgram::drawMap(const std::vector<std::vector<ObjectType>> &map, int width, int height)
{
    glUniform3fv(_uLightPosition_vs, 1, glm::value_ptr(_camera.getViewMatrix() * glm::vec4(_camera.getPosition(), 1)));

    // Draw quads
    drawQuads(map, width, height);

    // Draw models
    drawSword();

    float x = _camera.getPosition().x;
    float y = _camera.getPosition().y;
    float z = _camera.getPosition().z;

    drawChest(x, y, z + 2);
}

void DrawingProgram::drawModel(const std::string &modelName)
{
    try
    {
        _modelManager.getModel(modelName).draw(_program);
    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelName << " not found" << std::endl;
    }
}

void DrawingProgram::drawChest(float x, float y, float z)
{
    glm::mat4 MVMMatrix = glm::mat4(1);
    float     scale     = 100.f;
    MVMMatrix = glm::scale(MVMMatrix, glm::vec3(1. / scale));

    MVMMatrix = glm::translate(MVMMatrix, glm::vec3(
            x * scale,
            y * scale,
            z * scale)
    );

//    MVMMatrix = glm::rotate(MVMMatrix, glm::radians(-60.f), glm::vec3(1, 0, 0));
    setUniformMatrix(MVMMatrix);
    drawModel(ModelManager::CHEST_MODEL);
}

void DrawingProgram::drawSword()
{
    float x  = _camera.getPosition().x;
    float y  = _camera.getPosition().y;
    float z  = _camera.getPosition().z;
    float tx = 80.f;
    float ty = 100.f;
    float tz = 30.f;

    glm::mat4 MVMMatrix = glm::mat4(1);
    float     scale     = 800.f;
    MVMMatrix = glm::scale(MVMMatrix, glm::vec3(1. / scale));

    switch (_camera.getCameraDirection())
    {
        case DirectionType::NORTH: //
            MVMMatrix = glm::translate(MVMMatrix, glm::vec3(
                    x * scale + tx,
                    y * scale - ty,
                    z * scale - tz));
            MVMMatrix = glm::rotate(MVMMatrix, glm::radians(180.f), glm::vec3(0, 1, 0));
            break;
        case DirectionType::EAST: //
            MVMMatrix = glm::translate(MVMMatrix, glm::vec3(
                    x * scale + tz,
                    y * scale - ty,
                    z * scale + tx));
            MVMMatrix = glm::rotate(MVMMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));
            break;
        case DirectionType::SOUTH:
            MVMMatrix = glm::translate(MVMMatrix, glm::vec3(
                    x * scale - tx,
                    y * scale - ty,
                    z * scale + tz));
            break;
        case DirectionType::WEST: //
            MVMMatrix = glm::translate(MVMMatrix, glm::vec3(
                    x * scale - tz,
                    y * scale - ty,
                    z * scale - tx));
            MVMMatrix = glm::rotate(MVMMatrix, glm::radians(270.f), glm::vec3(0, 1, 0));
            break;
    }

    MVMMatrix = glm::rotate(MVMMatrix, glm::radians(-60.f), glm::vec3(1, 0, 0));
    MVMMatrix = glm::rotate(MVMMatrix, glm::radians(50.f), glm::vec3(0, 0, 1));

    setUniformMatrix(MVMMatrix);
    drawModel(ModelManager::SWORD_MODEL);
}

void DrawingProgram::drawQuads(const std::vector<std::vector<ObjectType>> &map, int width, int height)
{
    int numWall = 0;

    glUniform1i(glGetUniformLocation(_program.getGLId(), "uIsAModel"), false);
    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[i].size(); ++j)
        {
            if (map[i][j] == ObjectType::WALL)
            {
                // Check North
                if (i + 1 < height && map[i + 1][j] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::NORTH, numWall++);
                }

                // Check South
                if (i - 1 > 0 && map[i - 1][j] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::SOUTH, numWall++);
                }
                // Check East
                if (j + 1 < width && map[i][j + 1] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::EAST, numWall++);
                }
                // Check West
                if (j - 1 > 0 && map[i][j - 1] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::WEST, numWall++);
                }
            }

            else
            {
                drawFloorAndCeiling((float) j, 0, (float) i);

                if (map[i][j] == ObjectType::EXIT)
                {
                    drawExit((float) j, 0, (float) i);
                }
            }
        }
    }
}

void DrawingProgram::drawWall(float x, float y, float z, DirectionType wallOrientation, int numWall)
{
    glBindTexture(GL_TEXTURE_2D, _textureManager.getWallTexture(numWall));
    glUniform1i(_uTexture, 0);

    glm::mat4 MVMMatrix = glm::mat4(1);

    if (wallOrientation == DirectionType::NORTH)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y, -z - 0.5f));
        MVMMatrix = glm::rotate(MVMMatrix, glm::radians(180.f), glm::vec3(0, 1, 0));
    }
    if (wallOrientation == DirectionType::SOUTH)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y, -z + 0.5f));
    }
    else if (wallOrientation == DirectionType::WEST)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x - 0.5f, y, -z));
        MVMMatrix = glm::rotate(MVMMatrix, glm::radians(-90.f), glm::vec3(0, 1, 0));
    }
    else if (wallOrientation == DirectionType::EAST)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x + 0.5f, y, -z));
        MVMMatrix = glm::rotate(MVMMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));
    }

    setUniformMatrix(MVMMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawingProgram::drawFloorAndCeiling(float x, float y, float z)
{
    // Floor
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::FLOOR_TEXTURE));
    glUniform1i(_uTexture, 0);

    glm::mat4 MVMMatrix = glm::mat4(1);
    MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y - 0.5, -z));
    MVMMatrix = glm::rotate(MVMMatrix, glm::radians(90.f + 180.f), glm::vec3(1, 0, 0));

    setUniformMatrix(MVMMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Ceiling
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::WALL_TEXTURE_3));
    glUniform1i(_uTexture, 0);

    MVMMatrix = glm::mat4(1);
    MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y + 0.5, -z));
    MVMMatrix = glm::rotate(MVMMatrix, glm::radians(90.f), glm::vec3(1, 0, 0));

    setUniformMatrix(MVMMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawingProgram::drawExit(float x, float y, float z)
{
    // Exit
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::EXIT_TEXTURE));
    glUniform1i(_uTexture, 0);

    glm::mat4 MVMMatrix = glm::mat4(1);
    MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y, -z - 0.5));

    setUniformMatrix(MVMMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}





