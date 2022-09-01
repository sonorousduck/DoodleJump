#pragma once

#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace components
{
    /// <summary>
    /// Note that rotation is done in DEGREES
    /// </summary>
    class Position : public PolymorphicComparable<Component, Position>
    {
      public:
        Position(sf::Vector2f position, float rotation = 0.0f) :
            m_position(position),
            m_rotation(rotation)
        {
        }

        auto get() { return m_position; }
        auto set(sf::Vector2f position) { m_position = position; }

        /// <summary>
        /// Returns the rotation of the transform
        /// </summary>
        /// <returns>Angle of the transform in degrees</returns>
        auto getRotation() { return m_rotation; }
        /// <summary>
        /// Sets the rotation of the transform
        /// </summary>
        /// <param name="rotation">The angle of the object in degrees</param>
        void setRotation(float rotation) { m_rotation = rotation; }

        bool operator==(Position& rhs) 
        {
            return m_position == rhs.m_position && m_rotation == rhs.m_rotation;
        }

      private:
        sf::Vector2f m_position;
        float m_rotation;
    };
}