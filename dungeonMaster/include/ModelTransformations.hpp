#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

#include "ModelType.hpp"
#include "DirectionType.hpp"
#include "Weapon.hpp"
#include "ItemType.hpp"

using namespace glm;


static vec3 rotationForAttackingWeapon = glm::vec3(-47, 5, 5);
static vec3 globalTranslation          = vec3(0.f, 0.25f, 0.f);
static vec3 globalScale                = vec3(1.f, 0.75f, 1.f);

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

    void addSword01AttackingModelTransformation();

    void addSword02ModelTransformation();

    void addSword02AttackingModelTransformation();

    void addSword03ModelTransformation();

    void addSword03AttackingModelTransformation();

    void addHealthModelTransformation();

    void addKeyModelTransformation();

    void addMonster1ModelTransformation();

    void addMonster2ModelTransformation();

    void addMonster3AModelTransformation();

    void addMonstersAttackModelTransformation();

    void addExitModelTransformation();

    void addChestModelTransformation();

    void addMoneyModelTransformation();

    void addDoorModelTransformation();

    void addInventoryModelTransformation();

    void addMenuModelTransformation();

    void addHealthPotionModelTransformation();

    void addMilkModelTransformation();

    void addFairyModelTransformation();

public:
    ModelTransformations();

    static vec3 getGlobalTranslate() { return globalTranslation; }

    static vec3 getGlobalScale() { return globalScale; }

    ModelTransformation getModelTransformation(const ModelType &modelType, const DirectionType &directionType) const;

    ModelTransformation getAttackModelTransformation(const ModelType &modelType, const DirectionType &directionType);

    ModelTransformation getModelTransformation(const ModelType &modelType) const;

    ModelTransformation getDoorModelTransformation(const DirectionType &directionType) const;

    ModelTransformation getModelTransformationForItem(ItemType itemType, unsigned int index) const;

    ModelTransformation getModelTransformationForInventoryWeapon(WeaponType weaponType, unsigned int index) const;

    static vec3 getRotationForAttackingWeapon() { return rotationForAttackingWeapon; }
};

