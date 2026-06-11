#pragma once

#include "BounceAdventure/UI/TextLabel.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <string>

namespace BounceAdventure
{
class Button
{
public:
    Button(const sf::Font& font, const std::string& text, sf::Vector2f position, sf::Vector2f size);

    void update(const sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    void setCallback(std::function<void()> callback);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);

    bool isHovered() const;

    void draw(sf::RenderWindow& window) const;

private:
    void syncLayout();

    sf::RectangleShape m_background;
    TextLabel m_label;
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    std::function<void()> m_callback;
    bool m_isHovered = false;
};
}
