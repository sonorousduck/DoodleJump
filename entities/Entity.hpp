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

#include <memory>
#include <unordered_map>

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

    class Entity
    {
      public:
        Entity() :
          m_id(Entity::nextId++)
        {
        }

        auto getId() { return m_id; }

        template <typename T>
        void addComponent(std::unique_ptr<T> component);

        template <typename T>
        void removeComponent();

        auto& getComponents() { return m_components; }

        template <typename T>
        T* getComponent();
      
      private:
        static std::atomic<std::uint32_t> nextId; // static ensures each entity gets a unique id, and atomic ensures no problems with threading

        decltype(nextId.load()) m_id;
        std::unordered_map<ctti::unnamed_type_id_t, std::unique_ptr<components::Component>> m_components;
    };

    using EntityMap = std::unordered_map<decltype(Entity().getId()), std::shared_ptr<Entity>>;


    template <typename T>
    void Entity::addComponent(std::unique_ptr<T> component)
    {
      m_components[ctti::unnamed_type_id<T>()] = std::move(component);
    }

    template <typename T>
    void Entity::removeComponent()
    {
      m_components.erase(ctti::unnamed_type_id<T>());
    }

    template <typename T>
    T* Entity::getComponent()
    {
      return static_cast<T*>(m_components[ctti::unnamed_type_id<T>()].get());
    }
}