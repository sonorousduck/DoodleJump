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
        FontRenderer(std::shared_ptr<sf::RenderWindow> window) :
            System({ctti::unnamed_type_id<components::Text>(),
                    ctti::unnamed_type_id<components::Position>()}),
            window(window)
        {
            shojumaru.loadFromFile("assets/fonts/Shojumaru-Regular.ttf");
        }
	
        void update(std::chrono::milliseconds elapsedTime);


      private:
        std::shared_ptr<sf::RenderWindow> window;
        sf::Font shojumaru;

	};
	

}
