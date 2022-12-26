#pragma one

#include <glm/glm.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "DirectionType.hpp"
#include "FreeflyCamera.hpp"
#include "ObjectType.hpp"

class CameraManager
{
public:
    CameraManager(FreeflyCamera &camera, const glimac::SDLWindowManager &windowManager,
                  const std::vector<std::vector<ObjectType>> &map);

    void moveCamera();

private:
    bool                                               _cameraCanMove = true;
    FreeflyCamera                                      &_camera;
    const std::vector<std::vector<ObjectType>>         &_map;
    glimac::SDLWindowManager                           _windowManager;
    std::chrono::time_point<std::chrono::system_clock> _timeMoved     = std::chrono::system_clock::now();

    bool isOutOfMap(int i, int j);

    bool canMoveTowardDirection(DirectionType nextMovementDirectionType);

    bool canMoveAgain();

    glm::vec3 getNextPosition(DirectionType cameraDirection,
                              DirectionType nextMovementDirectionType);
};