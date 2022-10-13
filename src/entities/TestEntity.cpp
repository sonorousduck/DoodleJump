#include "TestEntity.hpp"



namespace entities
{   
    std::shared_ptr<Entity> entities::createTestEntity(std::string textureFile, sf::Vector2f viewSize, sf::Vector2f position, float size, std::unordered_set<std::shared_ptr<sf::Texture>>& textures)
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
    
        auto texture = std::make_shared<sf::Texture>();
        textures.insert(texture);
        if (!texture->loadFromFile(textureFile))
        {
            std::cout << "Couldn't find the file " << textureFile << std::endl;
            return nullptr;
        }

        auto platformSprite = std::make_shared<sf::Sprite>();
        platformSprite->setTexture(*texture);
        // Set the origin of the texture to the center of it
        platformSprite->setOrigin({texture->getSize().x / 2.0f, texture->getSize().y / 2.0f});

        //
        // Original inspiration: https://en.sfml-dev.org/forums/index.php?topic=15755.0
        // Implementation from Dr. Mathias' work on GameTech (linked in repository)
        // Define a scaling that converts from the texture size in pixels to unit coordinates
        // that match the view.  This makes the texture have the same size/shape as the view.
        sf::Vector2f scaleToUnitSize(viewSize.x / texture->getSize().x, viewSize.y / texture->getSize().y);

        platformSprite->setScale(sf::Vector2f(size * scaleToUnitSize.x, size * scaleToUnitSize.y));

        //entity->addComponent(std::make_unique<components::Text>(string, color, outlineColor, size, outlineThickness));
        //entity->addComponent(std::make_unique<components::Position>(position, rotation));
        entity->addComponent(std::make_unique<components::Position>(position, 180.0f));
        entity->addComponent(std::make_unique<components::Size>(viewSize));
        entity->addComponent(std::make_unique<components::RectangularCollider>(sf::Vector2f(6.5f, 2.0f)));
        entity->addComponent(std::make_unique<components::Sprite>(platformSprite));


        return entity;
    }
}

