#pragma once
#include "Component.hpp"
#include <entities/Entity.hpp>

namespace components
{
    class ScriptBase : public PolymorphicComparable<Component, ScriptBase>
    {
      public:
          // This might need a rewrite. Seems weird to need the entity inside of a component, when the entity itself holds the component. 
        entities::EntityPtr entity;

        ScriptBase(entities::EntityPtr entity) :
            entity(entity)
        {
        }


        virtual void start() = 0;
        virtual void destroyed() = 0;
        virtual void onCollision(entities::EntityPtr other) = 0;
        virtual void onCollisionStart(entities::EntityPtr other) = 0;
        virtual void onCollisionEnd(entities::EntityPtr  other) = 0;
        virtual void update(std::chrono::milliseconds elapsedTime) = 0;

        /// <summary>
        /// Allows you to try to call a function from a script, useful for the input system and such
        /// Enforces correct types and parameter counts
        /// </summary>
        /// <param name="functionName"></param>
        /// <param name="values"></param>
        /// https://github.com/Serpents-of-the-East/TowerDefense/blob/fec50d70998b40072d4b3e9858043aa480b487be/CrowEngineBase/Components/ScriptBase.cs#L19
        /// TODO: Implement sendMessage. Not necessary at this time, but it would be cool to have
       /* void sendMessage(std::string functionName);*/
    
    };

}
