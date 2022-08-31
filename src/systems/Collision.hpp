#pragma once
#include "System.hpp"
#include "components/Position.hpp"
#include "components/RectangularCollider.hpp"

namespace systems
{
	class Collision : public System
    {
      public:
        Collision() :
            System({ctti::unnamed_type_id<components::Position>(),
                    ctti::unnamed_type_id<components::RectangularCollider>()})
        {
        }

        bool rectangleOnRectangle(entities::Entity rectangle1, entities::Entity rectangle2);
        void update(std::chrono::milliseconds elapsedTime);
    };

}