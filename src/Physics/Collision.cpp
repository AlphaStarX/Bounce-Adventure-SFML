#include "BounceAdventure/Physics/Collision.hpp"

#include "BounceAdventure/Core/SfmlCompat.hpp"

#include <algorithm>
#include <cmath>

namespace BounceAdventure
{
bool Collision::intersects(const sf::FloatRect& a, const sf::FloatRect& b)
{
#if SFML_VERSION_MAJOR >= 3
    return a.findIntersection(b).has_value();
#else
    return a.intersects(b);
#endif
}

bool Collision::intersects(const CircleCollider& circle, const sf::FloatRect& rect)
{
    return resolveCircleRect(circle, rect).collided;
}

bool Collision::contains(const sf::FloatRect& rect, sf::Vector2f point)
{
    return rect.contains(point);
}

CollisionResult Collision::resolveCircleRect(const CircleCollider& circle, const sf::FloatRect& rect)
{
    const sf::Vector2f rectPosition = SfmlCompat::rectPosition(rect);
    const sf::Vector2f rectSize = SfmlCompat::rectSize(rect);
    const float closestX = std::clamp(circle.center.x, rectPosition.x, rectPosition.x + rectSize.x);
    const float closestY = std::clamp(circle.center.y, rectPosition.y, rectPosition.y + rectSize.y);

    const sf::Vector2f delta{circle.center.x - closestX, circle.center.y - closestY};
    const float distanceSquared = delta.x * delta.x + delta.y * delta.y;
    const float radiusSquared = circle.radius * circle.radius;

    if (distanceSquared >= radiusSquared)
    {
        return {};
    }

    if (distanceSquared > 0.0f)
    {
        const float distance = std::sqrt(distanceSquared);
        return {true, {delta.x / distance, delta.y / distance}, circle.radius - distance};
    }

    const float leftDepth = std::abs(circle.center.x - rectPosition.x);
    const float rightDepth = std::abs((rectPosition.x + rectSize.x) - circle.center.x);
    const float topDepth = std::abs(circle.center.y - rectPosition.y);
    const float bottomDepth = std::abs((rectPosition.y + rectSize.y) - circle.center.y);

    const float minDepth = std::min({leftDepth, rightDepth, topDepth, bottomDepth});
    if (minDepth == leftDepth)
    {
        return {true, {-1.0f, 0.0f}, circle.radius};
    }
    if (minDepth == rightDepth)
    {
        return {true, {1.0f, 0.0f}, circle.radius};
    }
    if (minDepth == topDepth)
    {
        return {true, {0.0f, -1.0f}, circle.radius};
    }

    return {true, {0.0f, 1.0f}, circle.radius};
}
}
