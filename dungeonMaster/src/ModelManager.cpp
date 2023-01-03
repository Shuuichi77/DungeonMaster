#include "../include/ModelManager.hpp"
#include "../include/ModelType.hpp"


ModelManager::ModelManager(const glimac::FilePath &applicationPath, const FreeflyCamera &camera,
                           std::vector<std::unique_ptr<Monster>> &monstersToDraw,
                           std::vector<std::unique_ptr<InteractableObject>> &interactableObjectsToDraw)
        : _directory(applicationPath.dirPath() + "/assets/models")
        , _camera(camera)
        , _modelTransformations()
        , _monstersToDraw(monstersToDraw)
        , _interactableObjectsToDraw(interactableObjectsToDraw)
{
    loadModelFromFile(_directory + "/Armogohma/Armogohma.dae", MONSTER_01_MODEL);
    loadModelFromFile(_directory + "/KingBoo/KingBoo.dae", MONSTER_02_MODEL);
    loadModelFromFile(_directory + "/Darkrai/Darkrai.obj", MONSTER_03_MODEL);
    loadModelFromFile(_directory + "/MonstersAttack/MonstersAttack.fbx", MONSTERS_ATTACK_MODEL);
    loadModelFromFile(_directory + "/Sword01/Sword01.dae", WOODEN_SWORD_MODEL);
    loadModelFromFile(_directory + "/Sword02/Sword02.dae", ROYAL_SWORD_MODEL);
    loadModelFromFile(_directory + "/Sword03/Sword03.dae", MASTER_SWORD_MODEL);
    loadModelFromFile(_directory + "/Health/Health.dae", HEALTH_MODEL);
    loadModelFromFile(_directory + "/Stairs/Stairs.obj", LADDER_MODEL);
    loadModelFromFile(_directory + "/Chest/Chest.obj", CHEST_MODEL);
    loadModelFromFile(_directory + "/Money/Money.dae", MONEY_MODEL);
    loadModelFromFile(_directory + "/Door/Door.obj", DOOR_MODEL);
    loadModelFromFile(_directory + "/Milk/Milk.obj", MILK_MODEL);
    loadModelFromFile(_directory + "/HealthPotion/HealthPotion.obj", HEALTH_POTION_MODEL);
    loadModelFromFile(_directory + "/Fairy/Fairy.fbx", FAIRY_MODEL);
    loadModelFromFile(_directory + "/Key/Key.dae", KEY_MODEL);
}

bool ModelManager::loadModelFromFile(const std::string &path, const ModelType &modelType)
{
    Model model(path);

    if (model.getMeshesSize() == 0)
    {
        return false;
    }

    _models.emplace(modelType, model);
    return true;
}

mat4 ModelManager::transformMobileModel(mat4 &MVMMatrix, const vec3 &position,
                                        const ModelTransformation &modelTransformation)
{
    MVMMatrix = translate(MVMMatrix, vec3(
            position.x + modelTransformation.translation.x,
            position.y + modelTransformation.translation.y,
            position.z + modelTransformation.translation.z));

    MVMMatrix = rotate(MVMMatrix, radians(modelTransformation.rotation.x), vec3(1, 0, 0));
    MVMMatrix = rotate(MVMMatrix, radians(modelTransformation.rotation.y), vec3(0, 1, 0));
    MVMMatrix = rotate(MVMMatrix, radians(modelTransformation.rotation.z), vec3(0, 0, 1));

    MVMMatrix = scale(MVMMatrix, vec3(modelTransformation.scale.x,
                                      modelTransformation.scale.y,
                                      modelTransformation.scale.z));

    return MVMMatrix;
}

mat4 ModelManager::transformFixModel(const FreeflyCamera &camera, mat4 &MVMMatrix,
                                     const ModelTransformation &modelTransformation)
{
    const vec3 &camPos = camera.getPosition();
    switch (camera.getCameraDirection())
    {
        case DirectionType::NORTH:
            MVMMatrix = translate(MVMMatrix, vec3(
                    camPos.x + modelTransformation.translation.x,
                    camPos.y + modelTransformation.translation.y,
                    camPos.z + modelTransformation.translation.z));
            break;

        case DirectionType::EAST:
            MVMMatrix = translate(MVMMatrix, vec3(
                    camPos.x - modelTransformation.translation.z,
                    camPos.y + modelTransformation.translation.y,
                    camPos.z + modelTransformation.translation.x));
            MVMMatrix = rotate(MVMMatrix, radians(-90.f), vec3(0, 1, 0));
            break;

        case DirectionType::SOUTH:
            MVMMatrix = translate(MVMMatrix, vec3(
                    camPos.x - modelTransformation.translation.x,
                    camPos.y + modelTransformation.translation.y,
                    camPos.z - modelTransformation.translation.z));
            MVMMatrix = rotate(MVMMatrix, radians(180.f), vec3(0, 1, 0));
            break;

        case DirectionType::WEST:
            MVMMatrix = translate(MVMMatrix, vec3(
                    camPos.x + modelTransformation.translation.z,
                    camPos.y + modelTransformation.translation.y,
                    camPos.z - modelTransformation.translation.x));
            MVMMatrix = rotate(MVMMatrix, radians(-270.f), vec3(0, 1, 0));
            break;
    }

    MVMMatrix = rotate(MVMMatrix, radians(modelTransformation.rotation.x), vec3(1, 0, 0));
    MVMMatrix = rotate(MVMMatrix, radians(modelTransformation.rotation.y), vec3(0, 1, 0));
    MVMMatrix = rotate(MVMMatrix, radians(modelTransformation.rotation.z), vec3(0, 0, 1));
    MVMMatrix = scale(MVMMatrix, vec3(modelTransformation.scale.x,
                                      modelTransformation.scale.y,
                                      modelTransformation.scale.z));

    return MVMMatrix;
}

