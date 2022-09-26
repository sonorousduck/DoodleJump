#pragma once

#include "System.hpp"
#include "components/AnimatedSprite.hpp"

#include <chrono>

namespace systems
{
	class AnimationRenderer : public System
    {
      public:
        AnimationRenderer() :
            System({ctti::unnamed_type_id<components::AnimatedSprite>()})
        {
        }
        virtual void update(std::chrono::microseconds elapsedTime);

      private:
        void updateImpl(std::chrono::microseconds elapsedTime);

    };

}