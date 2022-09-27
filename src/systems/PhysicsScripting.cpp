#include "PhysicsScripting.hpp"

namespace systems
{
    void PhysicsScripting::update(std::chrono::milliseconds elapsedTime)
    {

        for (auto&& [id, entity] : m_entities)
        {
            if (entity->hasComponent<scripts::PlayerPhysics>())
            {
                entity->getComponent<scripts::PlayerPhysics>()->update(elapsedTime);
            }

        } 
    }

}