mat4 ModelManager::applyModelTransformation(const ModelTransformation &modelTransformation, const vec3 &position)
{
    mat4 MVMMatrix = mat4(1);;
    return (modelTransformation.isFix ? transformFixModel(_camera, MVMMatrix, modelTransformation)
                                      : transformMobileModel(MVMMatrix, position, modelTransformation));
}

void ModelManager::drawWeapon(const ModelType &modelType, const glimac::Program &program, const mat4 &projMatrix,
                              GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix, bool isAttacking)
{
    try
    {
        Model &model = _models.at(modelType);
        try
        {
            ModelTransformation modelTransformation = _modelTransformations.getModelTransformation(modelType,
                                                                                                   DirectionType::NEUTRAL);
            if (isAttacking)
            {
                modelTransformation.rotation += _modelTransformations.getRotationForAttackingWeapon();
            }
            mat4 MVMMatrix = applyModelTransformation(modelTransformation,
                                                      _camera.getPosition());
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);
        } catch (std::out_of_range &e)
        {
            std::cerr << "Model Transformation " << modelType << " not found" << std::endl;
        }

    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}


void ModelManager::drawModel(const ModelType &modelType, const vec3 &position, const DirectionType &directionType,
                             const glimac::Program &program, const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                             GLint uNormalMatrix)
{
    try
    {
        Model &model = _models.at(modelType);
        try
        {
            ModelTransformation modelTransformation = _modelTransformations.getModelTransformation(modelType,
                                                                                                   directionType);
            mat4                MVMMatrix           = applyModelTransformation(modelTransformation, position);
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);
        } catch (std::out_of_range &e)
        {
            std::cerr << "Model Transformation " << modelType << " not found" << std::endl;
        }

    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}

void ModelManager::drawModelDebug(const ModelType &modelType, const vec3 &position, const glimac::Program &program,
                                  const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                                  GLint uNormalMatrix, const mat4 &MVMMatrix)
{
    try
    {
        _models.at(modelType).draw(program);
    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}

void ModelManager::drawMultipleFixModels(const ModelType &modelType, const vec3 &position, const Program &program,
                                         const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                                         GLint uNormalMatrix, float space, unsigned int qty)
{
    try
    {
        mat4  MVMMatrix;
        Model model = _models.at(modelType);

        try
        {
            for (int i = 0; i < qty; ++i)
            {
                ModelTransformation modelTransformation = _modelTransformations.getModelTransformation(modelType,
                                                                                                       DirectionType::NEUTRAL);
                modelTransformation.translation.x += (float) i * space;
                MVMMatrix = applyModelTransformation(modelTransformation, vec3(position.x,
                                                                               position.y,
                                                                               position.z));
                DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                            uNormalMatrix);
                model.draw(program);
            }
        } catch (std::out_of_range &e)
        {
            std::cerr << "Model Transformation" << modelType << " not found" << std::endl;
        }
    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}

void ModelManager::drawDoor(const vec3 &position, const DirectionType &directionType, const glimac::Program &program,
                            const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                            GLint uNormalMatrix)
{
    ModelType modelType = DOOR_MODEL;
    try
    {
        Model &model = _models.at(modelType);
        try
        {
            ModelTransformation modelTransformation = _modelTransformations.getDoorModelTransformation(
                    DirectionType::NORTH);
            mat4                MVMMatrix           = applyModelTransformation(modelTransformation, position);
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);

            modelTransformation = _modelTransformations.getDoorModelTransformation(DirectionType::SOUTH);
            MVMMatrix           = applyModelTransformation(modelTransformation, position);
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);

            modelTransformation = _modelTransformations.getDoorModelTransformation(DirectionType::EAST);
            MVMMatrix           = applyModelTransformation(modelTransformation, position);
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);

            modelTransformation = _modelTransformations.getDoorModelTransformation(DirectionType::WEST);
            MVMMatrix           = applyModelTransformation(modelTransformation, position);
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);


        } catch (std::out_of_range &e)
        {
            std::cerr << "Model Transformation " << modelType << " not found" << std::endl;
        }

    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}

