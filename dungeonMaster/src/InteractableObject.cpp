#include "../include/InteractableObject.hpp"
#include "../include/Utils.hpp"


InteractableObject::InteractableObject(InteractableObjectType type, const glm::vec3 &position,
                                       const DirectionType &directionType, unsigned int qty)
        : Interactable(position, directionType)
        , _type(type)
        , _qty(qty)
        , _modelType(getModelTypeFromInteractableObjectType(type)) {}

ModelType InteractableObject::getModelTypeFromInteractableObjectType(InteractableObjectType type)
{
    switch (type)
    {
        case INTERACTABLE_DOOR: //
            return ModelType::DOOR_MODEL;

        case INTERACTABLE_CHEST_MONEY: //
        case INTERACTABLE_CHEST_KEY: //
        case INTERACTABLE_CHEST_MILK: //
        case INTERACTABLE_CHEST_HEALTH_POTION: //
        case INTERACTABLE_CHEST_FAIRY: //
        case INTERACTABLE_CHEST_WEAPON_01: //
        case INTERACTABLE_CHEST_WEAPON_02: //
        case INTERACTABLE_CHEST_WEAPON_03: //
            return ModelType::CHEST_MODEL;

        default:return ModelType::NONE;
    }
}

bool InteractableObject::addObjectsToPlayer(Player &player, const InteractableObjectType &interactableObjectType) const
{
    for (int i = 0; i < _qty; ++i)
    {
        switch (interactableObjectType)
        {
            case INTERACTABLE_CHEST_KEY:player.addKey();
                break;

            case INTERACTABLE_CHEST_MILK:player.addItem(MILK);
                break;

            case INTERACTABLE_CHEST_HEALTH_POTION:player.addItem(HEALTH_POTION);
                break;

            case INTERACTABLE_CHEST_FAIRY:player.addItem(FAIRY);
                break;

            default:std::cerr << "Unknown type or type can't be added multiple times" << std::endl;
                return false;
        }
    }

    return true;
}

bool InteractableObject::interactWithPlayer(Player &player)
{
    switch (_type)
    {
        case INTERACTABLE_DOOR: //
            return player.useKey();

        case INTERACTABLE_CHEST_MONEY: //
            player.addMoney(_qty);
            return true;

        case INTERACTABLE_CHEST_FAIRY: //
        case INTERACTABLE_CHEST_HEALTH_POTION: //
        case INTERACTABLE_CHEST_MILK: //
        case INTERACTABLE_CHEST_KEY: //
            return addObjectsToPlayer(player, _type);

        case INTERACTABLE_CHEST_WEAPON_01: //
            player.addWeapon(WOODEN_SWORD);
            return true;

        case INTERACTABLE_CHEST_WEAPON_02: //
            player.addWeapon(ROYAL_SWORD);
            return true;

        case INTERACTABLE_CHEST_WEAPON_03: //
            player.addWeapon(MASTER_SWORD);
            return true;
    }

    return false;
}

InteractableObjectType InteractableObject::getInteractableObjectTypeFromName(const std::string &name)
{
    if (name == "MONEY")
    {
        return INTERACTABLE_CHEST_MONEY;
    }
    else if (name == "KEY")
    {
        return INTERACTABLE_CHEST_KEY;
    }
    else if (name == "MILK")
    {
        return INTERACTABLE_CHEST_MILK;
    }
    else if (name == "POTION")
    {
        return INTERACTABLE_CHEST_HEALTH_POTION;
    }
    else if (name == "FAIRY")
    {
        return INTERACTABLE_CHEST_FAIRY;
    }
    else if (name == "WOODENSWORD")
    {
        return INTERACTABLE_CHEST_WEAPON_01;
    }
    else if (name == "ROYALSWORD")
    {
        return INTERACTABLE_CHEST_WEAPON_02;
    }
    else if (name == "MASTERSWORD")
    {
        return INTERACTABLE_CHEST_WEAPON_03;
    }
    else
    {
        return UNKNOWN_INTERACTABLE_OBJECT_TYPE;
    }
}

void InteractableObject::createInteractableObject(const std::string &string,
                                                  std::vector<std::unique_ptr<InteractableObject>> &interactableObjects)
{
    std::vector<std::string> splitString = Utils::splitStringByDelimiter(string, ":");
    if (splitString.size() != 5 && splitString.size() != 6)
    {
        std::cerr << "Error while reading the dungeon file: wrong number of arguments for chest: " << string
                << std::endl;
        exit(EXIT_FAILURE);
    }

    int                    pos_i         = std::stoi(splitString[1]);
    int                    pos_j         = std::stoi(splitString[2]);
    InteractableObjectType chestType     = InteractableObject::getInteractableObjectTypeFromName(splitString[3]);
    DirectionType          directionType = Utils::getDirectionTypeFromString(splitString[4]);
    unsigned int           qty           = 1;
    if (splitString.size() == 6)
    {
        qty = std::stoi(splitString[5]);
    }

    if (chestType == UNKNOWN_INTERACTABLE_OBJECT_TYPE)
    {
        std::cerr << "Error while reading the dungeon file: unknown chest type" << std::endl;
        exit(EXIT_FAILURE);
    }

    else
    {
        interactableObjects.emplace_back(
                Utils::make_unique<InteractableObject>(
                        chestType,
                        glm::vec3(pos_j, 0, -pos_i),
                        directionType,
                        qty));
    }
}




