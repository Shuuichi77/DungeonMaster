#include "../include/Model.hpp"
#include "../../glimac/src/stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

GLint textureFromFile(const char *path, string directory)
{
    string pathString = string(path);
    std::replace(pathString.begin(), pathString.end(), '\\', '/');
    std::replace(pathString.begin(), pathString.end(), ' ', '_');

    string filename      = directory + '/' + pathString;
    GLuint textureID;
    glGenTextures(1, &textureID);

    int           width, height, nrComponents;
    unsigned char *image = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (image)
    {
        GLenum format;
        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filename << std::endl;
        std::cout << "directory: " << directory << std::endl;
        std::cout << "pathString: " << pathString << std::endl;
        stbi_image_free(image);
    }

    return textureID;
}

Model::Model(std::string path)
{
    this->loadModel(path);
}

void Model::draw(const glimac::Program &program)
{
    for (GLuint i = 0; i < _meshes.size(); i++)
    {
        _meshes[i].draw(program);
    }
}

void Model::loadModel(string path)
{
    Assimp::Importer importer;
    const aiScene    *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }

    _directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh, scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<glimac::ShapeVertex> vertices;
    vector<GLuint>              indices;
    vector<Texture>             textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        glimac::ShapeVertex vertex;
        glm::vec3           vector;

        vector.x        = mesh->mVertices[i].x;
        vector.y        = mesh->mVertices[i].y;
        vector.z        = mesh->mVertices[i].z;
        vertex.position = vector;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x            = mesh->mTextureCoords[0][i].x;
            vec.y            = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
        {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }

        vector.x      = mesh->mNormals[i].x;
        vector.y      = mesh->mNormals[i].y;
        vector.z      = mesh->mNormals[i].z;
        vertex.normal = vector;

        vertices.push_back(vertex);
    }

    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace      face = mesh->mFaces[i];
        for (GLuint j    = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "uModelTexture");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            // return a mesh object created from the extracted mesh data
            return Mesh(vertices, indices, textures);
        }
        else
        {
            aiColor4D color(0.0f, 0.0f, 0.0f, 0.0f);

            if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
            {
                return Mesh { vertices, indices, glm::vec3(color.r, color.g, color.b) };
            }
            else
            {
                std::cout << "NO COLOR NOR TEXTURES ??" << std::endl;
                return Mesh { vertices, indices, glm::vec3(0.0f, 0.0f, 0.0f) };
            }
        }
    }
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for (GLuint     i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        GLboolean   skip = false;
        for (GLuint j    = 0; j < _textures_loaded.size(); j++)
        {
            if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(_textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id   = textureFromFile(str.C_Str(), _directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            _textures_loaded.push_back(texture);
        }
    }
    return textures;
}
