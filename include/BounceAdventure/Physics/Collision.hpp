#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace BounceAdventure
{
struct CircleCollider
{
    sf::Vector2f center{};
    float radius = 0.0f;
};

struct CollisionResult
{
    bool collided = false;
    sf::Vector2f normal{};
    float depth = 0.0f;
};

class Collision
{
public:
    static bool intersects(const sf::FloatRect& a, const sf::FloatRect& b);
    static bool intersects(const CircleCollider& circle, const sf::FloatRect& rect);
    static bool contains(const sf::FloatRect& rect, sf::Vector2f point);

    static CollisionResult resolveCircleRect(const CircleCollider& circle, const sf::FloatRect& rect);
};
}
