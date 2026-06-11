#include "BounceAdventure/Gameplay/Hazard.hpp"

namespace BounceAdventure
{
Hazard::Hazard(sf::Vector2f position, sf::Vector2f size)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(210, 50, 60));
    m_shape.setOutlineColor(sf::Color(255, 120, 110));
    m_shape.setOutlineThickness(3.0f);
}

const sf::FloatRect Hazard::bounds() const
{
    return m_shape.getGlobalBounds();
}

void Hazard::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}
}
