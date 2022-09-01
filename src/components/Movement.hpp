#pragma once

#include "Component.hpp"

// --------------------------------------------------------------
//
// Holds details regarding movement properties.
//
// --------------------------------------------------------------
namespace components
{
    class Movement : public PolymorphicComparable<Component, Movement>
    {
      public:
        Movement(float speed) :
            m_speed(speed)
        {
        }

        float getAcceleration() { return m_speed; }

        bool operator==(Movement& rhs)
        {
            return m_speed == rhs.m_speed;
        }


      private:
        float m_speed;   // unit distance per millisecond
    };
} // namespace components