#include "System.hpp"

#include <algorithm>

namespace systems
{
  void System::addEntity(std::shared_ptr<entities::Entity> entity)
  {
    if (isInterested(entity.get()))
    {
      m_entities[entity->getId()] = entity;
    }
  }

  void System::removeEntity(decltype(entities::Entity().getId()) entityId)
  {
    m_entities.erase(entityId);
  }

  bool System::isInterested(entities::Entity* entity)
  {
    auto iCareIfAll = std::all_of(
      m_interests.begin(), m_interests.end(),
      [&entity](auto interest) {
        return entity->getComponents().find(interest) != entity->getComponents().end();
      });
    
    return iCareIfAll;
  }
}