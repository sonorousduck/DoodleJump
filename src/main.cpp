#include "GameModel.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <latch>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include "misc/Configuration.hpp"
#include "misc/ConfigurationPath.hpp"
#include "misc/Content.hpp"
#include "misc/ContentKey.hpp"

//
// This should not be in the Configuration.hpp header because client/server
// will have different configuration files.
const std::string CONFIG_SETTINGS_FILENAME = "client.settings.json";
const std::string CONFIG_DEVELOPER_FILENAME = "client.developer.json";
const std::string CONFIG_SCORES_FILENAME = "client.scores.json";


auto readConfiguration()
{
    // Reference: https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
    // Using Jerry's answer, because it was benchmarked to be quite fast, even though the config files are small.
    std::ifstream inSettings(CONFIG_SETTINGS_FILENAME);
    std::stringstream bufferSettings;
    bufferSettings << inSettings.rdbuf();
    inSettings.close();

    std::stringstream bufferDeveloper;
    std::ifstream inDeveloper(CONFIG_DEVELOPER_FILENAME);
    if (inDeveloper)
    {
        bufferDeveloper << inDeveloper.rdbuf();
        inDeveloper.close();
    }

    return Configuration::instance().initialize(bufferSettings.str(), bufferDeveloper.str());
}

// --------------------------------------------------------------
//
// Save the current configuration to the config file.
//
// --------------------------------------------------------------
void saveConfiguration()
{
    auto json = Configuration::instance().serialize();
    std::ofstream ofFile(CONFIG_SETTINGS_FILENAME);
    ofFile << json;
    ofFile.close();
}



std::shared_ptr<sf::RenderWindow> prepareWindow()
{
    //
    // Create the window : The settings parameter isn't necessary for what I'm doing, but leaving it here for reference
    sf::ContextSettings settings;

    int style = sf::Style::None;
    if (Configuration::get<bool>(config::GRAPHICS_FULL_SCREEN))
    {
        style = sf::Style::Fullscreen;
        //
        // Verify the config resolution is an available full-screen mode, if not, select
        // the first full-screen resolution by default;
        /*auto modes = sf::VideoMode::getFullscreenModes();
        auto isValidMode = std::any_of(modes.begin(), modes.end(),
                                       [](auto mode) {
                                           return mode.width == Configuration::get<std::uint16_t>(config::GRAPHICS_WIDTH) &&
                                                  mode.height == Configuration::get<std::uint16_t>(config::GRAPHICS_HEIGHT) &&
                                                  mode.bitsPerPixel == Configuration::get<std::uint8_t>(config::GRAPHICS_BPP);
                                       });
        if (!isValidMode)
        {
            auto mode = *modes.begin();
            Configuration::set<std::uint16_t>(config::GRAPHICS_WIDTH, static_cast<std::uint16_t>(mode.width));
            Configuration::set<std::uint16_t>(config::GRAPHICS_HEIGHT, static_cast<std::uint16_t>(mode.height));
            Configuration::set<std::uint8_t>(config::GRAPHICS_BPP, static_cast<std::uint8_t>(mode.bitsPerPixel));
        }*/

        //
        // By definition, use whatever resolution the desktop is in
        auto desktop = sf::VideoMode::getDesktopMode();
        Configuration::getGraphics().setResolution({desktop.width, desktop.height});
        Configuration::getGraphics().setBpp(desktop.bitsPerPixel);
    }
    else
    {
        style = sf::Style::Titlebar | sf::Style::Close;
        Configuration::getGraphics().setResolution({Configuration::get<std::uint16_t>(config::GRAPHICS_WIDTH),
                                                    Configuration::get<std::uint16_t>(config::GRAPHICS_HEIGHT)});
        Configuration::getGraphics().setBpp(Configuration::get<std::uint8_t>(config::GRAPHICS_BPP));
    }
    auto window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(
            Configuration::getGraphics().getResolution().width,
            Configuration::getGraphics().getResolution().height,
            Configuration::getGraphics().getBpp()),
        "Doodle Jump",
        style,
        settings);

    window->setVerticalSyncEnabled(Configuration::get<bool>(config::GRAPHICS_VSYNC));

    return window;
}

