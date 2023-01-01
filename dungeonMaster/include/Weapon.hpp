#pragma once

#include "ModelType.hpp"

enum WeaponType
{
    WOODEN_SWORD,
    ROYAL_SWORD,
    MASTER_SWORD,
};

class Weapon
{
private:
    static constexpr const unsigned int BASE_ATTACK_WOODEN_SWORD = 5;
    static constexpr const unsigned int BASE_ATTACK_ROYAL_SWORD  = 10;
    static constexpr const unsigned int BASE_ATTACK_MASTER_SWORD = 20;

    unsigned int _attack;
    WeaponType   _weaponType;

public:
    explicit Weapon(WeaponType type);

    unsigned int getAttack() const { return _attack; }

    WeaponType getWeaponType() const { return _weaponType; }

    static ModelType getInventoryModelTypeFromWeaponType(WeaponType weaponType);

    static unsigned int getAttackFromWeaponType(WeaponType type);

    static ModelType getModelTypeFromWeaponType(WeaponType weaponType);
};