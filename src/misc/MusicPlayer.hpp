#pragma once
#include <string>
#include <thread>
#include <mutex>
#include "misc/ConcurrentQueue.hpp"
#include <SFML/Audio/Music.hpp>

/*
	Note: This is a Singleton
*/
class MusicPlayer
{
  public:
    MusicPlayer(const MusicPlayer&) = delete;
    MusicPlayer(MusicPlayer&&) = delete;
    MusicPlayer& operator=(const MusicPlayer&) = delete;
    MusicPlayer& operator=(MusicPlayer&&) = delete;

    static MusicPlayer& instance();
    void initialize();
    void terminate();

    static void play(const std::string& key, float volume = 100.f);

  private:
    MusicPlayer() {}

    class Task
    {
      public:
        Task(std::string key, float volume) :
            key(key),
            volume(volume)
        {
        }
        std::string key;
        float volume;
    };

    //ConcurrentQueue<std::shared_ptr<sf::Music>> m_music;
    sf::Music m_music;
    bool m_done{false};
    std::unique_ptr<std::thread> m_thread;
    //ConcurrentQueue<Task> m_tasks;
    std::condition_variable m_eventTasks;
    //std::mutex m_mutexTasks;
};