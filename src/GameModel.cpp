#include "GameModel.hpp"

#include "components/Input.hpp"
#include "entities/LocalPlayer.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>
#include <tuple>

/// <summary>
/// Sets up all systems and any objects that should be added at the beginning
/// </summary> 
/// <param name="viewSize"></param>
/// <returns></returns>
bool GameModel::initialize(sf::Vector2f viewSize)
{
    // Initialize systems
    auto inputMapping = {
        std::make_tuple(components::Input::Type::Up, sf::Keyboard::W),
        std::make_tuple(components::Input::Type::Down, sf::Keyboard::S),
        std::make_tuple(components::Input::Type::Left, sf::Keyboard::A),
        std::make_tuple(components::Input::Type::Right, sf::Keyboard::D),
        std::make_tuple(components::Input::Type::Fire, sf::Keyboard::F)};
    m_systemKeyboardInput = std::make_unique<systems::KeyboardInput>(inputMapping);

    m_systemRender = std::make_unique<systems::Renderer>();

    // Create and add entities
    addEntity(entities::createLocalPlayer("assets/images/crow.png", viewSize, sf::Vector2f(-0.25f, 0.0f), 0.05f, m_textures));

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
}