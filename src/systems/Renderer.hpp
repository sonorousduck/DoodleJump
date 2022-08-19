#pragma once

#include "System.hpp"
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Size.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <chrono>
#include <memory>

namespace systems
{
    class Renderer : public System
    {
      public:
        Renderer() :
            System({ctti::unnamed_type_id<components::Sprite>(),
                    ctti::unnamed_type_id<components::Position>(),
                    ctti::unnamed_type_id<components::Size>()})
        {
        }

        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Woverloaded-virtual"
        void update(std::chrono::milliseconds elapsedTime, std::shared_ptr<sf::RenderTarget> renderTarget);
        #pragma clang diagnostic pop

      private:
    };
}