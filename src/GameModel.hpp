#pragma once

#include "entities/Entity.hpp"
#include "systems/Renderer.hpp"
#include "systems/KeyboardInput.hpp"
#include "systems/Collision.hpp"
#include "systems/Physics.hpp"
#include "systems/Scripting.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <memory>
#include <unordered_set>
#include <systems/FontRenderer.hpp>

class GameModel
{
  public:
    bool initialize(sf::Vector2f viewSize, std::shared_ptr<sf::RenderWindow> window);
    void signalKeyPressed(sf::Event::KeyEvent event);
    void signalKeyReleased(sf::Event::KeyEvent event);
    void update(const std::chrono::milliseconds elapsedTime, std::shared_ptr<sf::RenderTarget> renderTarget);

  private:
      // This keeps the textures alive throughout the program
    std::unordered_set<std::shared_ptr<sf::Texture>> m_textures;

    entities::EntityMap m_entities;


    // Systems
    std::unique_ptr<systems::FontRenderer> m_fontRenderer;
    std::unique_ptr<systems::KeyboardInput> m_systemKeyboardInput;
    std::unique_ptr<systems::Renderer> m_systemRender;
    std::unique_ptr<systems::Collision> m_collision;
    std::unique_ptr<systems::Physics> m_physics;
    std::unique_ptr<systems::Scripting> m_scripting;

    void addEntity(std::shared_ptr<entities::Entity> entity);
    void removeEntity(decltype(entities::Entity().getId()) entityId);
};