#include "BounceAdventure/UI/Button.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

namespace BounceAdventure
{
Button::Button(const sf::Font& font, const std::string& text, sf::Vector2f position, sf::Vector2f size)
    : m_label(font, text, 20)
    , m_position(position)
    , m_size(size)
{
    m_background.setSize(size);
    m_background.setFillColor(sf::Color(40, 44, 52));
    m_background.setOutlineColor(sf::Color(100, 110, 120));
    m_background.setOutlineThickness(2.0f);

#if SFML_VERSION_MAJOR >= 3
    m_background.setOrigin(size * 0.5f);
#else
    m_background.setOrigin(size.x * 0.5f, size.y * 0.5f);
#endif

    m_label.setAlignment(TextAlignment::Center);
    m_label.setFillColor(sf::Color::White);

    syncLayout();
}

void Button::update(const sf::RenderWindow& window)
{
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    const sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

    m_isHovered = m_background.getGlobalBounds().contains(worldMousePos);

    if (m_isHovered)
    {
        m_background.setFillColor(sf::Color(60, 68, 80));
        m_background.setOutlineColor(sf::Color(140, 200, 255));
        m_label.setFillColor(sf::Color(140, 200, 255));
    }
    else
    {
        m_background.setFillColor(sf::Color(40, 44, 52));
        m_background.setOutlineColor(sf::Color(100, 110, 120));
        m_label.setFillColor(sf::Color::White);
    }
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    static_cast<void>(window);

#if SFML_VERSION_MAJOR >= 3
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left && m_isHovered)
        {
            if (m_callback)
            {
                m_callback();
            }
        }
    }
#else
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left && m_isHovered)
        {
            if (m_callback)
            {
                m_callback();
            }
        }
    }
#endif
}

void Button::setCallback(std::function<void()> callback)
{
    m_callback = std::move(callback);
}

void Button::setPosition(sf::Vector2f position)
{
    m_position = position;
    syncLayout();
}

void Button::setSize(sf::Vector2f size)
{
    m_size = size;
    m_background.setSize(size);
#if SFML_VERSION_MAJOR >= 3
    m_background.setOrigin(size * 0.5f);
#else
    m_background.setOrigin(size.x * 0.5f, size.y * 0.5f);
#endif
    syncLayout();
}

bool Button::isHovered() const
{
    return m_isHovered;
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(m_background);
    m_label.draw(window);
}

void Button::syncLayout()
{
    m_background.setPosition(m_position);
    m_label.setPosition(m_position);
}
}
