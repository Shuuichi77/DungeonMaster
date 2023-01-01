#include "../include/Weapon.hpp"
#include <iostream>

Weapon::Weapon(WeaponType type)
        : _weaponType(type)
        , _attack(getAttackFromWeaponType(type))
{
}

unsigned int Weapon::getAttackFromWeaponType(WeaponType type)
{
    switch (type)
    {
        case WOODEN_SWORD:return BASE_ATTACK_WOODEN_SWORD;
        case ROYAL_SWORD:return BASE_ATTACK_ROYAL_SWORD;
        case MASTER_SWORD:return BASE_ATTACK_MASTER_SWORD;

        default: return 0;
    }
}

ModelType Weapon::getInventoryModelTypeFromWeaponType(WeaponType weaponType)
{
    switch (weaponType)
    {
        case WOODEN_SWORD:return ModelType::WOODEN_SWORD_IN_INVENTORY_MODEL;
        case ROYAL_SWORD:return ModelType::ROYAL_SWORD_IN_INVENTORY_MODEL;
        case MASTER_SWORD:return ModelType::MASTER_SWORD_IN_INVENTORY_MODEL;

        default:std::cerr << "Error: Weapon::getInventoryModelTypeFromWeaponType: unknown weaponType" << std::endl;
            return ModelType::NONE;
    }
}

ModelType Weapon::getModelTypeFromWeaponType(WeaponType weaponType)
{
    switch (weaponType)
    {
        case WOODEN_SWORD:return ModelType::WOODEN_SWORD_MODEL;
        case ROYAL_SWORD:return ModelType::ROYAL_SWORD_MODEL;
        case MASTER_SWORD:return ModelType::MASTER_SWORD_MODEL;
        
        default: std::cerr << "Error: Weapon::getInventoryModelTypeFromWeaponType: unknown weaponType" << std::endl;
            return ModelType::NONE;
    }
}