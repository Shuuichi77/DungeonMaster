#pragma once

#include <glm/glm.hpp>
#include "DirectionType.hpp"
#include "ModelType.hpp"

class Interactable
{
private:
    glm::vec3     _position;
    DirectionType _directionType;

protected:
    explicit Interactable(const glm::vec3 &position, DirectionType directionType);

    virtual ~Interactable() = default;

    void setPosition(const glm::vec3 &position) { _position = position; }

    void setDirectionType(DirectionType directionType) { _directionType = directionType; }

    virtual ModelType getModelType() const = 0;

public:
    glm::vec3 getPosition() const { return _position; }

    DirectionType getDirectionType() const { return _directionType; }

    bool isClicked(const glm::vec3 &clickPosition) const;
};