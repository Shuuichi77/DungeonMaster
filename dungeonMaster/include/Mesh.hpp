#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Shader.hpp>
#include <glimac/Program.hpp>
#include <assimp/color4.h>

struct Texture
{
    GLuint      id;
    std::string type;
    std::string path;
};

class Mesh
{
private:
    std::vector<glimac::ShapeVertex> _vertices;
    std::vector<GLuint>              _indexes;
    std::vector<Texture>             _textures;
    glm::vec3                        _color;

    GLuint _vbo;
    GLuint _ibo;
    GLuint _vao;

    static const GLuint VERTEX_ATTR_POSITION  = 0;
    static const GLuint VERTEX_ATTR_NORMAL    = 1;
    static const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    void initVBO();

    void initIBO();

    void initVAO();

    void setupMesh();

public:
    Mesh(std::vector<glimac::ShapeVertex> vertices, const std::vector<GLuint> &indexes,
         std::vector<Texture> textures);

    Mesh(std::vector<glimac::ShapeVertex> vertices, std::vector<GLuint> indexes,
         const glm::vec3 &color);

    void draw(const glimac::Program &program);
};