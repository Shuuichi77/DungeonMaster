#include <iostream>
#include "../include/ModelTransformations.hpp"
#include "../include/Player.hpp"

ModelTransformations::ModelTransformations()
{
    addSword01InInventoryModelTransformation();
    addSword02InInventoryModelTransformation();
    addSword03InInventoryModelTransformation();
    addSword01ModelTransformation();
    addSword02ModelTransformation();
    addSword03ModelTransformation();
    addHealthModelTransformation();
    addKeyModelTransformation();
    addMonster1ModelTransformation();
    addMonster2ModelTransformation();
    addMonster3AModelTransformation();
    addExitModelTransformation();
    addChestModelTransformation();
    addMoneyModelTransformation();
    addDoorModelTransformation();
    addInventoryModelTransformation();
    addMenuModelTransformation();
    addHealthPotionModelTransformation();
    addMilkModelTransformation();
    addFairyModelTransformation();
}

ModelTransformation ModelTransformations::getModelTransformation(const ModelType &modelType) const
{
    return _attributes.at(modelType);
}

ModelTransformation ModelTransformations::getModelTransformation(const ModelType &modelType,
                                                                 const DirectionType &directionType) const
{
    ModelTransformation modelTransformation = _attributes.at(modelType);

    if (modelTransformation.isVertical)
    {
        switch (directionType)
        {
            case DirectionType::EAST:modelTransformation.rotation += vec3(0.f, 0.f, 90.f);
                break;
            case DirectionType::NORTH:modelTransformation.rotation += vec3(0.f, 0.f, 180.f);
                break;
            case DirectionType::WEST:modelTransformation.rotation += vec3(0.f, 0.f, 270.f);
                break;
            case DirectionType::NEUTRAL: // do nothing
            case DirectionType::SOUTH: // do nothing
                break;
        }
    }
    else
    {
        switch (directionType)
        {
            case DirectionType::EAST:modelTransformation.rotation += vec3(0.f, 90.f, 0.f);
                break;
            case DirectionType::NORTH:modelTransformation.rotation += vec3(0.f, 180.f, 0.f);
                break;
            case DirectionType::WEST:modelTransformation.rotation += vec3(0.f, 270.f, 0.f);
                break;
            case DirectionType::NEUTRAL: // do nothing
            case DirectionType::SOUTH: // do nothing
                break;
        }
    }

    return modelTransformation;
}

ModelTransformation ModelTransformations::getDoorModelTransformation(const DirectionType &directionType) const
{
    ModelTransformation modelTransformation = _attributes.at(DOOR_MODEL);

    switch (directionType)
    {
        case DirectionType::NORTH: //
            modelTransformation.translation += vec3(0.f, 0.f, -0.4f);
            break;

        case DirectionType::SOUTH: //
            modelTransformation.translation += vec3(0.f, 0.f, 0.4f);
            break;

        case DirectionType::EAST: //
            modelTransformation.rotation += vec3(0.f, 90.f, 0.f);
            modelTransformation.translation += vec3(0.4f, 0.f, 0.f);
            break;

        case DirectionType::WEST: //
            modelTransformation.rotation += vec3(0.f, 90.f, 0.f);
            modelTransformation.translation += vec3(-0.4f, 0.f, 0.f);
            break;

        case DirectionType::NEUTRAL: // do nothing
            std::cerr << "Door directionType is neutral, which shouldn't happen" << std::endl;
            break;
    }

    return modelTransformation;
}

void ModelTransformations::addModelTransformation(const ModelType &modelType, const ModelTransformation &modelTrans)
{
    _attributes.emplace(modelType, modelTrans);
}

void ModelTransformations::addSword01InInventoryModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.18, 0.090, -0.35) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-90, -90, 9);
    modelTransformation.scale       = glm::vec3(1. / 13.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(WOODEN_SWORD_IN_INVENTORY_MODEL, modelTransformation);
}

void ModelTransformations::addSword02InInventoryModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.16, 0.1075, -0.31) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-90, -90, 9);
    modelTransformation.scale       = glm::vec3(1. / 14.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(ROYAL_SWORD_IN_INVENTORY_MODEL, modelTransformation);
}


