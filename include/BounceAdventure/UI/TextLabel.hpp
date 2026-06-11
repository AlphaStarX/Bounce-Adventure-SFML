#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Config.hpp>
#include <string>

namespace BounceAdventure
{
enum class TextAlignment
{
    Left,
    Center,
    Right
};

class TextLabel
{
public:
    TextLabel(const sf::Font& font, const std::string& text = "", unsigned int characterSize = 24);

    void setText(const std::string& text);
    void setCharacterSize(unsigned int size);
    void setFillColor(sf::Color color);
    void setPosition(sf::Vector2f position);
    void setAlignment(TextAlignment alignment);

    sf::Vector2f position() const;
    sf::FloatRect bounds() const;
    std::string text() const;

    void draw(sf::RenderWindow& window) const;

private:
    void updateOrigin();

    sf::Text m_text;
    TextAlignment m_alignment = TextAlignment::Left;
};
}
