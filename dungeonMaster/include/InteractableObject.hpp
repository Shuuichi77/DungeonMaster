#pragma once


#include <glm/glm.hpp>
#include "Interactable.hpp"
#include "Player.hpp"

enum InteractableObjectType
{
    INTERACTABLE_DOOR,
    INTERACTABLE_CHEST_MONEY,
    INTERACTABLE_CHEST_KEY,
    INTERACTABLE_CHEST_MILK,
    INTERACTABLE_CHEST_HEALTH_POTION,
    INTERACTABLE_CHEST_FAIRY,
    INTERACTABLE_CHEST_WEAPON_01,
    INTERACTABLE_CHEST_WEAPON_02,
    INTERACTABLE_CHEST_WEAPON_03,
};

class InteractableObject : public Interactable
{
private:
    InteractableObjectType _type;
    unsigned int           _qty;
    ModelType              _modelType;

    static ModelType getModelTypeFromInteractableObjectType(InteractableObjectType type);

public:
    explicit InteractableObject(InteractableObjectType type, const glm::vec3 &position,
                                const DirectionType &directionType, unsigned int qty = 1u);

    ~InteractableObject() override = default;

    InteractableObjectType getType() const { return _type; }

    bool interactWithPlayer(Player &player);

    ModelType getModelType() const override { return _modelType; }
};