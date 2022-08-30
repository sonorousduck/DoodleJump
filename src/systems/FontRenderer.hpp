#pragma once
#include "System.hpp"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include <SFML/Graphics/RenderWindow.hpp>


namespace systems
{
	class FontRenderer : public System
    {
      public:
        FontRenderer() :
            System({ctti::unnamed_type_id<components::Text>(),
                    ctti::unnamed_type_id<components::Position>()})
        {
            shojumaru.loadFromFile("assets/fonts/Shojumaru-Regular.ttf");
        }
	
        void update(std::chrono::milliseconds elapsedTime, std::shared_ptr<sf::RenderTarget> renderTarget);


      private:
        sf::Font shojumaru;

	};
	

}