void
ModelManager::drawMonsterAttack(std::unique_ptr<Monster> &monster, const glimac::Program &program,
                                const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix)
{
    try
    {
        Model &model = _models.at(MONSTERS_ATTACK_MODEL);
        try
        {
            ModelTransformation modelTransformation = _modelTransformations.getAttackModelTransformation(
                    MONSTERS_ATTACK_MODEL,
                    monster->getDirectionType());

            mat4 MVMMatrix = applyModelTransformation(modelTransformation, monster->getPosition());
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);
            monster->modelHasAttacked();
        } catch (std::out_of_range &e)
        {
            std::cerr << "Model Transformation " << monster->getModelType() << " not found" << std::endl;
        }

    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << monster->getModelType() << " not found" << std::endl;
    }
}

void
ModelManager::drawAllModels(const glimac::Program &program, const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                            GLint uNormalMatrix)
{
    ModelType modelType;
    try
    {
        for (auto &monster: _monstersToDraw)
        {
            if (monster != nullptr)
            {
                modelType = monster->getModelType();
                Model model = _models.at(modelType);
                if (monster->getIsAttacking())
                {
                    drawModel(modelType, monster->getPosition(), monster->getDirectionType(), program, projMatrix,
                              uMVPMatrix, uMVMatrix, uNormalMatrix);
                    drawMonsterAttack(monster, program, projMatrix, uMVPMatrix, uMVMatrix, uNormalMatrix);
                }
                else
                {
                    drawModel(modelType, monster->getPosition(), monster->getDirectionType(), program, projMatrix,
                              uMVPMatrix, uMVMatrix, uNormalMatrix);
                }
            }
        }

        for (const auto &interactable: _interactableObjectsToDraw)
        {
            if (interactable != nullptr)
            {
                modelType = interactable->getModelType();
                Model model = _models.at(modelType);

                if (modelType == ModelType::DOOR_MODEL)
                {
                    drawDoor(interactable->getPosition(), interactable->getDirectionType(), program, projMatrix,
                             uMVPMatrix, uMVMatrix, uNormalMatrix);
                }
                else
                {
                    drawModel(modelType, interactable->getPosition(), interactable->getDirectionType(), program,
                              projMatrix, uMVPMatrix, uMVMatrix, uNormalMatrix);
                }
            }
        }
    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}

void ModelManager::drawModelFromModelTransformation(Model model, const ModelTransformation &modelTransformation,
                                                    const vec3 &position, const glimac::Program &program,
                                                    const mat4 &projMatrix, GLint uMVPMatrix, GLint uMVMatrix,
                                                    GLint uNormalMatrix)
{
    mat4 MVMMatrix = applyModelTransformation(modelTransformation, position);
    DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                uNormalMatrix);
    model.draw(program);
}

void ModelManager::drawInventory(const std::vector<ItemType> &items, const std::vector<WeaponType> &weaponsTypes,
                                 const glimac::Program &program, const mat4 &projMatrix,
                                 GLint uMVPMatrix, GLint uMVMatrix, GLint uNormalMatrix)
{

    ModelType modelType;
    try
    {

        for (int i = 0; i < items.size(); ++i)
        {
            modelType = Player::getModelTypeFromItemType(items[i]);
            Model               model               = _models.at(modelType);
            ModelTransformation modelTransformation = _modelTransformations.getModelTransformationForItem(items[i], i);
            drawModelFromModelTransformation(model, modelTransformation, vec3(0, 0, 0), program, projMatrix,
                                             uMVPMatrix, uMVMatrix, uNormalMatrix);
        }

        for (int i = 0; i < weaponsTypes.size(); ++i)
        {
            modelType = Weapon::getModelTypeFromWeaponType(weaponsTypes[i]);
            Model model = _models.at(modelType);

            ModelTransformation modelTransformation = _modelTransformations.getModelTransformationForInventoryWeapon(
                    weaponsTypes[i], i);

            mat4 MVMMatrix = applyModelTransformation(modelTransformation, vec3(0, 0, 0));
            DrawUtils::setUniformMatrix(MVMMatrix, _camera.getViewMatrix(), projMatrix, uMVPMatrix, uMVMatrix,
                                        uNormalMatrix);
            model.draw(program);
        }
    } catch (std::out_of_range &e)
    {
        std::cerr << "Model " << modelType << " not found" << std::endl;
    }
}