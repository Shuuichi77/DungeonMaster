#pragma once

#include <unordered_map>
#include <memory.h>

#include "FreeflyCamera.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Monster.hpp"
#include "DrawUtils.hpp"
#include "ModelTransformations.hpp"
#include "InteractableObject.hpp"

using namespace glm;
using namespace glimac;

class ModelManager
{
private:
    std::string                                      _directory;
    std::unordered_map<ModelType, Model>             _models;
    std::vector<std::unique_ptr<Monster>>            &_monstersToDraw;
    std::vector<std::unique_ptr<InteractableObject>> &_interactableObjectsToDraw; // Chests, Doors
    const FreeflyCamera                              &_camera;
    ModelTransformations                             _modelTransformations;

    ModelTransformations getModelTransformations() const { return _modelTransformations; }

    bool loadModelFromFile(const std::string &path, const ModelType &modelType);

    static mat4 transformMobileModel(mat4 &MVMMatrix, const vec3 &position,
                                     const ModelTransformation &modelTransformation);

    mat4 transformFixModel(mat4 &MVMMatrix, const ModelTransformation &modelTransformation);

    mat4 applyModelTransformation(const ModelTransformation &modelTransformation, const vec3 &position);

    void drawModelFromModelTransformation(Model model, const ModelTransformation &modelTransformation,
                                          const vec3 &position, const glimac::Program &program, const mat4 &projMatrix,
                                          GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix);

    void drawDoor(const vec3 &position, const DirectionType &directionType, const glimac::Program &program,
                  const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                  GLint uNormalMatrix);

    // For Interface
    void drawFixModel(const ModelType &modelType, const glimac::Program &program, const mat4 &projMatrix,
                      GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix);

    // For Interface
    void drawMultipleFixModels(const ModelType &modelType, const vec3 &position, const Program &program,
                               const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix,
                               float space,
                               unsigned int qty);

    // For Interface
    void drawInventory(const std::vector<ItemType> &items, const std::vector<WeaponType> &weaponsTypes,
                       const glimac::Program &program, const mat4 &projMatrix, GLint uMVPMatrix,
                       GLint uMVMatrix, GLint uNormalMatrix);

    friend class Interface;

public:
    explicit ModelManager(const glimac::FilePath &applicationPath, const FreeflyCamera &camera,
                          std::vector<std::unique_ptr<Monster>> &monstersToDraw,
                          std::vector<std::unique_ptr<InteractableObject>> &interactableObjectsToDraw);

    ~ModelManager() = default;

    void drawAllModels(const glimac::Program &program, const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                       GLint uNormalMatrix);


    void drawModel(const ModelType &modelType, const vec3 &position, const DirectionType &directionType,
                   const glimac::Program &program, const mat4 &projMatrix, GLint uMVPMatrix,
                   GLint uMVMatrix, GLint uNormalMatrix);


    void drawModelDebug(const ModelType &modelType, const vec3 &position, const glimac::Program &program,
                        const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                        GLint uNormalMatrix, const mat4 &MVMMatrix);
};