#include "../include/InventoryCoordinates.hpp"


InventoryCoordinates::InventoryCoordinates(unsigned int windowWidth, unsigned int windowHeight)
        : _windowWidth(windowWidth)
        , _windowHeight(windowHeight) {}

std::pair<InventoryCoordinatesType, unsigned int> InventoryCoordinates::getInventoryCoordinatesType(
        const glm::vec2 &mousePosition)
{
    if (isInInventory(mousePosition))
    {
        if (isFirstItem(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::ITEM, 0);
        }

        else if (isSecondItem(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::ITEM, 1);
        }

        else if (isThirdItem(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::ITEM, 2);
        }

        else if (isFourthItem(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::ITEM, 3);
        }

        else if (isFifthItem(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::ITEM, 4);
        }

        else if (isSixthItem(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::ITEM, 5);
        }

        else if (isFirstWeapon(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::WEAPON, 0);
        }

        else if (isSecondWeapon(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::WEAPON, 1);
        }

        else if (isThirdWeapon(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::WEAPON, 2);
        }

        else if (isLeftArrow(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::LEFT_ARROW, 0);
        }

        else if (isRightArrow(mousePosition))
        {
            return std::make_pair(InventoryCoordinatesType::RIGHT_ARROW, 1);
        }
    }

    return std::make_pair(InventoryCoordinatesType::NOT_INVENTORY, 0);
}

bool InventoryCoordinates::isInCoords(float x1, float x2, float y1, float y2, const glm::vec2 &mousePosition)
{
    return mousePosition.x >= (x1 * (float) _windowWidth) && mousePosition.x <= (x2 * (float) _windowWidth) &&
           mousePosition.y >= (y1 * (float) _windowHeight) && mousePosition.y <= (y2 * (float) _windowHeight);
}

bool InventoryCoordinates::isInInventory(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_FIRST_COLUMN_LEFT_BORDER, WEAPONS_COLUMN_RIGHT_BORDER,
                      INVENTORY_FIRST_ROW_TOP_BORDER, INVENTORY_THIRD_ROW_BOTTOM_BORDER, mousePosition);
}


bool InventoryCoordinates::isFirstItem(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_FIRST_COLUMN_LEFT_BORDER, ITEMS_FIRST_COLUMN_RIGHT_BORDER,
                      INVENTORY_FIRST_ROW_TOP_BORDER, INVENTORY_FIRST_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isSecondItem(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_SECOND_COLUMN_LEFT_BORDER, ITEMS_SECOND_COLUMN_RIGHT_BORDER,
                      INVENTORY_FIRST_ROW_TOP_BORDER, INVENTORY_FIRST_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isThirdItem(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_FIRST_COLUMN_LEFT_BORDER, ITEMS_FIRST_COLUMN_RIGHT_BORDER,
                      INVENTORY_SECOND_ROW_TOP_BORDER, INVENTORY_SECOND_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isFourthItem(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_SECOND_COLUMN_LEFT_BORDER, ITEMS_SECOND_COLUMN_RIGHT_BORDER,
                      INVENTORY_SECOND_ROW_TOP_BORDER, INVENTORY_SECOND_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isFifthItem(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_FIRST_COLUMN_LEFT_BORDER, ITEMS_FIRST_COLUMN_RIGHT_BORDER,
                      INVENTORY_THIRD_ROW_TOP_BORDER, INVENTORY_THIRD_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isSixthItem(const glm::vec2 &mousePosition)
{
    return isInCoords(ITEMS_SECOND_COLUMN_LEFT_BORDER, ITEMS_SECOND_COLUMN_RIGHT_BORDER,
                      INVENTORY_THIRD_ROW_TOP_BORDER, INVENTORY_THIRD_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isFirstWeapon(const glm::vec2 &mousePosition)
{
    return isInCoords(WEAPONS_COLUMN_LEFT_BORDER, WEAPONS_COLUMN_RIGHT_BORDER,
                      INVENTORY_FIRST_ROW_TOP_BORDER, INVENTORY_FIRST_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isSecondWeapon(const glm::vec2 &mousePosition)
{
    return isInCoords(WEAPONS_COLUMN_LEFT_BORDER, WEAPONS_COLUMN_RIGHT_BORDER,
                      INVENTORY_SECOND_ROW_TOP_BORDER, INVENTORY_SECOND_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isThirdWeapon(const glm::vec2 &mousePosition)
{
    return isInCoords(WEAPONS_COLUMN_LEFT_BORDER, WEAPONS_COLUMN_RIGHT_BORDER,
                      INVENTORY_THIRD_ROW_TOP_BORDER, INVENTORY_THIRD_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isLeftArrow(const glm::vec2 &mousePosition)
{
    return isInCoords(LEFT_ARROW_LEFT_BORDER, LEFT_ARROW_RIGHT_BORDER,
                      INVENTORY_FIRST_ROW_TOP_BORDER, INVENTORY_THIRD_ROW_BOTTOM_BORDER, mousePosition);
}

bool InventoryCoordinates::isRightArrow(const glm::vec2 &mousePosition)
{
    return isInCoords(RIGHT_ARROW_LEFT_BORDER, RIGHT_ARROW_RIGHT_BORDER,
                      INVENTORY_FIRST_ROW_TOP_BORDER, INVENTORY_THIRD_ROW_BOTTOM_BORDER, mousePosition);
}




