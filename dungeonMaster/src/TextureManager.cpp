#include "../include/TextureManager.hpp"

#include <glimac/Image.hpp>
#include <iostream>

TextureManager::TextureManager(const glimac::FilePath &applicationPath)
        : _directory(applicationPath.dirPath() + "assets/textures" + "/")
{
    glEnable(GL_DEPTH_TEST);

    loadTextureFromFile(WALL_TEXTURE_NAME, "wall.jpg");
    loadTextureFromFile(FLOOR_TEXTURE_NAME, "floor.png");
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





