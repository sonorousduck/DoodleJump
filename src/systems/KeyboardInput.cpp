#include "KeyboardInput.hpp"

#include "entities/Entity.hpp"

#include <cmath>
#include <iostream>

namespace systems
{
  void KeyboardInput::addEntity(std::shared_ptr<entities::Entity> entity)
  {
    System::addEntity(entity);

    KeyToFunction map;

    if (entity->hasComponent<components::Input>())
    {
        for (auto&& input : entity->getComponent<components::Input>()->getInputs())
        {

            switch (input)
            {
                case components::Input::Type::Up:
                {
                    std::function<void(std::chrono::milliseconds, components::Position*, components::Movement*)> f = std::bind(&KeyboardInput::moveUp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    map.m_keyToFunction[m_typeToKeyMap[input]] = f;
                }
                break;
                case components::Input::Type::Down:
                {
                    std::function<void(std::chrono::milliseconds, components::Position*, components::Movement*)> f = std::bind(&KeyboardInput::moveDown, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    map.m_keyToFunction[m_typeToKeyMap[input]] = f;
                }
                break;
                case components::Input::Type::Left:
                {
                    std::function<void(std::chrono::milliseconds, components::Position*, components::Movement*)> f = std::bind(&KeyboardInput::moveLeft, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    map.m_keyToFunction[m_typeToKeyMap[input]] = f;
                }
                break;
                case components::Input::Type::Right:
                {
                    std::function<void(std::chrono::milliseconds, components::Position*, components::Movement*)> f = std::bind(&KeyboardInput::moveRight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    map.m_keyToFunction[m_typeToKeyMap[input]] = f;
                }
                break;
                case components::Input::Type::Fire:
                {
                    std::function<void(std::chrono::milliseconds, components::Position*, components::Movement*)> f = std::bind(&KeyboardInput::fire, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
                    map.m_keyToFunction[m_typeToKeyMap[input]] = f;
                }
                break;
            }
        }

        m_keyToFunctionMap[entity->getId()] = map;
    }


    
  }

  void KeyboardInput::removeEntity(decltype(entities::Entity().getId()) entityId)
  {
    // Need to let the System class do its thing
    System::removeEntity(entityId);
    // Remove from out local key to function mapping
    m_keyToFunctionMap.erase(entityId);
  }

  //
  // Loop through all the pressed keys and call the functions as necessary
  //
  void KeyboardInput::update(std::chrono::milliseconds elapsedTime)
  {
    for (auto&& [key, keyEvent] : m_keysPressed)
    {
      for (auto&& [id, entity] : m_entities)
      {
        if (m_keyToFunctionMap[id].m_keyToFunction.find(key) != m_keyToFunctionMap[id].m_keyToFunction.end())
        {
          auto position = entity->getComponent<components::Position>();
          auto movement = entity->getComponent<components::Movement>();
          m_keyToFunctionMap[id].m_keyToFunction[key](elapsedTime, position, movement);
        }
      }
    }
  }

  //
  // Add and remove keys from the currently pressed keys events
  //
  void KeyboardInput::keyPressed(sf::Event::KeyEvent keyEvent)
  {
    m_keysPressed[keyEvent.code] = keyEvent;
  }
  void KeyboardInput::keyReleased(sf::Event::KeyEvent keyEvent)
  {
    m_keysPressed.erase(keyEvent.code);
  }


  // Game specific inputs
  // These should change based on the game
  void KeyboardInput::moveUp(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement)
  {
    auto current = position->get();
    position->set(sf::Vector2f(
      current.x,
      current.y - elapsedTime.count() * movement->getAcceleration()));
  }

  void KeyboardInput::moveDown(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement)
  {
    auto current = position->get();
    position->set(sf::Vector2f(
      current.x,
      current.y + elapsedTime.count() * movement->getAcceleration()));
  }
  
  void KeyboardInput::moveLeft(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement)
  {
    auto current = position->get();
    position->set(sf::Vector2f(
      current.x - elapsedTime.count() * movement->getAcceleration(),
      current.y));
  }
  
  void KeyboardInput::moveRight(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement)
  {
    auto current = position->get();
    position->set(sf::Vector2f(
      current.x + elapsedTime.count() * movement->getAcceleration(),
      current.y));
  }

  void KeyboardInput::fire(std::chrono::milliseconds elapsedTime, components::Position* position, components::Movement* movement)
  {
    (void)elapsedTime;
  }

}