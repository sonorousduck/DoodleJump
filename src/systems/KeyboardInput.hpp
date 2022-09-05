#pragma once

#include "System.hpp"
#include "components/Input.hpp"
#include "components/Position.hpp"
#include "components/Movement.hpp"
#include "entities/Entity.hpp"
#include "misc/SoundPlayer.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <functional>
#include <initializer_list>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

namespace systems
{
  class KeyboardInput : public System
  {
    public:
      KeyboardInput(std::initializer_list<std::tuple<components::Input::Type, sf::Keyboard::Key>> mapping) : 
        System({ctti::unnamed_type_id<components::Input>(),
                ctti::unnamed_type_id<components::Position>(),
                ctti::unnamed_type_id<components::Movement>()})
      {
        for (auto&& input : mapping)
        {
          m_typeToKeyMap[std::get<0>(input)] = std::get<1>(input);
        }
      }

      virtual void addEntity(std::shared_ptr<entities::Entity> entity);
      virtual void removeEntity(decltype(entities::Entity().getId()) entityId);

      virtual void update(std::chrono::milliseconds elapsedTime);

      void keyPressed(sf::Event::KeyEvent keyEvent);
      void keyReleased(sf::Event::KeyEvent keyEvent);

    private:
      class KeyToFunction
        {
          public:
            std::unordered_map<sf::Keyboard::Key, std::function<void(std::chrono::milliseconds, components::Position*, components::Movement*)>> m_keyToFunction;
        };

      std::unordered_map<sf::Keyboard::Key, sf::Event::KeyEvent> m_keysPressed;
      std::unordered_map<components::Input::Type, sf::Keyboard::Key> m_typeToKeyMap;
      std::unordered_map<decltype(entities::Entity().getId()), KeyToFunction> m_keyToFunctionMap;

      void moveUp(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement);
      void moveLeft(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement);
      void moveRight(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement);
      void moveDown(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement);
      void fire(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement);
  };
}