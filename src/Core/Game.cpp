#include "BounceAdventure/Core/Game.hpp"

#include "BounceAdventure/Core/GameConfig.hpp"
#include "BounceAdventure/Core/SfmlCompat.hpp"
#include "BounceAdventure/Scenes/MainMenuScene.hpp"

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace BounceAdventure
{
Game::Game()
    : m_windowManager(GameConfig::WindowWidth, GameConfig::WindowHeight, GameConfig::WindowTitle)
{
    m_windowManager.window().setFramerateLimit(GameConfig::FrameRateLimit);
    m_sceneManager.push(std::make_unique<MainMenuScene>(m_sceneManager, m_inputManager, m_assetManager, m_windowManager.window()));
    m_sceneManager.processPendingChanges();
}

void Game::run()
{
    while (m_windowManager.isOpen())
    {
        const float deltaTime = m_clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
        m_sceneManager.processPendingChanges();
    }
}

void Game::processEvents()
{
    m_inputManager.beginFrame();

#if SFML_VERSION_MAJOR >= 3
    while (const auto event = m_windowManager.window().pollEvent())
    {
        m_inputManager.handleEvent(*event);

        if (SfmlCompat::isClosed(*event))
        {
            m_windowManager.close();
        }

        if (Scene* scene = m_sceneManager.current())
        {
            scene->handleEvent(*event);
        }
    }
#else
    sf::Event event{};
    while (m_windowManager.window().pollEvent(event))
    {
        m_inputManager.handleEvent(event);

        if (SfmlCompat::isClosed(event))
        {
            m_windowManager.close();
        }

        if (Scene* scene = m_sceneManager.current())
        {
            scene->handleEvent(event);
        }
    }
#endif
}

void Game::update(float deltaTime)
{
    if (Scene* scene = m_sceneManager.current())
    {
        scene->update(deltaTime);
    }
}

void Game::render()
{
    auto& window = m_windowManager.window();
    window.clear(sf::Color(20, 22, 28));
    if (Scene* scene = m_sceneManager.current())
    {
        scene->render(window);
    }
    window.display();
}
}
