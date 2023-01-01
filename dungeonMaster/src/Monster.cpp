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

bool Monster::update(Player &player, const std::vector<std::vector<MapElement>> &map,
                     std::vector<std::unique_ptr<Monster>> &monsters,
                     std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::cout << "update " << _type << std::endl;
    glm::vec3 playerPosition  = player.getPosition();
    glm::vec3 monsterPosition = getPosition();

    if (canAttackPlayer(playerPosition))
    {
        if (player.loseHealth(getAttack()))
        {
            return true;
        }
    }


//    else if (Utils::cmpff(playerPosition.x, monsterPosition.x))
//    {
//        std::cout << "SAME X for " << _type << std::endl;
//        if (isPathWalkableVertically((int) playerPosition.x, (int) playerPosition.z, (int) monsterPosition.z, map,
//                                     monsters,
//                                     interactableObjects))
//        {
//            std::cout << "isPathWalkableVertically for " << _type << std::endl;
//            if (playerPosition.z < monsterPosition.z)
//            {
////                if (getDirectionType() == DirectionType::NORTH)
////                {
////                    move(DirectionType::NORTH);
////                }
////                else
////                {
////                    setDirectionType(DirectionType::NORTH);
////                }
//            }
//            else
//            {
////                if (getDirectionType() == DirectionType::SOUTH)
////                {
////                    move(DirectionType::SOUTH);
////                }
////                else
////                {
////                    setDirectionType(DirectionType::SOUTH);
////                }
//            }
//        }
//    }
////
////    else if (Utils::cmpff(playerPosition.z, monsterPosition.z))
////    {
////        std::cout << "SAME Z for " << _type << std::endl;
////        if (isPathWalkableHorizontally(playerPosition.z, playerPosition.x, monsterPosition.x, map, monsters,
////                                       interactableObjects))
////        {
////            if (playerPosition.x < monsterPosition.x)
////            {
////                if (getDirectionType() == DirectionType::WEST)
////                {
////                    move(DirectionType::WEST);
////                }
////                else
////                {
////                    setDirectionType(DirectionType::WEST);
////                }
////            }
////            else
////            {
////                if (getDirectionType() == DirectionType::EAST)
////                {
////                    move(DirectionType::EAST);
////                }
////                else
////                {
////                    setDirectionType(DirectionType::EAST);
////                }
////            }
////        }
////    }

    return false;
}

std::vector<glm::vec3> Monster::getInteractablesPos(std::vector<std::unique_ptr<Monster>> &monsters,
                                                    std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<glm::vec3> interactablesPos;

    for (auto &monster: monsters)
    {
        if (monster->getPosition() == getPosition())
        {
            continue;
        }

        interactablesPos.push_back(monster->getPosition());
    }

    for (auto &interactableObject: interactableObjects)
    {
        interactablesPos.push_back(interactableObject->getPosition());
    }

    return interactablesPos;
}

bool
Monster::isPathWalkableVertically(int x, int starting, int ending, const std::vector<std::vector<MapElement>> &map,
                                  std::vector<std::unique_ptr<Monster>> &monsters,
                                  std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<glm::vec3> interactablesPos = getInteractablesPos(monsters, interactableObjects);

    starting = abs(starting);
    ending   = abs(ending);

    if (starting > ending)
    {
        int tmp = starting;
        starting = ending;
        ending   = tmp;
    }

    for (int i = abs(starting); i < abs(ending); ++i)
    {
        if (map[i][abs(x)] == MapElement::WALL)
        {
            return false;
        }

        for (auto &interactablePos: interactablesPos)
        {
            std::cout << (int) abs(interactablePos.z) << " vs " << i << std::endl;
            if ((int) abs(interactablePos.z) == i)
            {
                return false;
            }
        }
    }

    return true;
}

bool Monster::isPathWalkableHorizontally(int z, float starting, float ending,
                                         const std::vector<std::vector<MapElement>> &map,
                                         std::vector<std::unique_ptr<Monster>> &monsters,
                                         std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<glm::vec3> interactablePos = getInteractablesPos(monsters, interactableObjects);

    for (int i = (int) starting; i < (int) ending; ++(i))
    {
//        if (map[z][i] == MapElement::WALL)
//        {
//            return false;
//        }

        for (auto &pos: interactablePos)
        {
            if ((int) pos.x == i)
            {
                return false;
            }
        }
    }

    return true;
}

