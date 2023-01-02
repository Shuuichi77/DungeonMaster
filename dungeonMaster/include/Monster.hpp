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
    KING_BOO,
    UNKNOWN_MONSTER
};

class Monster : public Character
{
private:
    static constexpr const unsigned int HEALTH_KING_BOO  = 10;
    static constexpr const unsigned int ATTACK_KING_BOO  = 2;
    static constexpr const unsigned int DEFENSE_KING_BOO = 1;
    static constexpr const unsigned int MONEY_KING_BOO   = 10;


    static constexpr const unsigned int HEALTH_ARMOGOHMA  = 15;
    static constexpr const unsigned int ATTACK_ARMOGOHMA  = 3;
    static constexpr const unsigned int DEFENSE_ARMOGOHMA = 2;
    static constexpr const unsigned int MONEY_ARMOGOHMA   = 15;

    static constexpr const unsigned int HEALTH_DARKRAI  = 20;
    static constexpr const unsigned int ATTACK_DARKRAI  = 4;
    static constexpr const unsigned int DEFENSE_DARKRAI = 3;
    static constexpr const unsigned int MONEY_DARKRAI   = 20;

    const MonsterType _type;

    const ModelType _modelType;

    static ModelType getModelTypeFromMonsterType(MonsterType monsterType);

    static unsigned int getHealthFromMonsterType(MonsterType type);

    static unsigned int getAttackFromMonsterType(MonsterType type);

    static unsigned int getDefenseFromMonsterType(MonsterType type);

    static unsigned int getMoneyFromMonsterType(MonsterType type);

    bool canAttackPlayer(const glm::vec3 &playerPosition);

    bool update(Player &player, const std::vector<std::vector<MapElement>> &map,
                std::vector<std::unique_ptr<Monster>> &monsters,
                std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    std::vector<glm::vec3> getInteractablesPos(std::vector<std::unique_ptr<Monster>> &monsters,
                                               std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    bool isPathWalkableVertically(const glm::vec3 &playerPosition, const glm::vec3 &monsterPosition,
                                  const std::vector<std::vector<MapElement>> &map,
                                  std::vector<std::unique_ptr<Monster>> &monsters,
                                  std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    bool isPathWalkableHorizontally(const glm::vec3 &playerPosition, const glm::vec3 &monsterPosition,
                                    const std::vector<std::vector<MapElement>> &map,
                                    std::vector<std::unique_ptr<Monster>> &monsters,
                                    std::vector<std::unique_ptr<InteractableObject>> &interactableObjects);

    friend class CharacterManager;

public:
    ~Monster() override = default;

    explicit Monster(MonsterType type, const glm::vec3 &position, const DirectionType &directionType);

    explicit Monster(MonsterType type, const glm::vec3 &position, const DirectionType &directionType, int health,
                     unsigned int attack, int defense, int money);

    ModelType getModelType() const override { return _modelType; }

    static MonsterType getMonsterTypeFromName(const std::string &name);

    static bool isNextPositionWater(const glm::vec3 &nextPosition, const std::vector<std::vector<MapElement>> &map);

    void
    moveIfGoodDirectionAndNotWater(const DirectionType &nextDirection, const std::vector<std::vector<MapElement>> &map);

    static void createMonster(const std::string &string, std::vector<std::unique_ptr<Monster>> &monsters);
};
