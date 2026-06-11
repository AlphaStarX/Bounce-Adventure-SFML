#include "BounceAdventure/Gameplay/Goal.hpp"

namespace BounceAdventure
{
Goal::Goal(sf::Vector2f position, sf::Vector2f size)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(76, 201, 124, 180));
    m_shape.setOutlineColor(sf::Color(180, 255, 200));
    m_shape.setOutlineThickness(3.0f);
}

const sf::FloatRect Goal::bounds() const
{
    return m_shape.getGlobalBounds();
}

void Goal::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}
}
