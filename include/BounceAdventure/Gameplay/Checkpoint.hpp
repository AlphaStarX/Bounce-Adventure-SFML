#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace BounceAdventure
{
class Checkpoint
{
public:
    Checkpoint() = default;
    Checkpoint(sf::Vector2f position, sf::Vector2f size);

    const sf::FloatRect bounds() const;
    sf::Vector2f respawnPosition() const;
    bool isActivated() const;
    void activate();
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape m_shape;
    bool m_active = false;
};
}