void prepareView(std::shared_ptr<sf::RenderWindow> window)
{
    //
    // The aspect ratio is needed in order to know how to organize the viewport
    // for the "game play" area used for the demonstrations.
    auto aspectRatio = static_cast<float>(window->getSize().x) / window->getSize().y;

    //
    // Get the view coordinates to be square, based on the aspect ratio of the window
    if (aspectRatio > 1.0)
    {
        Configuration::getGraphics().setViewCoordinates(
            {Configuration::getGraphics().getViewCoordinates().width * aspectRatio,
             Configuration::getGraphics().getViewCoordinates().height});
    }
    else
    {
        Configuration::getGraphics().setViewCoordinates(
            {Configuration::getGraphics().getViewCoordinates().width,
             Configuration::getGraphics().getViewCoordinates().height * (1.0f / aspectRatio)});
    }

    // Have to set the view after preparing it
    sf::View view({0.0f, 0.0f}, Configuration::getGraphics().getViewCoordinates());
    window->setView(view);
}

void startLoadingGameContent()
{
    //std::vector<std::pair<std::string, config::config_path>> fonts{
    //    {content::KEY_FONT_DEVELOPER_HEX_COORDS, config::DEVELOPER_HEX_COORDS_FONT_FILENAME}};

    //for (auto&& [keyContent, keyConfig] : fonts)
    //{
    //    if (!Content::has<sf::Font>(keyContent))
    //    {
    //        Content::load<sf::Font>(keyContent, Configuration::get<std::string>(keyConfig), nullptr, nullptr);
    //    }
    //}

    //
    // Sounds
    //std::vector<std::pair<std::string, config::config_path>> sounds{
    //    {content::KEY_AUDIO_STEP, config::AUDIO_GAMEPLAY_STEP},
    //    {content::KEY_AUDIO_SINK, config::AUDIO_GAMEPLAY_SINK},
    //    {content::KEY_AUDIO_BURN, config::AUDIO_GAMEPLAY_BURN},
    //    {content::KEY_AUDIO_RULE_CHANGED, config::AUDIO_GAMEPLAY_RULE_CHANGED},
    //    {content::KEY_AUDIO_LEVEL_COMPLETE, config::AUDIO_GAMEPLAY_LEVEL_COMPLETE}};

    //for (auto&& [keyContent, keyConfig] : sounds)
    //{
    //    if (!Content::has<sf::SoundBuffer>(keyContent))
    //    {
    //        Content::load<sf::SoundBuffer>(keyContent, Configuration::get<std::string>(keyConfig), nullptr, nullptr);
    //    }
    //}

    //
    // Background Music
    if (!Content::has<sf::Music>(content::KEY_MUSIC_GENERIC))
    {
        Content::load<sf::Music>(content::KEY_MUSIC_GENERIC, Configuration::get<std::string>(config::MUSIC_BACKGROUND), nullptr, nullptr);
    }
}




int main()
{
    // Create and activate the window for rendering on main thread
    auto window = prepareWindow();
    prepareView(window);
    window->setActive(true);

    // Initialize game model
    GameModel model;
    if (!model.initialize(window->getView().getSize()))
    {
        std::cout << "Game model failed to initialize, terminating..." << std::endl;
        exit(0);
    }

    // Get the initial time-stamp
    auto previousTime = std::chrono::steady_clock::now();

    // Get the Window loop running, gameloop runs inside this loop

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                model.signalKeyPressed(event.key);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                model.signalKeyReleased(event.key);
            }
        }

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime);
        previousTime = currentTime;

        // Update the game model
        model.update(elapsedTime, window);

        // Display the window finally after the update has finished
        window->display();
    }

    return 0;
}