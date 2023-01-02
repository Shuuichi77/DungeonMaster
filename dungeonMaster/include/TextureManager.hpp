#pragma one

#include <glm/glm.hpp>
#include <unordered_map>
#include "GL/glew.h"
#include <glimac/FilePath.hpp>
#include <vector>

class TextureManager
{
private:
    std::unordered_map<std::string, GLuint> _textures;
    std::string                             _directory;
    std::vector<std::string>                _wallsTextures;

    bool loadTextureFromFile(const char *textureName, const char *imageFile);

    static constexpr const char *WALL_TEXTURE_1     = "wall_1";
    static constexpr const char *WALL_TEXTURE_2     = "wall_2";
    static constexpr const char *WALL_TEXTURE_3     = "wall_3";
    static constexpr const char *FLOOR_TEXTURE      = "floor";
    static constexpr const char *EXIT_TEXTURE       = "exit";
    static constexpr const char *INVENTORY_TEXTURE  = "inventory";
    static constexpr const char *WATER_TEXTURE      = "water";
    static constexpr const char *MENU_START_TEXTURE = "startingMenu";
    static constexpr const char *MENU_LOSE_TEXTURE  = "loseMenu";
    static constexpr const char *MENU_WIN_TEXTURE   = "winMenu";

    friend class DrawingProgram;

    friend class Interface;

public:
    explicit TextureManager(const glimac::FilePath &applicationPath);

    ~TextureManager() = default;

    void addRandomWallTexture();

    GLuint getWallTexture(int numWall) const;

    GLuint getTexture(const std::string &textureName) const;

    void freeTextures();
};