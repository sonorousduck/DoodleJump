#include "Content.hpp"
#include <iostream>

static const std::string CONTENT_PATH{"assets"};
static const std::string CONTENT_AUDIO_PATH{"audio"};
static const std::string CONTENT_MUSIC_PATH{"music"};




// -----------------------------------------------------------------
//
// Using the Meyer's Singleton technique...this is thread safe
//
// -----------------------------------------------------------------
Content& Content::instance()
{
    static Content instance;
    return instance;
}


// --------------------------------------------------------------
//
// Specialization on sf::SoundBuffer for loading an audio clip
//
// --------------------------------------------------------------
template <>
bool Content::loadImpl<sf::SoundBuffer>(LoadParams& params)
{
    std::filesystem::path path(CONTENT_PATH);
    path /= CONTENT_AUDIO_PATH;
    path /= params.filename;


    auto audio = std::make_shared<sf::SoundBuffer>();
    if (!audio->loadFromFile(path.string()))
    {
        return false;
    }

    instance().m_audioBuffers[params.key] = audio;
    instance().m_sound[params.key] = std::make_shared<sf::Sound>();
    instance().m_sound[params.key]->setBuffer(*audio);

}


// --------------------------------------------------------------
//
// Specialization on sf::SoundBuffer for loading an audio clip
//
// --------------------------------------------------------------
template <>
void Content::load<sf::SoundBuffer>(std::string key, std::string filename, std::function<void(std::string)> onComplete, std::function<void(std::string)> onError)
{
    //auto work = [=]()
    //{
    auto params = LoadParams{
        key,
        filename,
        onComplete,
        onError};
    bool success = loadImpl<sf::SoundBuffer>(params);
    Content::instance().loadComplete(success, params);
    //};

    Content::instance().m_tasksRemaining++;
    //auto task = ThreadPool::instance().createIOTask(work);
    //ThreadPool::instance().enqueueTask(task);
}

void Content::loadComplete(bool success, LoadParams& params)
{
    if (success)
    {
        std::cout << "finished loading: " << params.key << std::endl;
        m_tasksRemaining--;
    }
    else
    {
        m_contentError = true;
        std::cout << "error in loading: " << params.filename << std::endl;
        m_tasksRemaining--;
    }
    if (success && params.onComplete != nullptr)
    {
        params.onComplete(params.key);
    }
    else if (!success && params.onError != nullptr)
    {
        params.onError(params.filename);
    }
}

// --------------------------------------------------------------
//
// Specialization on sf::SoundBuffer for obtaining an audio clip
//
// --------------------------------------------------------------
template <>
std::shared_ptr<sf::SoundBuffer> Content::get(std::string key)
{
    return instance().m_audioBuffers[key];
}

template <>
std::shared_ptr<sf::Sound> Content::get(std::string key)
{
    return instance().m_sound[key];
}

// Only need has<sf::SoundBuffer>, because it is good for both sf::Sound and sf::SoundBuffer
template <>
bool Content::has<sf::SoundBuffer>(std::string key)
{
    return instance().m_audioBuffers.find(key) != instance().m_audioBuffers.end();
}