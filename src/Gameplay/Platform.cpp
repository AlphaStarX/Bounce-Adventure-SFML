#include "BounceAdventure/Gameplay/Platform.hpp"

namespace BounceAdventure
{
Platform::Platform(sf::Vector2f position, sf::Vector2f size)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(82, 92, 118));
}

const sf::FloatRect Platform::bounds() const
{
    return m_shape.getGlobalBounds();
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}
}
