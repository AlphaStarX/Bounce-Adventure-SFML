#pragma once

#include "BounceAdventure/Physics/Collision.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace BounceAdventure
{
class Hazard
{
public:
    Hazard() = default;
    Hazard(sf::Vector2f position, sf::Vector2f size);

    const sf::FloatRect bounds() const;
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape m_shape;
};
}
