#include "BounceAdventure/Physics/CollisionSystem.hpp"

namespace BounceAdventure
{
CollisionResult CollisionSystem::firstCircleRectCollision(
    const CircleCollider& circle,
    const std::vector<sf::FloatRect>& rectangles) const
{
    for (const auto& rectangle : rectangles)
    {
        const CollisionResult result = Collision::resolveCircleRect(circle, rectangle);
        if (result.collided)
        {
            return result;
        }
    }

    return {};
}

bool CollisionSystem::overlapsAny(const CircleCollider& circle, const std::vector<sf::FloatRect>& rectangles) const
{
    for (const auto& rectangle : rectangles)
    {
        if (Collision::intersects(circle, rectangle))
        {
            return true;
        }
    }

    return false;
}
}
