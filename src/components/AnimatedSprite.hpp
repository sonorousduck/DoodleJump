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
        AnimatedSprite(std::shared_ptr<sf::Texture> texture, std::uint8_t spriteCount, std::chrono::microseconds spriteTime, sf::Color spriteColor) :
            m_spriteCount(spriteCount),
            m_spriteTime(spriteTime),
            m_spriteColor(spriteColor)
        {
            m_sprite = std::make_shared<sf::Sprite>();
            m_sprite->setTexture(*texture);
        }
    
        auto getSprite() { return m_sprite; }
        auto getSpriteCount() { return m_spriteCount; }
        auto getSpriteTime() { return m_spriteTime; }
        auto getSpriteColor() { return m_spriteColor; }
        auto getCurrentSprite() { return m_currentSprite; }
        auto getCurrentSpriteRect()
        {
            int width = (m_sprite->getTexture()->getSize().x / m_spriteCount);
            int left = m_currentSprite * width;
            return sf::IntRect({left, 0, width, static_cast<int>(m_sprite->getTexture()->getSize().y)});
        }

        auto incrementSprite() { m_currentSprite = (m_currentSprite + 1) % m_spriteCount; }
        void resetAnimation()
        {
            m_currentSprite = 0;
            m_elapsedTime = std::chrono::microseconds::zero();
        }

        auto getElapsedTime() { return m_elapsedTime; }
        void updateElapsedTime(std::chrono::microseconds elapsedTime) { m_elapsedTime += elapsedTime; }

        bool operator==(AnimatedSprite& rhs)
        {
            return m_sprite == rhs.m_sprite &&
                   m_spriteColor == rhs.m_spriteColor &&
                   m_spriteCount == rhs.m_spriteCount &&
                   m_spriteTime == rhs.m_spriteTime;
        }


      private: 
        std::shared_ptr<sf::Sprite> m_sprite;
        std::uint8_t m_spriteCount;
        std::chrono::microseconds m_spriteTime;
        sf::Color m_spriteColor;
        std::uint8_t m_currentSprite{0};
        std::chrono::microseconds m_elapsedTime{0};
    };
}