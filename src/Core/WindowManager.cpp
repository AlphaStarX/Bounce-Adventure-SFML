#include "BounceAdventure/Core/WindowManager.hpp"

#include <SFML/Config.hpp>
#include <SFML/Window/WindowEnums.hpp>

namespace BounceAdventure
{
WindowManager::WindowManager(unsigned int width, unsigned int height, const std::string& title)
#if SFML_VERSION_MAJOR >= 3
    : m_window(sf::VideoMode({width, height}), title, sf::Style::Close)
#else
    : m_window(sf::VideoMode(width, height), title, sf::Style::Close)
#endif
{
}

sf::RenderWindow& WindowManager::window()
{
    return m_window;
}

const sf::RenderWindow& WindowManager::window() const
{
    return m_window;
}

bool WindowManager::isOpen() const
{
    return m_window.isOpen();
}

void WindowManager::close()
{
    m_window.close();
}
}
