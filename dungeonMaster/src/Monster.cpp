#include "../include/Monster.hpp"
#include "../include/Utils.hpp"

Monster::Monster(MonsterType type, const glm::vec3 &position, const DirectionType &directionType)
        : _type(type)
        , _modelType(getModelTypeFromMonsterType(type))
        , Character(getHealthFromMonsterType(type), getAttackFromMonsterType(type), getMoneyFromMonsterType(type),
                    position, directionType)
{
}

ModelType Monster::getModelTypeFromMonsterType(MonsterType monsterType)
{
    switch (monsterType)
    {
        case ARMOGOHMA:return MONSTER_01_MODEL;
        case KING_BOO:return MONSTER_02_MODEL;
        case DARKRAI:return MONSTER_03_MODEL;

        default: return MONSTER_01_MODEL;
    }
}

unsigned int Monster::getHealthFromMonsterType(MonsterType type)
{
    switch (type)
    {
        case ARMOGOHMA:return HEALTH_ARMOGOHMA;
        case KING_BOO:return HEALTH_KING_BOO;
        case DARKRAI:return HEALTH_DARKRAI;

        default: return 0;
    }
}

unsigned int Monster::getAttackFromMonsterType(MonsterType type)
{
    switch (type)
    {
        case ARMOGOHMA:return ATTACK_ARMOGOHMA;
        case KING_BOO:return ATTACK_KING_BOO;
        case DARKRAI:return ATTACK_DARKRAI;

        default: return 0;
    }
}

unsigned int Monster::getMoneyFromMonsterType(MonsterType type)
{
    switch (type)
    {
        case ARMOGOHMA:return MONEY_ARMOGOHMA;
        case KING_BOO:return MONEY_KING_BOO;
        case DARKRAI:return MONEY_DARKRAI;

        default: return 0;
    }
}

bool Monster::canAttackPlayer(const glm::vec3 &playerPosition)
{
    // If monster is next to player
    if ((Utils::cmpff(playerPosition.x, getPosition().x) && Utils::cmpff(abs(playerPosition.z - getPosition().z), 1.f)))
    {
        if (playerPosition.z < getPosition().z)
        {
            return getDirectionType() == DirectionType::NORTH;
        }
        else
        {
            return getDirectionType() == DirectionType::SOUTH;
        }
    }

    else if ((Utils::cmpff(playerPosition.z, getPosition().z) &&
              Utils::cmpff(abs(playerPosition.x - getPosition().x), 1.f)))
    {
        if (playerPosition.x < getPosition().x)
        {
            return getDirectionType() == DirectionType::WEST;
        }
        else
        {
            return getDirectionType() == DirectionType::EAST;
        }
    }

    return false;
}

bool Monster::isNextPositionWater(const glm::vec3 &nextPosition,
                                  const std::vector<std::vector<MapElement>> &map)
{
    return map[Utils::floatToAbsInt(nextPosition.z)][Utils::floatToAbsInt(nextPosition.x)] == WATER;
}

void Monster::moveIfGoodDirectionAndNotWater(const DirectionType &nextDirection,
                                             const std::vector<std::vector<MapElement>> &map)
{
    if (getDirectionType() != nextDirection)
    {
        setDirectionType(nextDirection);
    }

    else
    {
        glm::vec3 nextPosition = Utils::getNextPosition(getPosition(), getDirectionType(), DirectionType::NORTH);
        if (!isNextPositionWater(nextPosition, map))
        {
            setPosition(nextPosition);
        }
    }
}

