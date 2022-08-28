#include "MusicPlayer.hpp"


// -----------------------------------------------------------------
//
// Using the Meyer's Singleton technique...this is thread safe
//
// -----------------------------------------------------------------
MusicPlayer& MusicPlayer::instance()
{
    static MusicPlayer instance;
    return instance;
}

// --------------------------------------------------------------
//
// Call this one time at program startup.  This gets the worker
// thread up and running.
//
// --------------------------------------------------------------
void MusicPlayer::initialize()
{
    //m_thread = std::make_unique<std::thread>(&MusicPlayer::run, this);

    // Create a queue of 10 sf::Music objects that we'll cycle through
    // Sound we had a queue of 100, but music will be MUCH less rare, if
    // this is even necessary at all. Which I have my doubts
}

// --------------------------------------------------------------
//
// Call this one time as the program is shutting down.  This gets
// the worker thread gracefully terminated.
//
// --------------------------------------------------------------
void MusicPlayer::terminate()
{
    m_done = true;
    m_eventTasks.notify_one();
    m_thread->join();
}

// --------------------------------------------------------------
//
// Public method to allow client code to initiate a sound.
//
// --------------------------------------------------------------
void MusicPlayer::play(const std::string& key, float volume)
{
    instance().m_music.stop();
    instance().m_music.openFromFile(key);
    instance().m_music.setVolume(volume);
    instance().m_music.setLoop(true);
    instance().m_music.play();
    instance().m_eventTasks.notify_one();
}
