#include "../include/InteractableObject.hpp"


InteractableObject::InteractableObject(InteractableObjectType type, const glm::vec3 &position,
                                       const DirectionType &directionType, unsigned int qty)
        : Interactable(position, directionType)
        , _type(type)
        , _qty(qty)
        , _modelType(getModelTypeFromInteractableObjectType(type)) {}

ModelType InteractableObject::getModelTypeFromInteractableObjectType(InteractableObjectType type)
{
    switch (type)
    {
        case INTERACTABLE_DOOR: //
            return ModelType::DOOR_MODEL;

        case INTERACTABLE_CHEST_MONEY: //
        case INTERACTABLE_CHEST_KEY: //
        case INTERACTABLE_CHEST_MILK: //
        case INTERACTABLE_CHEST_HEALTH_POTION: //
        case INTERACTABLE_CHEST_FAIRY: //
        case INTERACTABLE_CHEST_WEAPON_01: //
        case INTERACTABLE_CHEST_WEAPON_02: //
        case INTERACTABLE_CHEST_WEAPON_03: //
            return ModelType::CHEST_MODEL;

        default:return ModelType::NONE;
    }
}

bool InteractableObject::interactWithPlayer(Player &player)
{
    switch (_type)
    {
        case INTERACTABLE_DOOR: //
            return player.useKey();

        case INTERACTABLE_CHEST_MONEY: //
            player.addMoney(_qty);
            return true;

        case INTERACTABLE_CHEST_KEY: //
            player.addKey();
            return true;

        case INTERACTABLE_CHEST_MILK: //
            player.addItem(MILK);
            return true;

        case INTERACTABLE_CHEST_HEALTH_POTION: //
            player.addItem(HEALTH_POTION);
            return true;

        case INTERACTABLE_CHEST_FAIRY: //
            player.addItem(FAIRY);
            return true;

        case INTERACTABLE_CHEST_WEAPON_01: //
            player.addWeapon(WOODEN_SWORD);
            return true;

        case INTERACTABLE_CHEST_WEAPON_02: //
            player.addWeapon(ROYAL_SWORD);
            return true;

        case INTERACTABLE_CHEST_WEAPON_03: //
            player.addWeapon(MASTER_SWORD);
            return true;
    }

    return false;
}




