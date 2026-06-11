#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <string>

namespace BounceAdventure
{
class WindowManager
{
public:
    WindowManager(unsigned int width, unsigned int height, const std::string& title);

    sf::RenderWindow& window();
    const sf::RenderWindow& window() const;

    bool isOpen() const;
    void close();

private:
    sf::RenderWindow m_window;
};
}
