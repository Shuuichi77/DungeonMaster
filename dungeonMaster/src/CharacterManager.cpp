#include <iostream>
#include <algorithm>
#include "../include/CharacterManager.hpp"

CharacterManager::CharacterManager(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType,
                                   unsigned int windowWidth, unsigned int windowHeight)
        : _player(playerPosition, playerDirectionType)
        , _inventoryCoordinates(windowWidth, windowHeight) {}


bool CharacterManager::leftClick(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType,
                                 const glm::vec2 &mousePosition)
{
    int _playerMoney = _player.getMoney();

    if (inventoryIsClicked(mousePosition))
    {
        return false;
    }

    glm::vec3 coordsClicked = getCoordsClicked(playerPosition, playerDirectionType);

    _monsters.erase(std::remove_if(_monsters.begin(), _monsters.end(),
                                   [&coordsClicked, this](
                                           const std::unique_ptr<Monster> &monster)
                                   {
                                       if (monster != nullptr && monster->isClicked(coordsClicked))
                                       {
                                           if (monster->loseHealth(_player.getAttack()))
                                           {
                                               _player.addMoney(monster->getMoney());
                                               std::cout << _player.getMoney() << std::endl;
                                               return true;
                                           }
                                       }

                                       return false;
                                   }), _monsters.end());

    _interactableObjects.erase(std::remove_if(_interactableObjects.begin(), _interactableObjects.end(),
                                              [&coordsClicked, this](
                                                      const std::unique_ptr<InteractableObject> &interactableObject)
                                              {
                                                  if (interactableObject != nullptr &&
                                                      interactableObject->isClicked(coordsClicked) &&
                                                      interactableObject->interactWithPlayer(_player))
                                                  {
                                                      return true;
                                                  }

                                                  return false;
                                              }), _interactableObjects.end());

    return _playerMoney != _player.getMoney();
}

bool CharacterManager::inventoryIsClicked(const glm::vec2 &mousePosition)
{
    std::pair<InventoryCoordinatesType, unsigned int> _inventoryTypeNumber = _inventoryCoordinates.getInventoryCoordinatesType(
            mousePosition);

    switch (_inventoryTypeNumber.first)
    {
        case InventoryCoordinatesType::ITEM:_player.useItem(_inventoryTypeNumber.second);
            return true;
        case InventoryCoordinatesType::WEAPON:_player.changeWeapon(_inventoryTypeNumber.second);
            return true;
        default:return false;
    }
}

glm::vec3 CharacterManager::getCoordsClicked(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType)
{
    glm::vec3 coordsClicked = playerPosition;

    switch (playerDirectionType)
    {
        case NORTH:coordsClicked.z -= 1;
            break;
        case SOUTH:coordsClicked.z += 1;
            break;
        case EAST:coordsClicked.x += 1;
            break;
        case WEST:coordsClicked.x -= 1;
            break;
        case NEUTRAL:break;
    }

    return coordsClicked;
}

void CharacterManager::addMonster(std::unique_ptr<Monster> monster)
{
    assert(monster != nullptr);
    _monsters.emplace_back(std::move(monster));
}

void CharacterManager::addInteractableObject(std::unique_ptr<InteractableObject> interactableObject)
{
    assert(interactableObject != nullptr);
    _interactableObjects.emplace_back(std::move(interactableObject));
}

bool CharacterManager::updateMonsters(const std::vector<std::vector<MapElement>> &map)
{
    if (_chronoBetweenMonstersUpdate.isTimeElapsed())
    {
        for (auto &monster: _monsters)
        {
            if (monster != nullptr && monster->update(_player, map, _monsters, _interactableObjects))
            {
                return true;
            }
        }
    }

    return false;
}


