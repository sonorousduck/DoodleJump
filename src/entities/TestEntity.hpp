#pragma once
#include "entities/Entity.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "components/RectangularCollider.hpp"
#include <components/Input.hpp>
#include "components/RigidBody.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "components/Sprite.hpp"
#include <components/Size.hpp>


#include <memory>
#include <string>
#include <unordered_set>


namespace entities
{
    std::shared_ptr<Entity> createTestEntity(std::string textureFile, sf::Vector2f viewSize, sf::Vector2f position, float size, std::unordered_set<std::shared_ptr<sf::Texture>>& textures);
}