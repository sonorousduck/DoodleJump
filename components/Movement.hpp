#pragma once

#include "Component.hpp"

// --------------------------------------------------------------
//
// Holds details regarding movement properties.
//
// --------------------------------------------------------------
namespace components
{
    class Movement : public Component
    {
      public:
        Movement(float speed) :
            m_speed(speed)
        {
        }

        float getAcceleration() { return m_speed; }

      private:
        float m_speed;   // unit distance per millisecond
    };
} // namespace components