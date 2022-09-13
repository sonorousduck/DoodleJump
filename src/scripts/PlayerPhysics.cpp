#include "PlayerPhysics.hpp"

namespace scripts
{
    void PlayerPhysics::update(std::chrono::milliseconds elapsedTime) 
    {
        if (entity->hasComponent<components::RigidBody>())
        {
            auto rigidBody = entity->getComponent<components::RigidBody>();

            if (rigidBody->velocity.y < -5.0f) 
            {
                rigidBody->velocity.y = -5.0f;    
            }
            
        }
    }
    
    void PlayerPhysics::start()
    {
    }

    void PlayerPhysics::destroyed()
    {
    }

    void PlayerPhysics::onCollisionStart(entities::EntityPtr other)
    {
    
    }

    void PlayerPhysics::onCollision(entities::EntityPtr other)
    {
        if (entity->hasComponent<components::RigidBody>())
        {
            auto rigidBody = entity->getComponent<components::RigidBody>();

            rigidBody->velocity.y = 5.0f;
        }

    }

    void PlayerPhysics::onCollisionEnd(entities::EntityPtr other)
    {
    
    }

}