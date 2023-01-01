#include <iostream>
#include <utility>
#include "../include/Mesh.hpp"


Mesh::Mesh(std::vector<glimac::ShapeVertex> vertices, const std::vector<GLuint> &indexes,
           std::vector<Texture> textures)
        : _vertices(std::move(vertices))
        , _indexes(indexes)
        , _textures(std::move(textures))
{
    setupMesh();
}

Mesh::Mesh(std::vector<glimac::ShapeVertex> vertices, std::vector<GLuint> indexes, const glm::vec3 &color)
        : _vertices(std::move(vertices))
        , _indexes(std::move(indexes))
        , _color(color)
{
    setupMesh();
}

void Mesh::initVBO()
{
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glimac::ShapeVertex), _vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initIBO()
{
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(GLuint), _indexes.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::initVAO()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    if (_indexes.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    }

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex),
                          (const GLvoid *) offsetof(glimac::ShapeVertex, texCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (_indexes.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Mesh::setupMesh()
{
    initVBO();
    if (_indexes.size() > 0)
    {
        initIBO();
    }
    initVAO();
}


void Mesh::draw(const glimac::Program &program)
{
    glUniform1i(glGetUniformLocation(program.getGLId(), "uIsAModel"), true);

    if (_textures.size() > 0)
    {
        glUniform1i(glGetUniformLocation(program.getGLId(), "uModelHasTexture"), true);
        for (GLuint i = 0; i < _textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glUniform1i(glGetUniformLocation(program.getGLId(), (_textures[i].type).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, _textures[i].id);
        }
    }
    else
    {
        glUniform1i(glGetUniformLocation(program.getGLId(), "uModelHasTexture"), false);
        glUniform3f(glGetUniformLocation(program.getGLId(), "uModelColor"), _color.r, _color.g, _color.b);
    }

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indexes.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Debind all textures
    for (GLuint i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}




