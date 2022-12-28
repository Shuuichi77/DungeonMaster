#include "../include/TextureManager.hpp"

#include <glimac/Image.hpp>
#include <iostream>

TextureManager::TextureManager(const glimac::FilePath &applicationPath)
        : _directory(applicationPath.dirPath() + "assets/textures" + "/")
{
    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS);

    loadTextureFromFile(WALL_TEXTURE_1, "wall_01.png");
    loadTextureFromFile(WALL_TEXTURE_2, "wall_02.png");
    loadTextureFromFile(WALL_TEXTURE_3, "wall_03.png");

    loadTextureFromFile(FLOOR_TEXTURE, "floor_01.png");
    loadTextureFromFile(EXIT_TEXTURE, "stairs.png");
}

GLuint TextureManager::getTexture(const std::string &textureName) const
{
    return _textures.at(textureName);
}

void TextureManager::freeTextures()
{
    for (auto &texture: _textures)
    {
        glDeleteTextures(1, &texture.second);
    }
}

bool TextureManager::loadTextureFromFile(const char *textureName, const char *imageFile)
{
    std::unique_ptr<glimac::Image> image = glimac::loadImage(_directory + "/" + imageFile);
    if (image == nullptr)
    {
        std::cout << "Error while loading the image from " << imageFile << std::endl;
        return false;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA,
                 GL_FLOAT, image->getPixels());
    glBindTexture(GL_TEXTURE_2D, 0);

    _textures.emplace(textureName, texture);

    return true;
}

GLuint TextureManager::getWallTexture(int numWall) const
{
    return _textures.at(_wallsTextures[numWall]);
}

void TextureManager::addRandomWallTexture()
{
    std::string textureName;
    switch (rand() % 3)
    {
        case 0: textureName = TextureManager::WALL_TEXTURE_1;
            break;
        case 1: textureName = TextureManager::WALL_TEXTURE_2;
            break;
        case 2: textureName = TextureManager::WALL_TEXTURE_3;
            break;
    }

    _wallsTextures.emplace_back(textureName);
}






