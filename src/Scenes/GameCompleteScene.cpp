#include "BounceAdventure/Scenes/GameCompleteScene.hpp"
#include "BounceAdventure/Scenes/MainMenuScene.hpp"
#include "BounceAdventure/Core/GameConfig.hpp"

namespace BounceAdventure
{
GameCompleteScene::GameCompleteScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, sf::RenderWindow& window, int coins)
    : m_sceneManager(sceneManager)
    , m_input(input)
    , m_assets(assets)
    , m_window(window)
    , m_title(assets.font("default", "assets/fonts/arial.ttf"), "CONGRATULATIONS!", 44)
    , m_statsLabel(assets.font("default", "assets/fonts/arial.ttf"), "You Completed All Levels!\nTotal Coins: " + std::to_string(coins), 24)
{
    const float centerX = static_cast<float>(GameConfig::WindowWidth) * 0.5f;

    m_title.setAlignment(TextAlignment::Center);
    m_title.setFillColor(sf::Color(255, 215, 0)); // Gold color
    m_title.setPosition({centerX, 180.0f});

    m_statsLabel.setAlignment(TextAlignment::Center);
    m_statsLabel.setFillColor(sf::Color::White);
    m_statsLabel.setPosition({centerX, 280.0f});

    const sf::Font& font = assets.font("default", "assets/fonts/arial.ttf");

    // Main Menu Button
    Button menuButton(font, "Main Menu", {centerX, 420.0f}, {240.0f, 50.0f});
    menuButton.setCallback([this]() {
        m_sceneManager.clear();
        m_sceneManager.push(std::make_unique<MainMenuScene>(m_sceneManager, m_input, m_assets, m_window));
    });
    m_buttons.push_back(std::move(menuButton));
}

void GameCompleteScene::handleEvent(const sf::Event& event)
{
    for (auto& button : m_buttons)
    {
        button.handleEvent(event, m_window);
    }
}

void GameCompleteScene::update(float deltaTime)
{
    static_cast<void>(deltaTime);
    for (auto& button : m_buttons)
    {
        button.update(m_window);
    }
}

void GameCompleteScene::render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    m_title.draw(window);
    m_statsLabel.draw(window);
    for (const auto& button : m_buttons)
    {
        button.draw(window);
    }
}
}
