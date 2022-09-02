#pragma once
#include "entities/Entity.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "components/RectangularCollider.hpp"
#include <components/Input.hpp>
#include "components/RigidBody.hpp"


#include <memory>
#include <string>
#include <unordered_set>


namespace entities
{
    std::shared_ptr<Entity> createTestEntity(std::string string, sf::Color color, sf::Color outlineColor, std::uint8_t size, sf::Vector2f position, float outlineThickness = 0, float rotation = 0.0f);
}