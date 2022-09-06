#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <filesystem>
#include <thread>

class Content
{
  public:
    Content(const Content&) = delete;
    Content(Content&&) = delete;
    Content& operator=(const Content&) = delete;
    Content& operator=(Content&&) = delete;
    static Content& instance();

    template <typename T>
    static void load(std::string key, std::string filename, std::function<void(std::string)> onComplete = nullptr, std::function<void(std::string)> onError = nullptr);

    // This is a template with specializations, because can't overload on return type
    template <typename T>
    static std::shared_ptr<T> get(std::string key);

    template <typename T>
    static bool has(std::string key);

    bool anyPending() { return m_tasksRemaining > 0; }
    bool isError() { return m_contentError; }

  private:

    Content() {}

    class LoadParams
    {
      public:
        std::string key;
        std::string filename;
        std::function<void(std::string)> onComplete;
        std::function<void(std::string)> onError;
    };

    std::atomic_bool m_contentError{false};
    std::atomic_uint16_t m_tasksRemaining{0};


    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> m_audioBuffers;
    std::unordered_map<std::string, std::shared_ptr<sf::Sound>> m_sound;
    
    template <typename T>
    static bool loadImpl(LoadParams& params);

    void loadComplete(bool success, LoadParams& task);


};