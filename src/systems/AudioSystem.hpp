#pragma once

#include "System.hpp"
#include "components/AudioSource.hpp"
#include <chrono>
#include <memory>


namespace systems
{
	class AudioSystem : public System
    {
      public:
        AudioSystem() :
            System({ctti::unnamed_type_id<components::AudioSource>()})
        {
        }

        virtual void update(std::chrono::milliseconds elapsedTime);
        virtual void addEntity(std::shared_ptr<entities::Entity> entity);
        virtual void removeEntity(decltype(entities::Entity().getId()) entityId);
    
        private:
	};
}