void ModelTransformations::addSword03InInventoryModelTransformation()
{
    ModelTransformation modelTransformation;
    modelTransformation.translation = glm::vec3(0.141, 0.126, -0.27) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-90, -90, 9);
    modelTransformation.scale       = glm::vec3(1. / 1580.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(MASTER_SWORD_IN_INVENTORY_MODEL, modelTransformation);
}

void ModelTransformations::addSword01ModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.33, -0.02, -0.65) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-96, -14, 44);
    modelTransformation.scale       = glm::vec3(1. / 2.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(WOODEN_SWORD_MODEL, modelTransformation);
}

void ModelTransformations::addSword02ModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.33, -0.02, -0.65) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-96, -14, 44);
    modelTransformation.scale       = glm::vec3(1. / 2.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(ROYAL_SWORD_MODEL, modelTransformation);
}

void ModelTransformations::addSword03ModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.33, -0.02, -0.65) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-96, -14, 44);
    modelTransformation.scale       = glm::vec3(1. / 175.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(MASTER_SWORD_MODEL, modelTransformation);
}

void ModelTransformations::addHealthModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(-0.09, 0.342, -0.14) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-90, 0, 0);
    modelTransformation.scale       = glm::vec3(1. / 100.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(HEALTH_MODEL, modelTransformation);
}

void ModelTransformations::addKeyModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(-0.1925f, 0.405f, -0.30f) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-90, 0, 0);
    modelTransformation.scale       = glm::vec3(1. / 58) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(KEY_MODEL, modelTransformation);
}

// ARMOGOHMA
void ModelTransformations::addMonster1ModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = -getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-90, 0, 0);
    modelTransformation.scale       = glm::vec3(1. / 2168.f) * getGlobalScale();
    modelTransformation.isVertical  = true;

    addModelTransformation(MONSTER_01_MODEL, modelTransformation);
}

// KING BOO
void ModelTransformations::addMonster2ModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.f, 0.2f, 0.f) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(0, 0, 0);
    modelTransformation.scale       = glm::vec3(1. / 5.f) * getGlobalScale();

    addModelTransformation(MONSTER_02_MODEL, modelTransformation);
}

// DARKRAI
void ModelTransformations::addMonster3AModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = -getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(0.f, 30.f, 0.f);
    modelTransformation.scale       = glm::vec3(1. / 15.f) * getGlobalScale();
    addModelTransformation(MONSTER_03_MODEL, modelTransformation);
}

// EXIT
void ModelTransformations::addExitModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = -getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(0.f, 0.f, 0.f);
    modelTransformation.scale       = glm::vec3(1. / 1.5f) * getGlobalScale();

    addModelTransformation(LADDER_MODEL, modelTransformation);
}

void ModelTransformations::addChestModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.f, 0.f, 0.f) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(0, 0, 0);
    modelTransformation.scale       = glm::vec3(1. / 3.) * getGlobalScale();

    addModelTransformation(CHEST_MODEL, modelTransformation);
}

void ModelTransformations::addMoneyModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(-0.25, 0.48, -0.39) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(97, -1, -20);
    modelTransformation.scale       = glm::vec3(1. / 50.) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(MONEY_MODEL, modelTransformation);
}

void ModelTransformations::addDoorModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0, 0.5, 0) - getGlobalTranslate();
    modelTransformation.scale       = glm::vec3(1. / 256., 1. / 191., 1. / 191.) * getGlobalScale();

    addModelTransformation(DOOR_MODEL, modelTransformation);
}

void ModelTransformations::addInventoryModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = vec3(0, 0.058, -0.35) - ModelTransformations::getGlobalTranslate();
    modelTransformation.rotation    = vec3(0.f, 0.f, 0.f);
    modelTransformation.scale       = vec3(1.f / 2.f, 1.f / 7.f, 1.f / 2.f) * ModelTransformations::getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(INVENTORY_MODEL, modelTransformation);
}

void ModelTransformations::addMenuModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = vec3(0, 0.25, -0.71) - ModelTransformations::getGlobalTranslate();
    modelTransformation.rotation    = vec3(0.f, 0.f, 0.f);
    modelTransformation.scale       = vec3(1.f, 1.f, 1.f);
    modelTransformation.isFix       = true;

    addModelTransformation(MENU_MODEL, modelTransformation);
}


