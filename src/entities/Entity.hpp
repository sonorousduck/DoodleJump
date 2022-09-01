#pragma once

#include "components/Component.hpp"
#include <atomic>
#include <cstdint>
#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable : 4245) // ctti has compiler warnings, I only care about my own
#endif
#include <ctti/type_id.hpp>
#if defined(_MSC_VER)
  #pragma warning(pop)
#endif

#include <atomic>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

namespace entities
{
  // --------------------------------------------------------------
    //
    // An Entity is an 'id' (a number) and a collection of components.
    //
    // The "name" for an entity is its "ctti::unnamed_type_id_t".  This
    // allows for compile-time determination of the name, using an integral
    // type, which also allows it to have fast lookup/use in various
    // associative containers.
    //
    // --------------------------------------------------------------

class Entity : public std::enable_shared_from_this<Entity>
  {
    private:
      static std::atomic_uint32_t nextId; // Each entity needs a unique id, using a static to do this.
    
  
  public:
      using IdType = decltype(nextId.load());

      Entity() :
          m_id(Entity::nextId.load())
      {
          Entity::nextId++;
      }
      virtual ~Entity(){};

      auto getId() { return m_id; }

      template <typename T>
      void addComponent(std::unique_ptr<T> component);

      template <typename T>
      void removeComponent();

      template <typename T>
      bool hasComponent();

      template <typename T>
      T* getComponent();

      auto& getComponents() { return m_components; }

      bool operator==(const Entity& rhs);
      bool operator!=(const Entity& rhs);

    private:
      IdType m_id;
      std::unordered_map<ctti::unnamed_type_id_t, std::unique_ptr<components::Component>> m_components;
  };

  // Convenience type aliases for use throughout the framework
  using EntityPtr = std::shared_ptr<Entity>;
  using EntityMap = std::unordered_map<Entity::IdType, EntityPtr>;
  using EntitySet = std::unordered_set<Entity::IdType>;
  using EntityVector = std::vector<EntityPtr>;

  // --------------------------------------------------------------
  //
  // Components are stored by their compile-time unnamed_type_id, because
  // only one of each type can ever exist on an entity (famous last words!).
  //
  // --------------------------------------------------------------
  template <typename T>
  void Entity::addComponent(std::unique_ptr<T> component)
  {
      m_components[ctti::unnamed_type_id<T>()] = std::move(component);
  }

  // --------------------------------------------------------------
  //
  // The component type is no longer needed, so get rid of it!
  //
  // --------------------------------------------------------------
  template <typename T>
  void Entity::removeComponent()
  {
      m_components.erase(ctti::unnamed_type_id<T>());
  }

  // --------------------------------------------------------------
  //
  // Returns true if the Entity has the component, false otherwise.
  //
  // --------------------------------------------------------------
  template <typename T>
  bool Entity::hasComponent()
  {
      return m_components.contains(ctti::unnamed_type_id<T>());
  }

  // --------------------------------------------------------------
  //
  // This method is returning a raw pointer, because ownership is
  // not an issue.  The calling object can only use/mutate the state
  // of the component, not destroy it.
  //
  // --------------------------------------------------------------
  template <typename T>
  T* Entity::getComponent()
  {
      assert(hasComponent<T>());

      return static_cast<T*>(m_components[ctti::unnamed_type_id<T>()].get());
  }

}

namespace std
{

    // --------------------------------------------------------------
    //
    // Hash function for entities::Entity, to allow it to be used in
    // std:: containers where a hash function is needed.
    //
    // --------------------------------------------------------------
    template <>
    struct hash<shared_ptr<entities::Entity>>
    {
        size_t operator()(const entities::EntityPtr& v) const noexcept
        {
            return v->getId();
        }
    };
} // namespace std