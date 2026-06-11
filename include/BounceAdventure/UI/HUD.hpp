#pragma once

#include "BounceAdventure/Core/AssetManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace BounceAdventure
{
class HUD
{
public:
    explicit HUD(AssetManager& assets);

    void update(int health, int maxHealth, int coins, int totalCoins, int levelNumber, const std::string& levelName);
    void setMessage(const std::string& message);
    void clearMessage();

    void draw(sf::RenderWindow& window) const;

private:
    sf::Text m_healthText;
    sf::Text m_coinText;
    sf::Text m_levelText;
    sf::Text m_messageText;
    bool m_showMessage = false;
};
}
