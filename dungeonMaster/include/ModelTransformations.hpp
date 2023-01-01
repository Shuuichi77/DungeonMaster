#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

#include "ModelType.hpp"
#include "DirectionType.hpp"
#include "Player.hpp"

using namespace glm;


static vec3 globalTranslation = vec3(0.f, 0.25f, 0.f);
static vec3 globalScale       = vec3(1.f, 0.75f, 1.f);

struct ModelTransformation
{
    bool isVertical = false;
    vec3 translation;
    vec3 rotation;
    vec3 scale;
    bool isFix      = false;
};

class ModelTransformations
{
private:
    std::unordered_map<ModelType, ModelTransformation> _attributes;

    void addModelTransformation(const ModelType &modelType, const ModelTransformation &modelTrans);

    void addSword01InInventoryModelTransformation();

    void addSword02InInventoryModelTransformation();

    void addSword03InInventoryModelTransformation();

    void addSword01ModelTransformation();

    void addSword02ModelTransformation();

    void addSword03ModelTransformation();

    void addHealthModelTransformation();

    void addKeyModelTransformation();

    void addMonster1ModelTransformation();

    void addMonster2ModelTransformation();

    void addMonster3AModelTransformation();

    void addExitModelTransformation();

    void addChestModelTransformation();

    void addMoneyModelTransformation();

    void addDoorModelTransformation();

    void addInventoryModelTransformation();

    void addHealthPotionModelTransformation();

    void addMilkModelTransformation();

    void addFairyModelTransformation();

public:
    ModelTransformations();

    static vec3 getGlobalTranslate() { return globalTranslation; }

    static vec3 getGlobalScale() { return globalScale; }

    ModelTransformation getModelTransformation(const ModelType &modelType, const DirectionType &directionType) const;

    ModelTransformation getModelTransformation(const ModelType &modelType) const;

    ModelTransformation getDoorModelTransformation(const DirectionType &directionType) const;

    ModelTransformation getModelTransformationForItem(ItemType itemType, unsigned int index) const;

    ModelTransformation getModelTransformationForWeapon(WeaponType weaponType, unsigned int index);
};

