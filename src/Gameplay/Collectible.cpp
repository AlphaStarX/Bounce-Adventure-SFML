#include "BounceAdventure/Gameplay/Collectible.hpp"

#include <SFML/Config.hpp>

namespace BounceAdventure
{
Collectible::Collectible(sf::Vector2f position, float radius)
{
    m_shape.setRadius(radius);
#if SFML_VERSION_MAJOR >= 3
    m_shape.setOrigin({radius, radius});
#else
    m_shape.setOrigin(radius, radius);
#endif
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color(255, 215, 0));
    m_shape.setOutlineColor(sf::Color(255, 250, 180));
    m_shape.setOutlineThickness(2.0f);
}

const sf::FloatRect Collectible::bounds() const
{
    return m_shape.getGlobalBounds();
}

float Collectible::radius() const
{
    return m_shape.getRadius();
}

bool Collectible::isCollected() const
{
    return m_collected;
}

void Collectible::collect()
{
    m_collected = true;
}

void Collectible::draw(sf::RenderWindow& window) const
{
    if (!m_collected)
    {
        window.draw(m_shape);
    }
}
}
