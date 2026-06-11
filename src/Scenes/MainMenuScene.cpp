#include "BounceAdventure/Scenes/MainMenuScene.hpp"
#include "BounceAdventure/Scenes/GameScene.hpp"
#include "BounceAdventure/Scenes/LevelSelectScene.hpp"
#include "BounceAdventure/Core/GameConfig.hpp"

namespace BounceAdventure
{
MainMenuScene::MainMenuScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, sf::RenderWindow& window)
    : m_sceneManager(sceneManager)
    , m_input(input)
    , m_assets(assets)
    , m_window(window)
    , m_title(assets.font("default", "C:/Windows/Fonts/arial.ttf"), "BOUNCE ADVENTURE", 54)
    , m_subtitle(assets.font("default", "C:/Windows/Fonts/arial.ttf"), "Modern C++ & SFML 2D Platformer", 20)
{
    const float centerX = static_cast<float>(GameConfig::WindowWidth) * 0.5f;

    m_title.setAlignment(TextAlignment::Center);
    m_title.setFillColor(sf::Color(230, 80, 68));
    m_title.setPosition({centerX, 180.0f});

    m_subtitle.setAlignment(TextAlignment::Center);
    m_subtitle.setFillColor(sf::Color(180, 190, 200));
    m_subtitle.setPosition({centerX, 250.0f});

    const sf::Font& font = assets.font("default", "C:/Windows/Fonts/arial.ttf");

    // Start Game Button
    Button startButton(font, "Start Game", {centerX, 340.0f}, {240.0f, 50.0f});
    startButton.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_window, 1));
    });
    m_buttons.push_back(std::move(startButton));

    // Select Level Button
    Button selectButton(font, "Select Level", {centerX, 410.0f}, {240.0f, 50.0f});
    selectButton.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<LevelSelectScene>(m_sceneManager, m_input, m_assets, m_window));
    });
    m_buttons.push_back(std::move(selectButton));

    // Quit Button
    Button quitButton(font, "Quit Game", {centerX, 480.0f}, {240.0f, 50.0f});
    quitButton.setCallback([this]() {
        m_window.close();
    });
    m_buttons.push_back(std::move(quitButton));
}

void MainMenuScene::handleEvent(const sf::Event& event)
{
    for (auto& button : m_buttons)
    {
        button.handleEvent(event, m_window);
    }
}

void MainMenuScene::update(float deltaTime)
{
    static_cast<void>(deltaTime);
    for (auto& button : m_buttons)
    {
        button.update(m_window);
    }
}

void MainMenuScene::render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    m_title.draw(window);
    m_subtitle.draw(window);
    for (const auto& button : m_buttons)
    {
        button.draw(window);
    }
}
}
