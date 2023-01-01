#include "../include/Character.hpp"
#include "../include/Utils.hpp"

Character::Character(unsigned int health, unsigned int attack, unsigned int money, const glm::vec3 &position,
                     const DirectionType &directionType)
        : _health(health)
        , _attack(attack)
        , _money(money)
        , Interactable(position, directionType) {}

void Character::move(const DirectionType &nextDirectionType)
{
    setPosition(Utils::getNextPosition(getPosition(), getDirectionType(), nextDirectionType));
}