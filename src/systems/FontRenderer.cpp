#include "FontRenderer.hpp"
#include "entities/Entity.hpp"


namespace systems
{
    void FontRenderer::update(std::chrono::milliseconds elapsedTime) 
    {
        (void)elapsedTime;

        for (auto&& [id, entity] : m_entities)
        {
            auto position = entity->getComponent<components::Position>();
            auto text = entity->getComponent<components::Text>();

            text->text.setPosition(position->get());
            text->text.setRotation(position->getRotation());
            text->text.setFont(shojumaru);
            window->draw(text->text);
        }
    }
}