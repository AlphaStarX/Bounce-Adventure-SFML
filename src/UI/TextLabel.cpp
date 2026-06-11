#include "BounceAdventure/UI/TextLabel.hpp"

namespace BounceAdventure
{
#if SFML_VERSION_MAJOR >= 3
TextLabel::TextLabel(const sf::Font& font, const std::string& text, unsigned int characterSize)
    : m_text(font, text, characterSize)
{
    updateOrigin();
}
#else
TextLabel::TextLabel(const sf::Font& font, const std::string& text, unsigned int characterSize)
{
    m_text.setFont(font);
    m_text.setString(text);
    m_text.setCharacterSize(characterSize);
    updateOrigin();
}
#endif

void TextLabel::setText(const std::string& text)
{
    m_text.setString(text);
    updateOrigin();
}

void TextLabel::setCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
    updateOrigin();
}

void TextLabel::setFillColor(sf::Color color)
{
    m_text.setFillColor(color);
}

void TextLabel::setPosition(sf::Vector2f position)
{
    m_text.setPosition(position);
    updateOrigin();
}

void TextLabel::setAlignment(TextAlignment alignment)
{
    m_alignment = alignment;
    updateOrigin();
}

sf::Vector2f TextLabel::position() const
{
    return m_text.getPosition();
}

sf::FloatRect TextLabel::bounds() const
{
    return m_text.getGlobalBounds();
}

std::string TextLabel::text() const
{
    return m_text.getString().toAnsiString();
}

void TextLabel::draw(sf::RenderWindow& window) const
{
    window.draw(m_text);
}

void TextLabel::updateOrigin()
{
    const sf::FloatRect bounds = m_text.getLocalBounds();
    sf::Vector2f origin{0.0f, 0.0f};

#if SFML_VERSION_MAJOR >= 3
    float left = bounds.position.x;
    float top = bounds.position.y;
    float width = bounds.size.x;
    float height = bounds.size.y;
#else
    float left = bounds.left;
    float top = bounds.top;
    float width = bounds.width;
    float height = bounds.height;
#endif

    switch (m_alignment)
    {
        case TextAlignment::Left:
            origin = {left, top};
            break;
        case TextAlignment::Center:
            origin = {left + width * 0.5f, top + height * 0.5f};
            break;
        case TextAlignment::Right:
            origin = {left + width, top};
            break;
    }

#if SFML_VERSION_MAJOR >= 3
    m_text.setOrigin(origin);
#else
    m_text.setOrigin(origin.x, origin.y);
#endif
}
}
