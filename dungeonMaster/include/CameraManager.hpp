#pragma one

#include <glm/glm.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <chrono>
#include <vector>
#include "DirectionType.hpp"
#include "FreeflyCamera.hpp"
#include "MapElement.hpp"
#include "Monster.hpp"
#include "InteractableObject.hpp"

class CameraManager
{
private:
    FreeflyCamera            &_camera;
    glimac::SDLWindowManager &_windowManager;
    bool                     &_gameWin;

    bool isOutOfMap(int i, int j, const std::vector<std::vector<MapElement>> &map);

    bool canMoveTowardDirection(DirectionType nextMovementDirectionType,
                                const std::vector<std::vector<MapElement>> &map,
                                const std::vector<std::unique_ptr<Monster>> &monsters,
                                const std::vector<std::unique_ptr<InteractableObject>> &_interactableObjects);


public:
    CameraManager(FreeflyCamera &camera, glimac::SDLWindowManager &windowManager,
                  bool &gameWin);

    void moveCamera(const SDL_MouseButtonEvent &button,
                    const std::vector<std::vector<MapElement>> &map,
                    const std::vector<std::unique_ptr<Monster>> &monsters,
                    const std::vector<std::unique_ptr<InteractableObject>> &_interactableObjects,
                    Player &player);
};