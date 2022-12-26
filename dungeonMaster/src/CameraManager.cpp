#include <iostream>
#include "../include/CameraManager.hpp"

#include "../include/Utils.hpp"

CameraManager::CameraManager(FreeflyCamera &camera, const glimac::SDLWindowManager &windowManager,
                             const std::vector<std::vector<ObjectType>> &map)
        : _camera(camera)
        , _windowManager(windowManager)
        , _map(map) {}

void CameraManager::moveCamera()
{
    if (!_cameraCanMove && canMoveAgain())
    {
        std::cout << "Current Position: " << _camera.getPosition() << "\n" << std::endl;
        _cameraCanMove = true;
    }

    if (_cameraCanMove)
    {
        if (_windowManager.isKeyPressed(SDLK_a))
        {
            _camera.rotateLeft(90.f);
            _timeMoved     = std::chrono::system_clock::now();
            _cameraCanMove = false;
        }
        if (_windowManager.isKeyPressed(SDLK_e))
        {
            _camera.rotateLeft(-90.f);
            _timeMoved     = std::chrono::system_clock::now();
            _cameraCanMove = false;
        }
        if (_windowManager.isKeyPressed(SDLK_z))
        {
            if (canMoveTowardDirection(DirectionType::NORTH))
            {
                _camera.moveFront(1.f);
            }
            _timeMoved     = std::chrono::system_clock::now();
            _cameraCanMove = false;
        }
        if (_windowManager.isKeyPressed(SDLK_s))
        {
            if (canMoveTowardDirection(DirectionType::SOUTH))
            {
                _camera.moveFront(-1.f);
            }
            _timeMoved     = std::chrono::system_clock::now();
            _cameraCanMove = false;
        }
        if (_windowManager.isKeyPressed(SDLK_q))
        {
            if (canMoveTowardDirection(DirectionType::WEST))
            {
                _camera.moveLeft(1.f);

            }
            _timeMoved     = std::chrono::system_clock::now();
            _cameraCanMove = false;
        }
        if (_windowManager.isKeyPressed(SDLK_d))
        {
            if (canMoveTowardDirection(DirectionType::EAST))
            {
                _camera.moveLeft(-1.f);

            }
            _timeMoved     = std::chrono::system_clock::now();
            _cameraCanMove = false;
        }
    }
}

bool CameraManager::isOutOfMap(int i, int j)
{
    return i < 0 || i >= _map.size() || j < 0 || j >= _map[i].size();
}

bool CameraManager::canMoveTowardDirection(DirectionType nextMovementDirectionType)
{
    const glm::vec3 nextCameraPos = _camera.getPosition() = getNextPosition(_camera.getCameraDirection(),
                                                                            nextMovementDirectionType);

    int i = floatToint(-nextCameraPos.z);
    int j = floatToint(nextCameraPos.x);

    std::cout << _map.size() << ", " << _map[i].size() << std::endl;

    if (isOutOfMap(i, j))
    {
        std::cout << "OUT OF MAP" << std::endl;
        return false;
    }

    if (_map[i][j] == ObjectType::WALL)
    {
        std::cout << "WALL" << std::endl;
        return false;
    }

    return true;
}

bool CameraManager::canMoveAgain()
{
    std::chrono::time_point<std::chrono::system_clock> now             = std::chrono::system_clock::now();
    std::chrono::duration<double>                      elapsed_seconds = now - _timeMoved;
    if (elapsed_seconds.count() > 0.15)
    {
        return true;
    }
    return false;
}

glm::vec3 CameraManager::getNextPosition(DirectionType cameraDirection, DirectionType nextMovementDirectionType)
{
    switch (nextMovementDirectionType)
    {
        case NORTH:
            switch (cameraDirection)
            {
                case NORTH:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z - 1 };
                case EAST:
                    return glm::vec3 { _camera.getPosition().x + 1, _camera.getPosition().y, _camera.getPosition().z };
                case SOUTH:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z + 1 };
                case WEST:
                    return glm::vec3 { _camera.getPosition().x - 1, _camera.getPosition().y, _camera.getPosition().z };
            }

        case EAST:
            switch (cameraDirection)
            {
                case NORTH:
                    return glm::vec3 { _camera.getPosition().x + 1, _camera.getPosition().y, _camera.getPosition().z };
                case EAST:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z + 1 };
                case SOUTH:
                    return glm::vec3 { _camera.getPosition().x - 1, _camera.getPosition().y, _camera.getPosition().z };
                case WEST:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z - 1 };
            }

        case SOUTH:
            switch (cameraDirection)
            {
                case NORTH:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z + 1 };
                case EAST:
                    return glm::vec3 { _camera.getPosition().x - 1, _camera.getPosition().y, _camera.getPosition().z };
                case SOUTH:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z - 1 };
                case WEST:
                    return glm::vec3 { _camera.getPosition().x + 1, _camera.getPosition().y, _camera.getPosition().z };
            }

        case WEST:
            switch (cameraDirection)
            {
                case NORTH:
                    return glm::vec3 { _camera.getPosition().x - 1, _camera.getPosition().y, _camera.getPosition().z };
                case EAST:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z - 1 };
                case SOUTH:
                    return glm::vec3 { _camera.getPosition().x + 1, _camera.getPosition().y, _camera.getPosition().z };
                case WEST:
                    return glm::vec3 { _camera.getPosition().x, _camera.getPosition().y, _camera.getPosition().z + 1 };
            }

        default:return _camera.getPosition();
    }
}

