#pragma once

#include "System.hpp"
#include "components/ScriptBase.hpp"


namespace systems
{
	class Scripting : public System
    {
      public:
        Scripting() :
            System({ctti::unnamed_type_id<components::ScriptBase>()})
        {
        }

        void update(std::chrono::milliseconds elapsedTime);
        void addEntity(std::shared_ptr<entities::Entity> entity);

      protected:
        bool isInterested(entities::Entity* entity);

      private:
          // TODO: Implement this at a later time
        // void callInputScripts(std::uint8_t id);
	};
	
}
