#include <iostream>
#include "../include/CameraManager.hpp"
#include "../include/Utils.hpp"

CameraManager::CameraManager(FreeflyCamera &camera, glimac::SDLWindowManager &windowManager, bool &gameWin)
        : _camera(camera)
        , _windowManager(windowManager)
        , _gameWin(gameWin) {}

void CameraManager::moveCamera(const SDL_MouseButtonEvent &button,
                               const std::vector<std::vector<MapElement>> &map,
                               const std::vector<std::unique_ptr<Monster>> &monsters,
                               const std::vector<std::unique_ptr<InteractableObject>> &_interactableObjects,
                               Player &player)
{
    if (_windowManager.isKeyPressed(SDLK_a))
    {
        _camera.rotateLeft(90.f);
    }
    if (_windowManager.isKeyPressed(SDLK_e))
    {
        _camera.rotateLeft(-90.f);
    }
    if (_windowManager.isKeyPressed(SDLK_z))
    {
        if (canMoveTowardDirection(DirectionType::NORTH, map, monsters, _interactableObjects))
        {
            _camera.moveFront(1.f);
            player.setPosition(_camera.getPosition());
        }
    }
    if (_windowManager.isKeyPressed(SDLK_s))
    {
        if (canMoveTowardDirection(DirectionType::SOUTH, map, monsters, _interactableObjects))
        {
            _camera.moveFront(-1.f);
            player.setPosition(_camera.getPosition());
        }
    }
    if (_windowManager.isKeyPressed(SDLK_q))
    {
        if (canMoveTowardDirection(DirectionType::WEST, map, monsters, _interactableObjects))
        {
            _camera.moveLeft(1.f);
            player.setPosition(_camera.getPosition());
        }
    }
    if (_windowManager.isKeyPressed(SDLK_d))
    {
        if (canMoveTowardDirection(DirectionType::EAST, map, monsters, _interactableObjects))
        {
            _camera.moveLeft(-1.f);
            player.setPosition(_camera.getPosition());
        }
    }
}

bool CameraManager::isOutOfMap(int i, int j, const std::vector<std::vector<MapElement>> &map)
{
    return i < 0 || i >= map.size() || j < 0 || j >= map[i].size();
}

bool CameraManager::canMoveTowardDirection(DirectionType nextMovementDirectionType,
                                           const std::vector<std::vector<MapElement>> &map,
                                           const std::vector<std::unique_ptr<Monster>> &monsters,
                                           const std::vector<std::unique_ptr<InteractableObject>> &_interactableObjects)
{
    glm::vec3 nextPosition = Utils::getNextPosition(_camera.getPosition(), _camera.getCameraDirection(),
                                                    nextMovementDirectionType);

    for (const auto &monster: monsters)
    {
        if (monster != nullptr && Utils::cmpNextPosAndPos(monster->getPosition(), nextPosition))
        {
            return false;
        }
    }
    for (const auto &interactableObject: _interactableObjects)
    {
        if (interactableObject != nullptr && Utils::cmpNextPosAndPos(interactableObject->getPosition(), nextPosition))
        {
            return false;
        }
    }

    int i = Utils::floatToint(-nextPosition.z);
    int j = Utils::floatToint(nextPosition.x);
    if (isOutOfMap(i, j, map))
    {
        return false;
    }

    if (map[i][j] == MapElement::WALL || map[i][j] == MapElement::WATER)
    {
        std::cout << "Wall" << std::endl;
        return false;
    }

    if (map[i][j] == MapElement::EXIT)
    {
        std::cout << "Exit" << std::endl;
        _gameWin = true;
        return true;
    }

    return true;
}
