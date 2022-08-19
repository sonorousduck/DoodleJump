#pragma once

#include "entities/Entity.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>
#include <unordered_set>

namespace entities
{
    std::shared_ptr<Entity> createLocalPlayer(std::string textureFile, sf::Vector2f viewSize, sf::Vector2f position, float size, std::unordered_set<std::shared_ptr<sf::Texture>>& textures);
}