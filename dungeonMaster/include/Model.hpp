#pragma once

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "Mesh.hpp"

using namespace std;

GLint textureFromFile(const char *path, string directory);

class Model
{
private:
    vector<Mesh>    _meshes;
    string          _directory;
    vector<Texture> _textures_loaded;

    void loadModel(string path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

public:
    explicit Model(std::string path);

    void draw(const glimac::Program &program);

    size_t getMeshesSize() const { return _meshes.size(); }
};

/*
/home/johnson/CLionProjects/DungeonMaster/dungeonMaster/assets/models/dungeon-stairs/source/textures/Stair Rails A.png
/home/johnson/CLionProjects/DungeonMaster/dungeonMaster/assets/models/dungeon-stairs/source/textures/Stair Rails A.png


/home/johnson/CLionProjects/DungeonMaster/dungeonMaster/assets/models/dungeon-stairs/source/Stair_Rails_A.png
 */