bool Monster::update(Player &player, const std::vector<std::vector<MapElement>> &map,
                     std::vector<std::unique_ptr<Monster>> &monsters,
                     std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    glm::vec3 playerPosition  = player.getPosition();
    glm::vec3 monsterPosition = getPosition();

    if (canAttackPlayer(playerPosition))
    {
        if (player.loseHealth(getAttack()))
        {
            return true;
        }
    }


    else if (Utils::cmpff(playerPosition.x, monsterPosition.x))
    {
        if (isPathWalkableVertically(playerPosition, monsterPosition, map, monsters, interactableObjects))
        {
            if (playerPosition.z < monsterPosition.z)
            {
                moveIfGoodDirectionAndNotWater(DirectionType::NORTH, map);
            }
            else
            {
                moveIfGoodDirectionAndNotWater(DirectionType::SOUTH, map);
            }
        }
    }

    else if (Utils::cmpff(playerPosition.z, monsterPosition.z))
    {
        if (isPathWalkableHorizontally(playerPosition, monsterPosition, map, monsters, interactableObjects))
        {
            if (playerPosition.x < monsterPosition.x)
            {
                moveIfGoodDirectionAndNotWater(DirectionType::WEST, map);
            }
            else
            {
                moveIfGoodDirectionAndNotWater(DirectionType::EAST, map);
            }
        }
    }

    return false;
}

std::vector<glm::vec3> Monster::getInteractablesPos(std::vector<std::unique_ptr<Monster>> &monsters,
                                                    std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<glm::vec3> interactablesPos;

    for (auto &monster: monsters)
    {
        if (monster != nullptr)
        {
            if (monster->getPosition() == getPosition())
            {
                continue;
            }

            interactablesPos.push_back(monster->getPosition());
        }
    }

    for (auto &interactableObject: interactableObjects)
    {
        if (interactableObject != nullptr)
        {
            interactablesPos.push_back(interactableObject->getPosition());
        }
    }

    return interactablesPos;
}

bool Monster::isPathWalkableVertically(const glm::vec3 &playerPosition, const glm::vec3 &monsterPosition,
                                       const std::vector<std::vector<MapElement>> &map,
                                       std::vector<std::unique_ptr<Monster>> &monsters,
                                       std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<glm::vec3> interactablesPos = getInteractablesPos(monsters, interactableObjects);
    int                    x                = Utils::floatToAbsInt(monsterPosition.x);
    int                    start;
    int                    end;

    if (abs(playerPosition.z) < abs(monsterPosition.z))
    {
        start = Utils::floatToAbsInt(playerPosition.z);
        end   = Utils::floatToAbsInt(monsterPosition.z);
    }
    else
    {
        start = Utils::floatToAbsInt(monsterPosition.z);
        end   = Utils::floatToAbsInt(playerPosition.z);
    }

    for (int i = start; i < end; ++i)
    {
        if (map[i][x] == MapElement::WALL)
        {
            return false;
        }

        for (const auto &interactablePos: interactablesPos)
        {
            if (x == Utils::floatToAbsInt(interactablePos.x) && i == Utils::floatToAbsInt(interactablePos.z))
            {
                return false;
            }
        }
    }

    return true;
}

bool Monster::isPathWalkableHorizontally(const glm::vec3 &playerPosition, const glm::vec3 &monsterPosition,
                                         const std::vector<std::vector<MapElement>> &map,
                                         std::vector<std::unique_ptr<Monster>> &monsters,
                                         std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<glm::vec3> interactablesPos = getInteractablesPos(monsters, interactableObjects);
    int                    z                = Utils::floatToAbsInt(monsterPosition.z);
    int                    start;
    int                    end;

    if (abs(playerPosition.x) < abs(monsterPosition.x))
    {
        start = Utils::floatToAbsInt(playerPosition.x);
        end   = Utils::floatToAbsInt(monsterPosition.x);
    }
    else
    {
        start = Utils::floatToAbsInt(monsterPosition.x);
        end   = Utils::floatToAbsInt(playerPosition.x);
    }

    for (int i = start; i < end; ++i)
    {
        if (map[z][i] == MapElement::WALL || map[z][i] == MapElement::WATER)
        {
            return false;
        }

        for (const auto &interactablePos: interactablesPos)
        {
            if (i == Utils::floatToAbsInt(interactablePos.x) && z == Utils::floatToAbsInt(interactablePos.z))
            {
                return false;
            }
        }
    }

    return true;
}

