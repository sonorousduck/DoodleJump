#include "Physics.hpp"


namespace systems
{
    const float Physics::GRAVITY_CONSTANT = 9.81f;

    void Physics::update(std::chrono::milliseconds elapsedTime)
    {
        (void)elapsedTime;

        for (auto& [id, entity] : m_entities)
        {
            components::Position* position = entity->getComponent<components::Position>();
            components::RigidBody* rigidBody = entity->getComponent<components::RigidBody>();

            rigidBody->velocity += sf::Vector2f(0.0f, GRAVITY_CONSTANT * (elapsedTime.count() / 1000.0f) * rigidBody->gravityScale);
            rigidBody->velocity += sf::Vector2f(rigidBody->acceleration.x * (elapsedTime.count() / 1000.0f), rigidBody->acceleration.y * pow((elapsedTime.count() / 1000.0f), 2));


            position->set(position->get() + rigidBody->velocity * (elapsedTime.count() / 1000.0f));
        }
    
    }

}