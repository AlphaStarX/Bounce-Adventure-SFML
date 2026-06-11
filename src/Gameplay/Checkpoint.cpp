#include "BounceAdventure/Gameplay/Checkpoint.hpp"

namespace BounceAdventure
{
Checkpoint::Checkpoint(sf::Vector2f position, sf::Vector2f size)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color(255, 200, 80));
    m_shape.setOutlineColor(sf::Color(255, 240, 180));
    m_shape.setOutlineThickness(3.0f);
}

const sf::FloatRect Checkpoint::bounds() const
{
    return m_shape.getGlobalBounds();
}

sf::Vector2f Checkpoint::respawnPosition() const
{
    return m_shape.getPosition() + sf::Vector2f{m_shape.getSize().x * 0.5f, 0.0f};
}

bool Checkpoint::isActivated() const
{
    return m_active;
}

void Checkpoint::activate()
{
    m_active = true;
    m_shape.setFillColor(sf::Color(100, 255, 120));
    m_shape.setOutlineColor(sf::Color(180, 255, 200));
}

void Checkpoint::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}
}
