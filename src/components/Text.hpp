#pragma once
#include "Component.hpp"
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

// https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Text.php#aa19ec69c3b894e963602a6804ca68fe4

namespace components
{
	class Text : public Component
    {
      public:
        Text(std::string string, sf::Color color, sf::Color outlineColor, std::uint8_t size, float outlineThickness = 0)  
        {
            text.setString(string);
            text.setFillColor(color);
            text.setOutlineColor(outlineColor);
            text.setCharacterSize(size);
            text.setOutlineThickness(outlineThickness);
        }

      public:
        sf::Text text;


    };
}