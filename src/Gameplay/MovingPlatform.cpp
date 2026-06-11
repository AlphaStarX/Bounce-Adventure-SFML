#include "BounceAdventure/Gameplay/MovingPlatform.hpp"

#include <cmath>

namespace BounceAdventure
{
MovingPlatform::MovingPlatform(sf::Vector2f position, sf::Vector2f size, bool vertical, float travelDistance, float speed)
    : m_startPosition(position)
    , m_vertical(vertical)
    , m_travelDistance(travelDistance)
    , m_speed(speed)
{
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(120, 130, 160));
    m_shape.setOutlineColor(sf::Color(170, 180, 210));
    m_shape.setOutlineThickness(2.0f);

    m_shape.setPosition(position);
    m_previousPosition = position;
}

sf::FloatRect MovingPlatform::bounds() const
{
    return m_shape.getGlobalBounds();
}

sf::Vector2f MovingPlatform::position() const
{
    return m_shape.getPosition();
}

sf::Vector2f MovingPlatform::velocity() const
{
    return m_shape.getPosition() - m_previousPosition;
}

void MovingPlatform::update(float deltaTime)
{
    m_previousPosition = m_shape.getPosition();

    // Calculate angular frequency so m_speed represents actual average linear speed in pixels/sec
    const float angularFrequency = (3.14159265f * m_speed) / m_travelDistance;
    m_time += deltaTime * angularFrequency;

    const float offset = std::sin(m_time) * (m_travelDistance * 0.5f);

    if (m_vertical)
    {
        m_shape.setPosition({m_startPosition.x, m_startPosition.y + offset});
    }
    else
    {
        m_shape.setPosition({m_startPosition.x + offset, m_startPosition.y});
    }
}

void MovingPlatform::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}
}
