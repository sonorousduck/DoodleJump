#include "TestEntity.hpp"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include <components/Input.hpp>


namespace entities
{   
    std::shared_ptr<Entity> entities::createTestEntity(std::string string, sf::Color color, sf::Color outlineColor, std::uint8_t size, sf::Vector2f position, float outlineThickness, float rotation)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    
        entity->addComponent(std::make_unique<components::Text>(string, color, outlineColor, size, outlineThickness));
        entity->addComponent(std::make_unique<components::Position>(position, rotation));

        auto inputs = {
            components::Input::Type::Up,
            components::Input::Type::Down,
            components::Input::Type::Left,
            components::Input::Type::Right,
            components::Input::Type::Fire};
        entity->addComponent(std::make_unique<components::Input>(inputs));


        return entity;
    }
}

