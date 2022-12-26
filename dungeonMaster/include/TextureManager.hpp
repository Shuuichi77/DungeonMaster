#pragma one

#include <glm/glm.hpp>
#include <unordered_map>
#include "GL/glew.h"
#include <glimac/FilePath.hpp>

class TextureManager
{
public:
    explicit TextureManager(const glimac::FilePath &applicationPath);

    ~TextureManager() = default;

    GLuint getTexture(const std::string &textureName) const;

    void freeTextures();

private:
    std::unordered_map<std::string, GLuint> _textures;
    std::string                             _directory;

    bool loadTextureFromFile(const char *textureName, const char *imageFile);

    static constexpr const char *WALL_TEXTURE_NAME  = "wall";
    static constexpr const char *FLOOR_TEXTURE_NAME = "floor";

    friend class DrawingProgram;
};