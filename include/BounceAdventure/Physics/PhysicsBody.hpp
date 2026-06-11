#pragma once

#include <SFML/System/Vector2.hpp>

namespace BounceAdventure
{
struct PhysicsBody
{
    sf::Vector2f position{};
    sf::Vector2f velocity{};
    sf::Vector2f acceleration{};
    float radius = 0.0f;
    bool grounded = false;
};
}
