#pragma once

#include "BounceAdventure/Core/AssetManager.hpp"
#include "BounceAdventure/Core/AudioManager.hpp"
#include "BounceAdventure/Core/InputManager.hpp"
#include "BounceAdventure/Core/SceneManager.hpp"
#include "BounceAdventure/Core/WindowManager.hpp"

#include <SFML/System/Clock.hpp>

namespace BounceAdventure
{
class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    WindowManager m_windowManager;
    InputManager m_inputManager;
    AssetManager m_assetManager;
    AudioManager m_audioManager;
    SceneManager m_sceneManager;
    sf::Clock m_clock;
};
}
