#include "FontRenderer.hpp"
#include "entities/Entity.hpp"


namespace systems
{
    void FontRenderer::update(std::chrono::milliseconds elapsedTime, std::shared_ptr<sf::RenderTarget> renderTarget) 
    {
        (void)elapsedTime;

        for (auto&& [id, entity] : m_entities)
        {
            auto position = entity->getComponent<components::Position>();
            auto text = entity->getComponent<components::Text>();

            text->text.setPosition(position->get());
            text->text.setRotation(position->getRotation());
            text->text.setFont(shojumaru);
            text->text.setScale(Configuration::getGraphics().getScaleUI());
            renderTarget->draw(text->text);
        }
    }
}