void ModelTransformations::addHealthPotionModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(-0.07, 0.1805, -0.14) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-25, -3, -75);
    modelTransformation.scale       = glm::vec3(1. / 41.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(HEALTH_POTION_MODEL, modelTransformation);
}

void ModelTransformations::addMilkModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(-0.15, 0.108, -0.29) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-1, 30, -7);
    modelTransformation.scale       = glm::vec3(1. / 1044.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(MILK_MODEL, modelTransformation);
}

void ModelTransformations::addFairyModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(-0.11, 0.146, -0.21) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(-10, 10, -21);
    modelTransformation.scale       = glm::vec3(1. / 927.f) * getGlobalScale();
    modelTransformation.isFix       = true;

    addModelTransformation(FAIRY_MODEL, modelTransformation);
}

ModelTransformation ModelTransformations::getModelTransformationForItem(ItemType itemType, unsigned int index) const
{
    ModelTransformation modelTransformation;

    float tx;
    float ty;
    int   i = index % 2;
    int   j = index / 2;

    switch (itemType)
    {
        case ItemType::HEALTH_POTION: //
            tx                  = 0.0265;
            ty                  = 0.0125;
            modelTransformation = getModelTransformation(HEALTH_POTION_MODEL);
            break;

        case ItemType::MILK: //
            tx                  = 0.055;
            ty                  = 0.026;
            modelTransformation = getModelTransformation(MILK_MODEL);
            break;
        case ItemType::FAIRY: //
            tx                  = 0.04;
            ty                  = 0.019;
            modelTransformation = getModelTransformation(FAIRY_MODEL);
            break;
    }

    modelTransformation.translation += glm::vec3((float) i * tx, -((float) j * ty), 0);

    return modelTransformation;
}

ModelTransformation
ModelTransformations::getModelTransformationForWeapon(WeaponType weaponType, unsigned int index)
{
    ModelTransformation modelTransformation;

    float ty;

    switch (weaponType)
    {
        case WeaponType::WOODEN_SWORD: //
            ty                  = 0.031;
            modelTransformation = getModelTransformation(
                    Weapon::getInventoryModelTypeFromWeaponType(WeaponType::WOODEN_SWORD));
            break;


        case WeaponType::ROYAL_SWORD: //
            ty                  = 0.0275;
            modelTransformation = getModelTransformation(
                    Weapon::getInventoryModelTypeFromWeaponType(WeaponType::ROYAL_SWORD));
            break;

        case WeaponType::MASTER_SWORD: //
            ty                  = 0.0245;
            modelTransformation = getModelTransformation(
                    Weapon::getInventoryModelTypeFromWeaponType(WeaponType::MASTER_SWORD));
            break;

    }

    modelTransformation.translation += glm::vec3(0, -((float) index * ty), 0);

    return modelTransformation;
}

//ModelTransformation ModelTransformations::getModelTransformationForWeapon(WeaponType weaponType, unsigned int index)
//{
//    ModelTransformation modelTransformation;
//
//    float ty;
//
//    switch (weaponType)
//    {
//        case WeaponType::WOODEN_SWORD: //
//            ty                  = 0.02;
//            modelTransformation = getModelTransformation(WeaponType::WOODEN_SWORD);
//            break;
////        case WeaponType //
////            ty = 0.031;
////            modelTransformation = getModelTransformation(HEALTH_POTION_MODEL);
////            break;
////
////        case ItemType::MILK: //
////            ty = 0.0275
////            ty                  = 0.026;
////            modelTransformation = getModelTransformation(MILK_MODEL);
////            break;
////        case ItemType::FAIRY: //
////            ty = 0.0245
////            modelTransformation = getModelTransformation(FAIRY_MODEL);
////            break;
//    }
//
////    modelTransformation.translation += glm::vec3((float) i * tx, -((float) j * ty), 0);
////
////    return modelTransformation;
//}


// ------------------------------ REFERENCE ------------------------------
/*
void ModelTransformations::addTODOModelTransformation()
{
    ModelTransformation modelTransformation;

    modelTransformation.translation = glm::vec3(0.f, 0.f, 0.f) - getGlobalTranslate();
    modelTransformation.rotation    = glm::vec3(0, 0, 0);
    modelTransformation.scale       = glm::vec3(1. / TODO) * getGlobalScale();
    modelTransformation.isFix       = TODO;

    addModelTransformation(TODO, modelTransformation);
}
*/