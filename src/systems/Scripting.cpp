#include "Scripting.hpp"

namespace systems
{
    void Scripting::update(std::chrono::milliseconds elapsedTime)
    {
        (void)elapsedTime;

        for (auto&& [id, entity] : m_entities)
        {
            for (auto&& [id1, component] : entity->getComponents())
            {
                auto pointer = dynamic_cast<components::ScriptBase*>(component.get());

                if (pointer != nullptr)
                {
                    pointer->update(elapsedTime);
                }       
            } 
        }
    }

    bool Scripting::isInterested(entities::Entity* entity)
    {

        for (auto&& [id, component] : entity->getComponents())
        {
            auto pointer = dynamic_cast<components::ScriptBase*>(component.get());

            if (pointer != nullptr)
            {
                return true;
            }
        }

        return false;
    }


    void Scripting::addEntity(std::shared_ptr<entities::Entity> entity)
    {
        if (isInterested(entity.get()))
        {
            m_entities[entity->getId()] = entity;
        }
    }
}

