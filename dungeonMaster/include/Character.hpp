#pragma once


#include <glm/glm.hpp>
#include "Interactable.hpp"
#include <iostream>

class Character : public Interactable
{

protected:
    int          _health;
    int          _money;
    unsigned int _attack;

public:
    ~Character() override = default;

    Character(unsigned int health, unsigned int attack, unsigned int money, const glm::vec3 &position,
              const DirectionType &directionType);

    unsigned int getHealth() const { return _health; }

    int getMoney() const { return _money; }

    bool loseHealth(unsigned int damage)
    {
        _health -= damage;
        return _health <= 0;
    }

    virtual unsigned int getAttack() const { return _attack; }

    virtual void addHealth(unsigned int health)
    {
        _health += health;
    }
};