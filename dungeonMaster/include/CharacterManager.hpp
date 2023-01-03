#pragma once

#include "Player.hpp"
#include "Monster.hpp"
#include "MapElement.hpp"
#include "InteractableObject.hpp"
#include "InventoryCoordinates.hpp"
#include "ChronoBetweenActions.hpp"
#include "FreeflyCamera.hpp"

#include <glm/glm.hpp>
#include <memory>

class CharacterManager
{
private:
    Music                                            &_music;
    Player                                           _player;
    std::vector<std::unique_ptr<Monster>>            _monsters;
    std::vector<std::unique_ptr<InteractableObject>> _interactableObjects;
    InventoryCoordinates                             _inventoryCoordinates;
    ChronoBetweenActions                             _chronoBetweenMonstersUpdate;

    static glm::vec3 getCoordsClicked(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType);

    bool inventoryIsClicked(const glm::vec2 &mousePosition, FreeflyCamera &camera);

public:
    explicit CharacterManager(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType,
                              unsigned int windowWidth, unsigned int windowHeight,
                              std::vector<std::unique_ptr<InteractableObject>> &interableObjects,
                              std::vector<std::unique_ptr<Monster>> &monsters, Music &music);

    ~CharacterManager() = default;

    Player &getPlayer() { return _player; }

    std::vector<std::unique_ptr<Monster>> &getMonsters() { return _monsters; }

    std::vector<std::unique_ptr<InteractableObject>> &getInteractableObjects() { return _interactableObjects; }

    void leftClick(const DirectionType &playerDirectionType, const glm::vec2 &mousePosition, FreeflyCamera &camera);

    bool updateMonsters(const std::vector<std::vector<MapElement>> &map);
};