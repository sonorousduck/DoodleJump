#pragma once

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstdint>
#include <memory>

namespace components
{
	class AnimatedSprite : public PolymorphicComparable<Component, AnimatedSprite>
    {
      public:
        AnimatedSprite(std::shared_ptr<sf::Texture> tecture, std::uint8_t spriteCount, std::chrono::microseconds spriteTime, sf::Color spriteColor)
    
    };
}