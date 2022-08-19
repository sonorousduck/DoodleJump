#include "Renderer.hpp"
#include "AudioSystem.hpp"
#include "entities/Entity.hpp"


namespace systems
{
    void AudioSystem::update(std::chrono::milliseconds elapsedTime)
    {
        (void)elapsedTime;

        for (auto&& [id, entity] : m_entities)
        {
            auto audioSource = entity->getComponent<components::AudioSource>();
            
            if (audioSource->previousState == components::AudioSource::SongState::Stopped && audioSource->currentState == components::AudioSource::SongState::Playing) 
            {
                if (audioSource->music.openFromFile(audioSource->currentSong))
                {
                    audioSource->music.play();
                    if (audioSource->repeatSong)
                    {
                        audioSource->music.setLoop(true);
                    }

                }
            }
            else if (audioSource->previousState == components::AudioSource::SongState::Paused && audioSource->currentState == components::AudioSource::SongState::Playing)
            {
                audioSource->music.play();

            }
            else if (audioSource->previousState == components::AudioSource::SongState::Playing && audioSource->currentState == components::AudioSource::SongState::Paused)
            {
                audioSource->music.pause();
            }
            else if (audioSource->previousState == components::AudioSource::SongState::Playing && audioSource->currentState == components::AudioSource::SongState::Stopped)
            {
                audioSource->music.stop();
            }

            audioSource->previousState = audioSource->currentState;
            audioSource->previousSong = audioSource->currentSong;


            // Plays all the sound effects
            for (int i = 0; i < audioSource->soundEffectsToPlay.size(); i++)
            {
                if (audioSource->buffer.loadFromFile(audioSource->soundEffectsToPlay[i]))
                {
                    audioSource->sound.setBuffer(audioSource->buffer);
                    audioSource->sound.play();
                }
            }

        }

        return;
    }
    void AudioSystem::addEntity(std::shared_ptr<entities::Entity> entity)
    {
    }

    void AudioSystem::removeEntity(decltype(entities::Entity().getId()) entityId)
    {
    }
}

