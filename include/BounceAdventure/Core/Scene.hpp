#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace BounceAdventure
{
class Scene
{
public:
    virtual ~Scene() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
}
