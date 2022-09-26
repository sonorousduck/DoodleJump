#include "AnimationRenderer.hpp"

#include <chrono>
#include <memory>

namespace systems
{
    void AnimationRenderer::update(const std::chrono::microseconds elapsedTime)
    {
        this->updateImpl(elapsedTime);
    }

    void AnimationRenderer::updateImpl(std::chrono::microseconds elapsedTime)
    {
        for (auto&& [id, entity] : m_entities)
        {
            auto sprite = entity->getComponent<components::AnimatedSprite>();
            sprite->updateElapsedTime(elapsedTime);

            while (sprite->getElapsedTime() >= sprite->getSpriteTime())
            {
                sprite->incrementSprite();
                sprite->updateElapsedTime(-sprite->getSpriteTime());
            }
        }
    }

}