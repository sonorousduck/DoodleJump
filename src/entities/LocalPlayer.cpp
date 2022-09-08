#include "LocalPlayer.hpp"

#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Size.hpp"
#include "components/Movement.hpp"
#include "components/Input.hpp"
#include "components/Audio.hpp"
#include "components/RectangularCollider.hpp"
#include "components/AudioSource.hpp"
#include "misc/Content.hpp"



#include <iostream>

namespace entities
{
    std::shared_ptr<Entity> createLocalPlayer(std::string textureFile, sf::Vector2f viewSize, sf::Vector2f position, float size, std::unordered_set<std::shared_ptr<sf::Texture>>& textures) 
    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();

        // Load the texture
        auto texture = std::make_shared<sf::Texture>();
        textures.insert(texture);
        if (!texture->loadFromFile(textureFile))
        {
            std::cout << "Couldn't find the file " << textureFile << std::endl;
            return nullptr;
        }

        auto playerSprite = std::make_shared<sf::Sprite>();
        playerSprite->setTexture(*texture);
        // Set the origin of the texture to the center of it
        playerSprite->setOrigin({texture->getSize().x / 2.0f, texture->getSize().y / 2.0f});

        //
        // Original inspiration: https://en.sfml-dev.org/forums/index.php?topic=15755.0
        // Implementation from Dr. Mathias' work on GameTech (linked in repository)
        // Define a scaling that converts from the texture size in pixels to unit coordinates
        // that match the view.  This makes the texture have the same size/shape as the view.
        sf::Vector2f scaleToUnitSize(viewSize.x / texture->getSize().x, viewSize.y / texture->getSize().y);

        playerSprite->setScale(sf::Vector2f(size * scaleToUnitSize.x, size * scaleToUnitSize.y));

        // Add the components to this
        entity->addComponent(std::make_unique<components::Position>(position));
        entity->addComponent(std::make_unique<components::Size>(viewSize));
        entity->addComponent(std::make_unique<components::Sprite>(playerSprite));
        entity->addComponent(std::make_unique<components::Movement>(0.02f));
        entity->addComponent(std::make_unique<components::RectangularCollider>(sf::Vector2f(1.0f, 1.0f)));

        //entity->addComponent(std::make_unique<components::Audio>(content::KEY_AUDIO_GENERIC, true));

        auto inputs = {
            components::Input::Type::Up,
            components::Input::Type::Down,
            components::Input::Type::Jump};
        entity->addComponent(std::make_unique<components::Input>(inputs));

        return entity;

    }
}