#pragma once
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace components
{
    class RectangularCollider : public Component
    {
      public:
        RectangularCollider(sf::Vector2f size) :
            m_size(size)
        {
        }

        auto get() { return m_size; }
        auto set(sf::Vector2f newSize) { m_size = newSize; }


      private:
        sf::Vector2f m_size;
    };
}