#pragma once
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace components
{
    class RectangularCollider : public PolymorphicComparable<Component, RectangularCollider>
    {
      public:
        RectangularCollider(sf::Vector2f size) :
            m_size(size)
        {
        }

        auto get() { return m_size; }
        auto set(sf::Vector2f newSize) { m_size = newSize; }
        std::vector<std::shared_ptr<entities::Entity>> currentlyColliding;

      private:
        sf::Vector2f m_size;
        
    };
}