#pragma once

#include <unordered_map>
#include <vector>
#include "Character.hpp"
#include "Weapon.hpp"
#include "ModelTransformations.hpp"
#include "Music.hpp"

#include <memory>

class Player : public Character
{
private:
    static constexpr const unsigned int MAX_ITEMS_SIZE      = 6;
    static constexpr const unsigned int MAX_WEAPONS_SIZE    = 3;
    static constexpr const unsigned int BASE_HEALTH_PLAYER  = 10;
    static constexpr const unsigned int BASE_DEFENSE_PLAYER = 1;
    static constexpr const WeaponType   FIRST_WEAPON_TYPE   = WeaponType::WOODEN_SWORD;

    unsigned int _nbKeys           = 0;
    unsigned int _nbMonstersKilled = 0;

    std::vector<ItemType>                _items;
    std::vector<std::unique_ptr<Weapon>> _weapons;
    std::vector<WeaponType>              _weaponsTypes;

    bool addItem(ItemType type);

    void addHealth(unsigned int health) override;

    void addMoney(int money) { _money += money; }

    void addKey();

    bool useKey();

    friend class InteractableObject;

    friend class Monster;

    friend class CharacterManager;

    friend class CameraManager;

public:
    ~Player() override = default;

    explicit Player(const glm::vec3 &position, const DirectionType &directionType);

    ModelType getModelType() const override { return ModelType::NONE; }

    unsigned int getNbKeys() const { return _nbKeys; }

    unsigned int getAttack() const override;

    bool loseHealth(int damage) override;

    void useItem(unsigned int index, Music music);

    void changeWeapon(unsigned int index);

    bool addWeapon(WeaponType weaponType);

    void addMonsterKilled() { _nbMonstersKilled++; }

    unsigned int getNbMonstersKilled() const { return _nbMonstersKilled; }

    const std::unique_ptr<Weapon> &getCurrentWeapon() const;

    std::vector<WeaponType> getWeaponsTypes() const { return _weaponsTypes; }

    const std::vector<ItemType> &getItems() const { return _items; }

    static ModelType getModelTypeFromItemType(ItemType type);

    bool hasEnoughMoneyAndMonsterKilled(unsigned int money, unsigned int nbMonstersKilled) const;
};
