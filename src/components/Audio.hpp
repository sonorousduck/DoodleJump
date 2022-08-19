#pragma once

#include "components/Component.hpp"

#include "misc/ContentKey.hpp"
#include <SFML/Audio/Sound.hpp>
#include <string>
#include <misc/Content.hpp>



namespace components
{
	class Audio : public Component
    {
      public:
        Audio(std::string audioKey, bool load = false) :
            m_audioKey(audioKey)
        {
            if (load)
            {
                m_sound.setBuffer(*Content::get<sf::SoundBuffer>(audioKey));
            }
        }

        auto getKey() { return m_audioKey; }

        bool operator==(Audio& rhs)
        {
            return m_audioKey == rhs.m_audioKey;
        }
    
        private:
          std::string m_audioKey;
          sf::Sound m_sound;
    };
}