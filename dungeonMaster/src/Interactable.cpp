#include "../include/Interactable.hpp"
#include "../include/Utils.hpp"

Interactable::Interactable(const glm::vec3 &position, DirectionType directionType)
        : _position(position)
        , _directionType(directionType) {}

bool Interactable::isClicked(const glm::vec3 &clickPosition) const
{
    return Utils::cmpNextPosAndPos(_position, clickPosition);
}


