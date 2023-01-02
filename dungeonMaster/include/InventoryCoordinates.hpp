#pragma once

#include <glm/glm.hpp>
#include <iostream>

enum InventoryCoordinatesType
{
    NOT_INVENTORY,
    ITEM,
    WEAPON,
    LEFT_ARROW,
    RIGHT_ARROW,
};

class InventoryCoordinates
{
private:
    static constexpr const float ITEMS_FIRST_COLUMN_LEFT_BORDER  = 0.07812f;
    static constexpr const float ITEMS_FIRST_COLUMN_RIGHT_BORDER = 0.19f;

    static constexpr const float ITEMS_SECOND_COLUMN_LEFT_BORDER  = 0.2181f;
    static constexpr const float ITEMS_SECOND_COLUMN_RIGHT_BORDER = 0.3287f;

    static constexpr const float LEFT_ARROW_LEFT_BORDER  = 0.375235f;
    static constexpr const float LEFT_ARROW_RIGHT_BORDER = 0.488743f;

    static constexpr const float RIGHT_ARROW_LEFT_BORDER  = 0.515947f;
    static constexpr const float RIGHT_ARROW_RIGHT_BORDER = 0.620075f;

    static constexpr const float WEAPONS_COLUMN_LEFT_BORDER  = 0.669794f;
    static constexpr const float WEAPONS_COLUMN_RIGHT_BORDER = 0.9225f;

    static constexpr const float INVENTORY_FIRST_ROW_TOP_BORDER    = 0.8025f;
    static constexpr const float INVENTORY_FIRST_ROW_BOTTOM_BORDER = 0.8583f;

    static constexpr const float INVENTORY_SECOND_ROW_TOP_BORDER    = 0.8675f;
    static constexpr const float INVENTORY_SECOND_ROW_BOTTOM_BORDER = 0.9216f;

    static constexpr const float INVENTORY_THIRD_ROW_TOP_BORDER    = 0.9316f;
    static constexpr const float INVENTORY_THIRD_ROW_BOTTOM_BORDER = 0.9883f;

    unsigned int _windowWidth;
    unsigned int _windowHeight;

    bool isInCoords(float x1, float x2, float y1, float y2, const glm::vec2 &mousePosition);

    bool isInInventory(const glm::vec2 &mousePosition);

    bool isFirstItem(const glm::vec2 &mousePosition);

    bool isSecondItem(const glm::vec2 &mousePosition);

    bool isThirdItem(const glm::vec2 &mousePosition);

    bool isFourthItem(const glm::vec2 &mousePosition);

    bool isFifthItem(const glm::vec2 &mousePosition);

    bool isSixthItem(const glm::vec2 &mousePosition);

    bool isFirstWeapon(const glm::vec2 &mousePosition);

    bool isSecondWeapon(const glm::vec2 &mousePosition);

    bool isThirdWeapon(const glm::vec2 &mousePosition);

    bool isLeftArrow(const glm::vec2 &mousePosition);

    bool isRightArrow(const glm::vec2 &mousePosition);

public:
    explicit InventoryCoordinates(unsigned int windowWidth, unsigned int windowHeight);

    ~InventoryCoordinates() = default;

    std::pair<InventoryCoordinatesType, unsigned int> getInventoryCoordinatesType(const glm::vec2 &mousePosition);


};