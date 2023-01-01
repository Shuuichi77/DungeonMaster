#pragma once

#include "Character.hpp"
#include "ModelType.hpp"
#include "MapElement.hpp"
#include "Player.hpp"
#include "InteractableObject.hpp"
#include <vector>

enum MonsterType
{
    ARMOGOHMA,
    DARKRAI,
    KING_BOO
};

class Monster : public Character
{
private:
    static constexpr const unsigned int HEALTH_KING_BOO = 10;
    static constexpr const unsigned int ATTACK_KING_BOO = 2;
    static constexpr const unsigned int MONEY_KING_BOO  = 10;

    static constexpr const unsigned int HEALTH_ARMOGOHMA = 15;
    static constexpr const unsigned int ATTACK_ARMOGOHMA = 2;
    static constexpr const unsigned int MONEY_ARMOGOHMA  = 15;

    static constexpr const unsigned int HEALTH_DARKRAI = 20;
    static constexpr const unsigned int ATTACK_DARKRAI = 2;
    static constexpr const unsigned int MONEY_DARKRAI  = 20;

    const MonsterType _type;

    const ModelType _modelType;

    static ModelType getModelTypeFromMonsterType(MonsterType monsterType);

    static unsigned int getHealthFromMonsterType(MonsterType type);

    static unsigned int getAttackFromMonsterType(MonsterType type);

    static unsigned int getMoneyFromMonsterType(MonsterType type);

    bool canAttackPlayer(const glm::vec3 &playerPosition);

    bool update(Player &player, const std::vector<std::vector<MapElement>> &map,
                std::vector<std::unique_ptr<Monster>> &monsters,
                std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    std::vector<glm::vec3> getInteractablesPos(std::vector<std::unique_ptr<Monster>> &monsters,
                                               std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    bool isPathWalkableVertically(int x, int starting, int ending, const std::vector<std::vector<MapElement>> &map,
                                  std::vector<std::unique_ptr<Monster>> &monsters,
                                  std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    bool
    isPathWalkableHorizontally(int z, float starting, float ending, const std::vector<std::vector<MapElement>> &map,
                               std::vector<std::unique_ptr<Monster>> &monsters,
                               std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    friend class CharacterManager;

public:
    ~Monster() override = default;

    explicit Monster(MonsterType type, const glm::vec3 &position, const DirectionType &directionType);

    ModelType getModelType() const override { return _modelType; }


};
