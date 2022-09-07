#include "Scripting.hpp"

namespace systems
{
    void Scripting::update(std::chrono::milliseconds elapsedTime)
    {
        (void)elapsedTime;

        for (auto&& [id, entity] : m_entities)
        {
            auto script = entity->getComponent<components::ScriptBase>();
            script->update(elapsedTime);
        }
    
    }

}