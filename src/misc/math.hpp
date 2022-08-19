#pragma once

#include <cmath>
#include <numbers>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


namespace math
{
    const float PI = 3.14159f;
    
    // Redefine SFML's Vector2f to increase functionality
    struct Vector2f
    {
        Vector2f() :
            x(0), y(0)
        {
        }

        Vector2f(float x, float y) :
            x(x), y(y)
        {
        }

        operator sf::Vector2f() { return sf::Vector2f(x, y); }

        float x;
        float y;
    };

    // Redefine SFML's Point2f to increase functionality
    struct Point2f
    {
        Point2f():
            x(0), y(0)
        {
        }

        Point2f(float x, float y) :
            x(x), y(y)
        {
        }
        
        operator sf::Vector2f() { return sf::Vector2f(x, y); }
        operator Vector2f() { return Vector2f(x, y); }

        float x;
        float y;
    };

    struct Dimension2f
    {
        Dimension2f() :
            width(0), height(0)
        {
        }

        Dimension2f(float width, float height) :
            width(width), height(height)
        {
        }

        operator sf::Vector2f() { return sf::Vector2f(width, height); }

        float width;
        float height;
    };

    struct Dimension2u
    {
        Dimension2u() :
            width(0), height(0)
        {
        }

        Dimension2u(unsigned int width, unsigned int height) :
            width(width), height(height)
        {
        }

        unsigned int width;
        unsigned int height;
    };



}