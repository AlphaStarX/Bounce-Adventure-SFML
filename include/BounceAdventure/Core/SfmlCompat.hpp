#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace BounceAdventure
{
class SfmlCompat
{
public:
#if SFML_VERSION_MAJOR >= 3
    static bool isClosed(const sf::Event& event)
    {
        return event.is<sf::Event::Closed>();
    }

    static bool isKeyPressed(const sf::Event& event, sf::Keyboard::Key& key)
    {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            key = keyPressed->code;
            return true;
        }
        return false;
    }

    static bool isKeyReleased(const sf::Event& event, sf::Keyboard::Key& key)
    {
        if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>())
        {
            key = keyReleased->code;
            return true;
        }
        return false;
    }

    static sf::Keyboard::Key keyA() { return sf::Keyboard::Key::A; }
    static sf::Keyboard::Key keyD() { return sf::Keyboard::Key::D; }
    static sf::Keyboard::Key keySpace() { return sf::Keyboard::Key::Space; }
    static sf::Keyboard::Key keyEscape() { return sf::Keyboard::Key::Escape; }
    static sf::Keyboard::Key keyEnter() { return sf::Keyboard::Key::Enter; }
    static sf::Keyboard::Key keyBackspace() { return sf::Keyboard::Key::Backspace; }
    static sf::Keyboard::Key keyUnknown() { return sf::Keyboard::Key::Unknown; }

    static sf::Vector2f rectPosition(const sf::FloatRect& rect) { return rect.position; }
    static sf::Vector2f rectSize(const sf::FloatRect& rect) { return rect.size; }
    static sf::FloatRect makeRect(sf::Vector2f position, sf::Vector2f size) { return sf::FloatRect(position, size); }
#else
    static bool isClosed(const sf::Event& event)
    {
        return event.type == sf::Event::Closed;
    }

    static bool isKeyPressed(const sf::Event& event, sf::Keyboard::Key& key)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            key = event.key.code;
            return true;
        }
        return false;
    }

    static bool isKeyReleased(const sf::Event& event, sf::Keyboard::Key& key)
    {
        if (event.type == sf::Event::KeyReleased)
        {
            key = event.key.code;
            return true;
        }
        return false;
    }

    static sf::Keyboard::Key keyA() { return sf::Keyboard::A; }
    static sf::Keyboard::Key keyD() { return sf::Keyboard::D; }
    static sf::Keyboard::Key keySpace() { return sf::Keyboard::Space; }
    static sf::Keyboard::Key keyEscape() { return sf::Keyboard::Escape; }
    static sf::Keyboard::Key keyEnter() { return sf::Keyboard::Enter; }
    static sf::Keyboard::Key keyBackspace() { return sf::Keyboard::BackSpace; }
    static sf::Keyboard::Key keyUnknown() { return sf::Keyboard::Unknown; }

    static sf::Vector2f rectPosition(const sf::FloatRect& rect) { return {rect.left, rect.top}; }
    static sf::Vector2f rectSize(const sf::FloatRect& rect) { return {rect.width, rect.height}; }
    static sf::FloatRect makeRect(sf::Vector2f position, sf::Vector2f size)
    {
        return sf::FloatRect(position.x, position.y, size.x, size.y);
    }
#endif
};
}
