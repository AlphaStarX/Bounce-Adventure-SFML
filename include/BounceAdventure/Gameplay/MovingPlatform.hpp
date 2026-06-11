#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace BounceAdventure
{
class MovingPlatform
{
public:
    MovingPlatform() = default;
    MovingPlatform(sf::Vector2f position, sf::Vector2f size, bool vertical, float travelDistance, float speed);

    sf::FloatRect bounds() const;
    sf::Vector2f position() const;
    sf::Vector2f velocity() const;

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_startPosition{};
    bool m_vertical = false;
    float m_travelDistance = 0.0f;
    float m_speed = 0.0f;
    float m_time = 0.0f;
    sf::Vector2f m_previousPosition{};
};
}
