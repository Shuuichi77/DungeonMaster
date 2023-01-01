#pragma once

#include "Player.hpp"
#include "Monster.hpp"
#include "MapElement.hpp"
#include "InteractableObject.hpp"
#include "InventoryCoordinates.hpp"
#include "ChronoBetweenActions.hpp"

#include <glm/glm.hpp>
#include <memory>

class CharacterManager
{
private:
    Player                                           _player;
    std::vector<std::unique_ptr<Monster>>            _monsters;
    std::vector<std::unique_ptr<InteractableObject>> _interactableObjects;
    InventoryCoordinates                             _inventoryCoordinates;
    ChronoBetweenActions                             _chronoBetweenMonstersUpdate;

    static glm::vec3 getCoordsClicked(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType);

    bool inventoryIsClicked(const glm::vec2 &mousePosition);

public:
    explicit CharacterManager(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType,
                              unsigned int windowWidth, unsigned int windowHeight);

    ~CharacterManager() = default;

    Player &getPlayer() { return _player; }

    void addMonster(std::unique_ptr<Monster> monster);

    void addInteractableObject(std::unique_ptr<InteractableObject> interactableObject);

    std::vector<std::unique_ptr<Monster>> &getMonsters() { return _monsters; }

    std::vector<std::unique_ptr<InteractableObject>> &getInteractableObjects() { return _interactableObjects; }

    bool leftClick(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType,
                   const glm::vec2 &mousePosition);

    bool updateMonsters(const std::vector<std::vector<MapElement>> &map);
};