#pragma once

#include "components/ScriptBase.hpp"
#include "components/RigidBody.hpp"

namespace scripts
{
    class PlayerPhysics : public components::ScriptBase
    {
      public:
        PlayerPhysics(entities::EntityPtr entity) :
            ScriptBase(entity)
        {
        }
        void update(std::chrono::milliseconds elapsedTime);
        void start();
        void destroyed();
        void onCollision(entities::EntityPtr other);
        void onCollisionStart(entities::EntityPtr other);
        void onCollisionEnd(entities::EntityPtr other);
         

    };

}