#pragma once
#include "Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace components
{
	class RigidBody : public PolymorphicComparable<Component, RigidBody>
    {
      public:
        RigidBody(float mass, float gravityScale) :
            mass(mass),
            gravityScale(gravityScale),
            velocity(0.0f, 0.0f),
            acceleration(0.0f, 0.0f)
        {
        }

        float mass;
        float gravityScale;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;


      private:

    
    };
}