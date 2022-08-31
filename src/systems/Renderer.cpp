#include "Renderer.hpp"

#include "entities/Entity.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <misc/Configuration.hpp>

namespace systems
{
    void Renderer::update(std::chrono::milliseconds elapsedTime, std::shared_ptr<sf::RenderTarget> renderTarget)
    {
        (void)elapsedTime; // Compiler warning ignore since we don't care about elapsedTime yet...

        // Draw Background
        sf::RectangleShape square({1000.0f, 1000.0f});
        square.setFillColor(sf::Color::Blue);
        square.setPosition({-500, -500});

        renderTarget->clear(sf::Color::Black);
        renderTarget->draw(square);

        // Render each entity
        for (auto&& [id, entity] : m_entities)
        {
            auto position = entity->getComponent<components::Position>();
            auto sprite = entity->getComponent<components::Sprite>();

            sprite->get()->setPosition(position->get());
            
            sprite->get()->setRotation(position->getRotation());
            sprite->get()->setScale(Configuration::getGraphics().getScaleUI());

            renderTarget->draw(*sprite->get());
            
        }
    }
}