#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace BounceAdventure
{
class Goal
{
public:
    Goal() = default;
    Goal(sf::Vector2f position, sf::Vector2f size);

    const sf::FloatRect bounds() const;
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape m_shape;
};
}
