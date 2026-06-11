#include "BounceAdventure/Scenes/LevelSelectScene.hpp"
#include "BounceAdventure/Scenes/GameScene.hpp"
#include "BounceAdventure/Scenes/MainMenuScene.hpp"
#include "BounceAdventure/Core/GameConfig.hpp"

namespace BounceAdventure
{
LevelSelectScene::LevelSelectScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, AudioManager& audio, sf::RenderWindow& window)
    : m_sceneManager(sceneManager)
    , m_input(input)
    , m_assets(assets)
    , m_audio(audio)
    , m_window(window)
    , m_title(assets.font("default", "assets/fonts/arial.ttf"), "SELECT LEVEL", 44)
{
    const float centerX = static_cast<float>(GameConfig::WindowWidth) * 0.5f;

    m_title.setAlignment(TextAlignment::Center);
    m_title.setFillColor(sf::Color(140, 200, 255));
    m_title.setPosition({centerX, 180.0f});

    const sf::Font& font = assets.font("default", "assets/fonts/arial.ttf");

    // Level buttons in a 2x3 grid
    const float y1 = 300.0f;
    const float y2 = 380.0f;
    const float xOffset = 200.0f;
    const sf::Vector2f btnSize{160.0f, 50.0f};

    // Row 1
    // Level 1
    Button lvl1(font, "Level 1", {centerX - xOffset, y1}, btnSize);
    lvl1.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_audio, m_window, 1));
    });
    m_buttons.push_back(std::move(lvl1));

    // Level 2
    Button lvl2(font, "Level 2", {centerX, y1}, btnSize);
    lvl2.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_audio, m_window, 2));
    });
    m_buttons.push_back(std::move(lvl2));

    // Level 3
    Button lvl3(font, "Level 3", {centerX + xOffset, y1}, btnSize);
    lvl3.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_audio, m_window, 3));
    });
    m_buttons.push_back(std::move(lvl3));

    // Row 2
    // Level 4
    Button lvl4(font, "Level 4", {centerX - xOffset, y2}, btnSize);
    lvl4.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_audio, m_window, 4));
    });
    m_buttons.push_back(std::move(lvl4));

    // Level 5
    Button lvl5(font, "Level 5", {centerX, y2}, btnSize);
    lvl5.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_audio, m_window, 5));
    });
    m_buttons.push_back(std::move(lvl5));

    // Level 6
    Button lvl6(font, "Level 6", {centerX + xOffset, y2}, btnSize);
    lvl6.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<GameScene>(m_sceneManager, m_input, m_assets, m_audio, m_window, 6));
    });
    m_buttons.push_back(std::move(lvl6));

    // Back to Menu Button
    Button backButton(font, "Back to Menu", {centerX, 480.0f}, {240.0f, 50.0f});
    backButton.setCallback([this]() {
        m_sceneManager.replace(std::make_unique<MainMenuScene>(m_sceneManager, m_input, m_assets, m_audio, m_window));
    });
    m_buttons.push_back(std::move(backButton));
}

void LevelSelectScene::handleEvent(const sf::Event& event)
{
    for (auto& button : m_buttons)
    {
        button.handleEvent(event, m_window);
    }
}

void LevelSelectScene::update(float deltaTime)
{
    static_cast<void>(deltaTime);
    for (auto& button : m_buttons)
    {
        button.update(m_window);
    }
}

void LevelSelectScene::render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    m_title.draw(window);
    for (const auto& button : m_buttons)
    {
        button.draw(window);
    }
}
}
