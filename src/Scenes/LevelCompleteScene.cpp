#include "BounceAdventure/Scenes/LevelCompleteScene.hpp"
#include "BounceAdventure/Scenes/GameScene.hpp"
#include "BounceAdventure/Scenes/MainMenuScene.hpp"
#include "BounceAdventure/Core/GameConfig.hpp"

namespace BounceAdventure
{
LevelCompleteScene::LevelCompleteScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, sf::RenderWindow& window, int completedLevel, int coins)
    : m_sceneManager(sceneManager)
    , m_input(input)
    , m_assets(assets)
    , m_window(window)
    , m_title(assets.font("default", "assets/fonts/arial.ttf"), "LEVEL COMPLETE!", 44)
    , m_statsLabel(assets.font("default", "assets/fonts/arial.ttf"), "Coins Collected: " + std::to_string(coins), 24)
{
    const float centerX = static_cast<float>(GameConfig::WindowWidth) * 0.5f;

    m_title.setAlignment(TextAlignment::Center);
    m_title.setFillColor(sf::Color(100, 255, 150));
    m_title.setPosition({centerX, 200.0f});

    m_statsLabel.setAlignment(TextAlignment::Center);
    m_statsLabel.setFillColor(sf::Color::White);
    m_statsLabel.setPosition({centerX, 280.0f});

    const sf::Font& font = assets.font("default", "assets/fonts/arial.ttf");

    // Next Level Button
    Button nextButton(font, "Next Level", {centerX, 380.0f}, {240.0f, 50.0f});
    nextButton.setCallback([this, completedLevel, coins]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_window, completedLevel + 1, coins));
    });
    m_buttons.push_back(std::move(nextButton));

    // Main Menu Button
    Button menuButton(font, "Main Menu", {centerX, 460.0f}, {240.0f, 50.0f});
    menuButton.setCallback([this]() {
        m_sceneManager.clear();
        m_sceneManager.push(std::make_unique<MainMenuScene>(m_sceneManager, m_input, m_assets, m_window));
    });
    m_buttons.push_back(std::move(menuButton));
}

void LevelCompleteScene::handleEvent(const sf::Event& event)
{
    for (auto& button : m_buttons)
    {
        button.handleEvent(event, m_window);
    }
}

void LevelCompleteScene::update(float deltaTime)
{
    static_cast<void>(deltaTime);
    for (auto& button : m_buttons)
    {
        button.update(m_window);
    }
}

void LevelCompleteScene::render(sf::RenderWindow& window)
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
