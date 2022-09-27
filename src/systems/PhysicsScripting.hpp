#pragma once
#include "System.hpp"
#include "scripts/PlayerPhysics.hpp"

namespace systems
{
    class PhysicsScripting : public System
    {
      public:
        PhysicsScripting() :
            System({ctti::unnamed_type_id<scripts::PlayerPhysics>()})
        {
        }

        // Just add more if you need to have different forms of this PhysicsScripting. This will allow for extension. While this really isn't scripting as much anymore, it works :)
        //PhysicsScripting() :
        //    System({ctti::unnamed_type_id<scripts::PlayerPhysics>()})
        //{
        //}

        void update(std::chrono::milliseconds elapsedTime);

      private:
    };

} // namespace systems