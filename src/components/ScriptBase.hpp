#pragma once
#include "Component.hpp"
#include <entities/Entity.hpp>

namespace components
{
    class ScriptBase : public PolymorphicComparable<Component, ScriptBase>
    {
      public:
        virtual void start();
        virtual void destroyed();
        virtual void onCollision(entities::Entity other);
        virtual void onCollisionStart(entities::Entity other);
        virtual void onCollisionEnd(entities::Entity other);
        virtual void update(std::chrono::milliseconds elapsedTime);

        /// <summary>
        /// Allows you to try to call a function from a script, useful for the input system and such
        /// Enforces correct types and parameter counts
        /// </summary>
        /// <param name="functionName"></param>
        /// <param name="values"></param>
        /// https://github.com/Serpents-of-the-East/TowerDefense/blob/fec50d70998b40072d4b3e9858043aa480b487be/CrowEngineBase/Components/ScriptBase.cs#L19
        void sendMessage(std::string functionName)
    
    };

}
