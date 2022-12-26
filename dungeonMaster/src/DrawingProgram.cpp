#include <iostream>
#include "../include/DrawingProgram.hpp"

#include "../include/TextureManager.hpp"

DrawingProgram::DrawingProgram(const glimac::FilePath &applicationPath, const std::string &vertexShader,
                               const std::string &fragmentShader, FreeflyCamera &camera, float width,
                               float height, const TextureManager &textureManager)
        :
        _program(loadProgram(applicationPath.dirPath() + "shaders/" + vertexShader,
                             applicationPath.dirPath() + "shaders/" + fragmentShader))
        , _camera(camera)
        , _textureManager(textureManager)
{
    _projMatrix    = glm::perspective(glm::radians(70.f), width / height, 0.1f, 100.f);
    _uMVPMatrix    = glGetUniformLocation(_program.getGLId(), "uMVPMatrix");
    _uMVMatrix     = glGetUniformLocation(_program.getGLId(), "uMVMatrix");
    _uNormalMatrix = glGetUniformLocation(_program.getGLId(), "uNormalMatrix");
    _uTexture      = glGetUniformLocation(_program.getGLId(), "uTexture");
}

void DrawingProgram::use()
{
    _program.use();
}

void DrawingProgram::drawMap(const std::vector<std::vector<ObjectType>> &map, int width, int height)
{
    for (int i = 0; i < map.size(); ++i)
    {
        for (int j = 0; j < map[i].size(); ++j)
        {
            if (map[i][j] == ObjectType::WALL)
            {
                // Check North
                if (i + 1 < height && map[i + 1][j] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::NORTH);
                }

                // Check South
                if (i - 1 > 0 && map[i - 1][j] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::SOUTH);
                }
                // Check East
                if (j + 1 < width && map[i][j + 1] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::EAST);
                }
                // Check West
                if (j - 1 > 0 && map[i][j - 1] != ObjectType::WALL)
                {
                    drawWall((float) j, 0, (float) i, DirectionType::WEST);
                }
            }
            else if (map[i][j] == ObjectType::EMPTY)
            {
                drawFloor((float) j, 0, (float) i);
            }
        }
    }
}

void DrawingProgram::setUniformMatrix(glm::mat4 MVMMatrix)
{
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(_projMatrix * MVMMatrix));
    glUniformMatrix4fv(_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMMatrix));
    glUniformMatrix4fv(_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMMatrix))));
}


void DrawingProgram::drawWall(float x, float y, float z, DirectionType wallOrientation)
{
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::WALL_TEXTURE_NAME));
    glUniform1i(_uTexture, 0);

    glm::mat4 MVMMatrix = glm::mat4(1);

    if (wallOrientation == DirectionType::NORTH)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y, -z - 0.5f));
    }
    if (wallOrientation == DirectionType::SOUTH)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y, -z + 0.5f));
    }
    else if (wallOrientation == DirectionType::WEST)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x - 0.5f, y, -z));
        MVMMatrix = glm::rotate(MVMMatrix, glm::radians(90.f), glm::vec3(0, 1, 0));
    }
    else if (wallOrientation == DirectionType::EAST)
    {
        MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x + 0.5f, y, -z));
        MVMMatrix = glm::rotate(MVMMatrix, glm::radians(-90.f), glm::vec3(0, 1, 0));
    }

    MVMMatrix = _camera.getViewMatrix() * MVMMatrix;

    setUniformMatrix(MVMMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void DrawingProgram::drawFloor(float x, float y, float z)
{
    glBindTexture(GL_TEXTURE_2D, _textureManager.getTexture(TextureManager::FLOOR_TEXTURE_NAME));
    glUniform1i(_uTexture, 0);

    glm::mat4 MVMMatrix = glm::mat4(1);

    MVMMatrix = glm::translate(MVMMatrix, glm::vec3(x, y - 0.5, -z));
    MVMMatrix = glm::rotate(MVMMatrix, glm::radians(90.f), glm::vec3(1, 0, 0));
    MVMMatrix = _camera.getViewMatrix() * MVMMatrix;

    setUniformMatrix(MVMMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}





