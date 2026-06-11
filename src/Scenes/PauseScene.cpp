#include "BounceAdventure/Scenes/PauseScene.hpp"
#include "BounceAdventure/Scenes/MainMenuScene.hpp"
#include "BounceAdventure/Core/GameConfig.hpp"
#include "BounceAdventure/Core/SfmlCompat.hpp"

namespace BounceAdventure
{
PauseScene::PauseScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, sf::RenderWindow& window)
    : m_sceneManager(sceneManager)
    , m_input(input)
    , m_assets(assets)
    , m_window(window)
    , m_title(assets.font("default", "assets/fonts/arial.ttf"), "GAME PAUSED", 44)
{
    const float centerX = static_cast<float>(GameConfig::WindowWidth) * 0.5f;

    m_title.setAlignment(TextAlignment::Center);
    m_title.setFillColor(sf::Color(255, 200, 100));
    m_title.setPosition({centerX, 200.0f});

    const sf::Font& font = assets.font("default", "assets/fonts/arial.ttf");

    // Resume Button
    Button resumeButton(font, "Resume Game", {centerX, 340.0f}, {260.0f, 50.0f});
    resumeButton.setCallback([this]() {
        m_sceneManager.pop();
    });
    m_buttons.push_back(std::move(resumeButton));

    // Exit Button
    Button exitButton(font, "Main Menu", {centerX, 420.0f}, {260.0f, 50.0f});
    exitButton.setCallback([this]() {
        m_sceneManager.clear();
        m_sceneManager.push(std::make_unique<MainMenuScene>(m_sceneManager, m_input, m_assets, m_window));
    });
    m_buttons.push_back(std::move(exitButton));
}

void PauseScene::handleEvent(const sf::Event& event)
{
    sf::Keyboard::Key key = SfmlCompat::keyUnknown();
    if (SfmlCompat::isKeyPressed(event, key) && key == SfmlCompat::keyEscape())
    {
        m_sceneManager.pop();
        return;
    }

    for (auto& button : m_buttons)
    {
        button.handleEvent(event, m_window);
    }
}

void PauseScene::update(float deltaTime)
{
    static_cast<void>(deltaTime);
    for (auto& button : m_buttons)
    {
        button.update(m_window);
    }
}

void PauseScene::render(sf::RenderWindow& window)
{
    window.setView(window.getDefaultView());
    m_title.draw(window);
    for (const auto& button : m_buttons)
    {
        button.draw(window);
    }
}
}
