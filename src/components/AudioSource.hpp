#pragma once
#include <SFML/Audio.hpp>

#include "Component.hpp"

namespace components
{
	class AudioSource : public Component
    {
      public: 
        enum class SongState : std::uint8_t
        {
            Paused,
            Playing,
            Stopped
        };



        SongState previousState;
        SongState currentState;
        std::string previousSong;
        std::string currentSong;
        bool repeatSong;
        std::vector<std::string> soundEffectsToPlay;
        sf::SoundBuffer buffer;
        sf::Music music;
        sf::Sound sound;



      private:

    };
}