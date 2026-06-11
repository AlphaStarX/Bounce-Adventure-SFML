#pragma once

#include "BounceAdventure/Physics/Collision.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <vector>

namespace BounceAdventure
{
class CollisionSystem
{
public:
    CollisionResult firstCircleRectCollision(
        const CircleCollider& circle,
        const std::vector<sf::FloatRect>& rectangles) const;

    bool overlapsAny(const CircleCollider& circle, const std::vector<sf::FloatRect>& rectangles) const;
};
}
