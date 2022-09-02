#include "GameModel.hpp"

#include "components/Input.hpp"
#include "entities/LocalPlayer.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>
#include <tuple>
#include "misc/Configuration.hpp"
#include "misc/ConfigurationPath.hpp"
#include "misc/Content.hpp"
#include "misc/ContentKey.hpp"
#include <entities/TestEntity.hpp>

/// <summary>
/// Sets up all systems and any objects that should be added at the beginning
/// </summary> 
/// <param name="viewSize"></param>
/// <returns></returns>
bool GameModel::initialize(sf::Vector2f viewSize, std::shared_ptr<sf::RenderWindow> window)
{
    // Initialize systems

    // TODO: Should read from config file for key remappings
    auto inputMapping = {
        std::make_tuple(components::Input::Type::Up, sf::Keyboard::W),
        std::make_tuple(components::Input::Type::Down, sf::Keyboard::S),
        std::make_tuple(components::Input::Type::Left, sf::Keyboard::A),
        std::make_tuple(components::Input::Type::Right, sf::Keyboard::D),
        std::make_tuple(components::Input::Type::Fire, sf::Keyboard::F)};
    m_systemKeyboardInput = std::make_unique<systems::KeyboardInput>(inputMapping);

    m_systemRender = std::make_unique<systems::Renderer>();
    m_fontRenderer = std::make_unique<systems::FontRenderer>();
    m_collision = std::make_unique<systems::Collision>();
    m_physics = std::make_unique<systems::Physics>();
    

    // Create and add entities
    addEntity(entities::createLocalPlayer("assets/images/crow.png", viewSize, sf::Vector2f(-0.25f, 0.0f), 1, m_textures));
    addEntity(entities::createTestEntity("YEEET", sf::Color::Red, sf::Color::Green, 40, sf::Vector2f(-1.0f, 1.0f), 1.0f));


    return true;
}

void GameModel::signalKeyPressed(sf::Event::KeyEvent event)
{
    // this should notify the keyboard system eventually
    m_systemKeyboardInput->keyPressed(event);
}

void GameModel::signalKeyReleased(sf::Event::KeyEvent event)
{
    // this should notify the keyboard system eventually
    m_systemKeyboardInput->keyReleased(event);
}

/// <summary>
/// Updates all systems
/// </summary>
/// <param name="elapsedTime"></param>
/// <param name="renderTarget"></param>
void GameModel::update(const std::chrono::milliseconds elapsedTime, std::shared_ptr<sf::RenderTarget> renderTarget)
{
    // Update non-render systems

    // Render
    m_systemKeyboardInput->update(elapsedTime);
    m_systemRender->update(elapsedTime, renderTarget);
    m_fontRenderer->update(elapsedTime, renderTarget);
    m_collision->update(elapsedTime);
    m_physics->update(elapsedTime);

}

/// <summary>
/// Adds the entity given to the systems that want it
/// </summary>
/// <param name="entity"></param>
void GameModel::addEntity(std::shared_ptr<entities::Entity> entity)
{
    if (entity == nullptr)
        return;

    m_entities[entity->getId()] = entity;

    // Add to all systems
    m_systemKeyboardInput->addEntity(entity);
    m_systemRender->addEntity(entity);
    m_fontRenderer->addEntity(entity);
    m_collision->addEntity(entity);
    m_physics->addEntity(entity);
}

/// <summary>
/// Removes the given entity from the systems
/// </summary>
/// <param name="entityId"></param>
void GameModel::removeEntity(decltype(entities::Entity().getId()) entityId)
{
    m_entities.erase(entityId);

    // Remove from all systems
    m_systemKeyboardInput->removeEntity(entityId);
    m_systemRender->removeEntity(entityId);
    m_fontRenderer->removeEntity(entityId);
    m_collision->removeEntity(entityId);
    m_physics->removeEntity(entityId);
}