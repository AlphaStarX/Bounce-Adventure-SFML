#include "BounceAdventure/UI/HUD.hpp"

#include "BounceAdventure/Core/GameConfig.hpp"
#include "BounceAdventure/Core/SfmlCompat.hpp"

#include <SFML/Config.hpp>
#include <algorithm>
#include <cmath>

namespace BounceAdventure
{
#if SFML_VERSION_MAJOR >= 3
HUD::HUD(AssetManager& assets)
    : m_healthText(assets.font("default", "C:/Windows/Fonts/arial.ttf")),
      m_coinText(assets.font("default", "C:/Windows/Fonts/arial.ttf")),
      m_levelText(assets.font("default", "C:/Windows/Fonts/arial.ttf")),
      m_messageText(assets.font("default", "C:/Windows/Fonts/arial.ttf"))
{
    const sf::Font& font = assets.font("default", "C:/Windows/Fonts/arial.ttf");
#else
HUD::HUD(AssetManager& assets)
{
    const std::filesystem::path fontPath = std::filesystem::path("C:/Windows/Fonts/arial.ttf");
    const sf::Font& font = assets.font("default", fontPath);

    m_healthText.setFont(font);
    m_coinText.setFont(font);
    m_levelText.setFont(font);
    m_messageText.setFont(font);
#endif

    m_healthText.setCharacterSize(24);
    m_coinText.setCharacterSize(24);
    m_levelText.setCharacterSize(20);
    m_messageText.setCharacterSize(48);

    m_healthText.setFillColor(sf::Color::White);
    m_coinText.setFillColor(sf::Color::White);
    m_levelText.setFillColor(sf::Color(200, 200, 200));
    m_messageText.setFillColor(sf::Color(100, 255, 150));

    m_healthText.setPosition({20.0f, 20.0f});
    m_coinText.setPosition({20.0f, 52.0f});
    m_levelText.setPosition({20.0f, 84.0f});
}

void HUD::update(int health, int maxHealth, int coins, int totalCoins, int levelNumber, const std::string& levelName)
{
    m_healthText.setString("Health: " + std::to_string(health) + "/" + std::to_string(maxHealth));
    m_coinText.setString("Coins: " + std::to_string(coins) + "/" + std::to_string(totalCoins));
    m_levelText.setString("Level " + std::to_string(levelNumber) + ": " + levelName);
}

void HUD::setMessage(const std::string& message)
{
    m_messageText.setString(message);
    m_showMessage = true;

    const sf::FloatRect bounds = m_messageText.getLocalBounds();
#if SFML_VERSION_MAJOR >= 3
    m_messageText.setOrigin({bounds.position.x + bounds.size.x * 0.5f, bounds.position.y + bounds.size.y * 0.5f});
#else
    m_messageText.setOrigin(bounds.left + bounds.width * 0.5f, bounds.top + bounds.height * 0.5f);
#endif
    m_messageText.setPosition({static_cast<float>(GameConfig::WindowWidth) * 0.5f, static_cast<float>(GameConfig::WindowHeight) * 0.5f});
}

void HUD::clearMessage()
{
    m_showMessage = false;
}

void HUD::draw(sf::RenderWindow& window) const
{
    const sf::View previousView = window.getView();
    window.setView(window.getDefaultView());

    window.draw(m_healthText);
    window.draw(m_coinText);
    window.draw(m_levelText);

    if (m_showMessage)
    {
        window.draw(m_messageText);
    }

    window.setView(previousView);
}
}
