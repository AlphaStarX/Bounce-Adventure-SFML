#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace BounceAdventure
{
class Collectible
{
public:
    Collectible() = default;
    Collectible(sf::Vector2f position, float radius);

    const sf::FloatRect bounds() const;
    float radius() const;
    bool isCollected() const;
    void collect();
    void draw(sf::RenderWindow& window) const;

private:
    sf::CircleShape m_shape;
    bool m_collected = false;
};
}
