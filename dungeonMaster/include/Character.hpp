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
    int          _defense;

public:
    ~Character() override = default;

    Character(unsigned int health, unsigned int attack, int _defense, unsigned int money,
              const glm::vec3 &position, const DirectionType &directionType);

    unsigned int getHealth() const { return _health; }

    int getMoney() const { return _money; }

    virtual void addHealth(unsigned int health) { _health += health; }

    virtual unsigned int getAttack() const { return _attack; }

    virtual bool loseHealth(int damage);
};