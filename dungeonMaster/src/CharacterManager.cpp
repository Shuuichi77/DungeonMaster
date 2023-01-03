#include <algorithm>
#include "../include/CharacterManager.hpp"

CharacterManager::CharacterManager(const glm::vec3 &playerPosition, const DirectionType &playerDirectionType,
                                   unsigned int windowWidth, unsigned int windowHeight,
                                   std::vector<std::unique_ptr<InteractableObject>> &interableObjects,
                                   std::vector<std::unique_ptr<Monster>> &monsters, Music &music)
        : _player(playerPosition, playerDirectionType)
        , _inventoryCoordinates(windowWidth, windowHeight)
        , _music(music)
{
    _interactableObjects = std::move(interableObjects);
    _monsters            = std::move(monsters);
}


void CharacterManager::leftClick(const DirectionType &playerDirectionType,
                                 const glm::vec2 &mousePosition, FreeflyCamera &camera)
{
    int _playerMoney = _player.getMoney();

    if (inventoryIsClicked(mousePosition, camera))
    {
        return;
    }

    glm::vec3 coordsClicked = getCoordsClicked(_player.getPosition(), playerDirectionType);

    _monsters.erase(std::remove_if(_monsters.begin(), _monsters.end(),
                                   [&coordsClicked, this](
                                           const std::unique_ptr<Monster> &monster)
                                   {
                                       if (monster != nullptr && monster->isClicked(coordsClicked))
                                       {
                                           _player.setIsAttacking(true);
                                           _music.playPlayerHit();

                                           if (monster->loseHealth(_player.getAttack()))
                                           {
                                               _player.addMonsterKilled();
                                               _player.addMoney(monster->getMoney());
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
                                                      _music.playSoundSuccess();
                                                      return true;
                                                  }

                                                  return false;
                                              }), _interactableObjects.end());
}

bool CharacterManager::inventoryIsClicked(const glm::vec2 &mousePosition, FreeflyCamera &camera)
{
    std::pair<InventoryCoordinatesType, unsigned int> _inventoryTypeNumber = _inventoryCoordinates.getInventoryCoordinatesType(
            mousePosition);

    switch (_inventoryTypeNumber.first)
    {
        case InventoryCoordinatesType::ITEM:_player.useItem(_inventoryTypeNumber.second, _music);
            return true;
        case InventoryCoordinatesType::WEAPON:_player.changeWeapon(_inventoryTypeNumber.second);
            _music.changeWeapon();
            return true;
        case InventoryCoordinatesType::LEFT_ARROW:camera.rotateLeft(90.f);
            return true;
        case InventoryCoordinatesType::RIGHT_ARROW:camera.rotateLeft(-90.f);
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

bool CharacterManager::updateMonsters(const std::vector<std::vector<MapElement>> &map)
{
    if (_chronoBetweenMonstersUpdate.isTimeElapsed())
    {
        for (auto &monster: _monsters)
        {
            if (monster != nullptr && monster->update(_player, map, _monsters, _interactableObjects, _music))
            {
                return true;
            }
        }
    }

    return false;
}


