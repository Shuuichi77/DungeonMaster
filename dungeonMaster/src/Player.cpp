#include "../include/Player.hpp"
#include "../include/Utils.hpp"
#include <memory>

Player::Player(const glm::vec3 &position, const DirectionType &directionType)
        : Character(BASE_HEALTH_PLAYER, 0, BASE_DEFENSE_PLAYER, 0, position, directionType)
{
    addWeapon(FIRST_WEAPON_TYPE);
}

void Player::use(ItemType type)
{
    switch (type)
    {
        case MILK:addHealth(2);
            break;
        case HEALTH_POTION:addHealth(5);
            break;
        case FAIRY:addHealth(BASE_HEALTH_PLAYER);
            break;
    }

}

void Player::addHealth(unsigned int health)
{
    if (_health < BASE_HEALTH_PLAYER)
    {
        unsigned int baseHealth = BASE_HEALTH_PLAYER;
        _health = std::min(_health + health, baseHealth);
    }
}

void Player::changeWeapon(unsigned int index)
{
    if (index != 0 && index < _weapons.size())
    {
        if (_weapons[0] != nullptr && _weapons[index] != nullptr)
        {
            std::swap(_weapons[0], _weapons[index]);
            std::swap(_weaponsTypes[0], _weaponsTypes[index]);
        }
    }
}

bool Player::addWeapon(WeaponType weaponType)
{
    if (_weapons.size() < MAX_WEAPONS_SIZE)
    {
        _weapons.emplace_back(Utils::make_unique<Weapon>(weaponType));
        _weaponsTypes.push_back(weaponType);
        return true;
    }

    return false;
}

bool Player::addItem(ItemType type)
{
    if (_items.size() < MAX_ITEMS_SIZE)
    {
        _items.push_back(type);
        return true;
    }

    return false;
}

void Player::addKey()
{
    _nbKeys++;
}

void Player::useItem(unsigned int index)
{
    if (_items.size() > index)
    {
        use(_items[index]);
        _items.erase(_items.begin() + index);
    }
}

bool Player::useKey()
{
    if (_nbKeys > 0)
    {
        _nbKeys--;
        return true;
    }

    return false;
}

ModelType Player::getModelTypeFromItemType(ItemType type)
{
    switch (type)
    {
        case MILK:return ModelType::MILK_MODEL;
        case HEALTH_POTION:return ModelType::HEALTH_POTION_MODEL;
        case FAIRY:return ModelType::FAIRY_MODEL;
        default: return ModelType::NONE;
    }
}

unsigned Player::getAttack() const
{
    assert(!_weapons.empty() && "Player has no weapon");
    assert(_weapons[0] != nullptr && "Player has no weapon");

    return _weapons[0]->getAttack();
}

const std::unique_ptr<Weapon> &Player::getCurrentWeapon() const
{
    assert(!_weapons.empty() && "Player has no weapon");
    assert(_weapons[0] != nullptr && "Player has no weapon");

    return _weapons[0];
}

bool Player::loseHealth(int damage)
{
    _health -= std::max(damage - _defense, 0);
    if (_health <= 0)
    {
        for (auto it = _items.begin(); it != _items.end(); ++it)
        {
            if (*it == FAIRY)
            {
                _health = BASE_HEALTH_PLAYER;
                it      = _items.erase(it);
                return false;
            }
        }

        return true;
    }

    return false;
}

bool Player::hasEnoughMoneyAndMonsterKilled(unsigned int money, unsigned int nbMonstersKilled) const
{
    return _money >= money && _nbMonstersKilled >= nbMonstersKilled;
}








