#include "../include/Character.hpp"
#include "../include/Utils.hpp"

Character::Character(unsigned int health, unsigned int attack, int defense, unsigned int money,
                     const glm::vec3 &position,
                     const DirectionType &directionType)
        : _health(health)
        , _attack(attack)
        , _defense(defense)
        , _money(money)
        , Interactable(position, directionType) {}

bool Character::loseHealth(int damage)
{
    _health -= std::max(damage - _defense, 0);
    return _health <= 0;
}

void Character::modelHasAttacked()
{
    currentNbFrameAttacking++;
    if (currentNbFrameAttacking >= NB_FRAME_TOTAL_FOR_ATTACK)
    {
        currentNbFrameAttacking = 0;
        _isAttacking            = false;
    }
}
