#pragma once
#include "System.hpp"
#include "components/Position.hpp"
#include "components/RectangularCollider.hpp"
#include "components/ScriptBase.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include "scripts/PlayerPhysics.hpp"



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

        //bool rectangleOnRectangle(entities::Entity rectangle1, entities::Entity rectangle2);
        void update(std::chrono::milliseconds elapsedTime);

      private:
        bool hasCollided(entities::EntityPtr rectangle1, entities::EntityPtr rectangle2);
        std::vector<entities::Entity*> currentCollidedGameObjects = {};
    };

}