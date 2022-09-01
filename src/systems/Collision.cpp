#include "Collision.hpp"


namespace systems
{
    void Collision::update(std::chrono::milliseconds elapsedTime)
    {
        (void)elapsedTime;

        for (auto& [id, entity] : m_entities)
        {
            std::vector<std::shared_ptr<entities::Entity>> currentlyColliding = {};

            for (auto& [id1, entity1] : m_entities)
            {
                if (hasCollided(entity, entity1))
                {
                    currentlyColliding.push_back(entity1);
                    
                    // This is where I will handle OnCollisionStart, OnCollision, and OnCollisionEnd

                    if (!(std::find(entity->getComponent<components::RectangularCollider>()->currentlyColliding.begin(), entity->getComponent<components::RectangularCollider>()->currentlyColliding.end(), entity1) != entity->getComponent<components::RectangularCollider>()->currentlyColliding.end()))
                    {
                        // This means OnCollisionStart
                        std::cout << "It began collision!" << std::endl;
                    }
                    else
                    {
                        // else, onCollision
                        std::cout << "It is colliding" << std::endl;
                    }
                }
                else
                {
                // We used to be colliding with this
                if (std::find(entity->getComponent<components::RectangularCollider>()->currentlyColliding.begin(), entity->getComponent<components::RectangularCollider>()->currentlyColliding.end(), entity1) != entity->getComponent<components::RectangularCollider>()->currentlyColliding.end())
                {
                    // OnCollisionEnd
                    std::cout << "It ended collision!" << std::endl;

                }

                // I believe this should auto delete the old pointer.... If memory is increasing steadily, this is a potential location of interest.

                }
            }

            entity->getComponent<components::RectangularCollider>()->currentlyColliding = currentlyColliding;
        }
    }


    bool Collision::hasCollided(entities::EntityPtr rectangle1, entities::EntityPtr rectangle2)
    {
        if (rectangle1 == rectangle2)
        {
            return false;
        }

        if (rectangle1->hasComponent<components::RectangularCollider>())
        {
            if (rectangle2->hasComponent<components::RectangularCollider>())
            {
                components::Position rectangle1Position = rectangle1->getComponent<components::Position>()->get();
                components::Position rectangle2Position = rectangle2->getComponent<components::Position>()->get();
                components::RectangularCollider rectangle1Collider = rectangle1->getComponent<components::RectangularCollider>()->get();
                components::RectangularCollider rectangle2Collider = rectangle2->getComponent<components::RectangularCollider>()->get();

                return !(
                    rectangle1Position.get().x - rectangle1Collider.get().x / 2.0f > rectangle2Position.get().x + rectangle2Collider.get().x / 2.0f || // sq1 left is greater than sq2 right
                    rectangle1Position.get().x + rectangle1Collider.get().x / 2.0f < rectangle2Position.get().x - rectangle2Collider.get().x / 2.0f || // sq1 right is less than sq2 left
                    rectangle1Position.get().y - rectangle1Collider.get().y / 2.0f > rectangle2Position.get().y + rectangle2Collider.get().y / 2.0f || // sq1 top is below sq2 bottom
                    rectangle1Position.get().y + rectangle1Collider.get().y / 2.0f < rectangle2Position.get().y - rectangle2Collider.get().y / 2.0f    // sq1 bottom is above sq1 top
                );
            }
        }

        return false;
    }
}