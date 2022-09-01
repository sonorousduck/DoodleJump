#pragma once

#include "System.hpp"
#include "components/RigidBody.hpp"
#include "components/Position.hpp"
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace systems
{
	class Physics : public System
    {
      public:
        Physics() :
            System({ctti::unnamed_type_id<components::RigidBody>(),
                    ctti::unnamed_type_id<components::Position>()})
        {
        }
    
        void update(std::chrono::milliseconds elapsedTime);
        const static float GRAVITY_CONSTANT;
    };
}
