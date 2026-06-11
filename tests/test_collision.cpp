#include "BounceAdventure/Physics/Collision.hpp"
#include "BounceAdventure/Physics/CollisionSystem.hpp"

#include "test_harness.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>

using namespace BounceAdventure;

namespace
{
constexpr float kEpsilon = 0.0001f;

bool approxEqual(float a, float b)
{
    return std::fabs(a - b) < kEpsilon;
}
} // namespace

TEST_CASE(Collision_RectsDoNotIntersect)
{
    const sf::FloatRect a{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const sf::FloatRect b{{20.0f, 20.0f}, {10.0f, 10.0f}};
    CHECK(!Collision::intersects(a, b));
    CHECK(!Collision::intersects(b, a));
}

TEST_CASE(Collision_RectsTouchingAtCornerDoNotIntersect)
{
    // SFML 3's findIntersection returns nullopt when the overlap has zero area, so
    // rects that share a single point (touching at a corner) are NOT reported as
    // intersecting. Only rects with a non-zero overlap region count.
    const sf::FloatRect a{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const sf::FloatRect b{{10.0f, 10.0f}, {10.0f, 10.0f}};
    CHECK(!Collision::intersects(a, b));

    // For a true intersection, the overlap must have non-zero area.
    const sf::FloatRect c{{9.0f, 9.0f}, {10.0f, 10.0f}};
    CHECK(Collision::intersects(a, c));
}

TEST_CASE(Collision_OverlappingRectsIntersect)
{
    const sf::FloatRect a{{0.0f, 0.0f}, {20.0f, 20.0f}};
    const sf::FloatRect b{{10.0f, 10.0f}, {20.0f, 20.0f}};
    CHECK(Collision::intersects(a, b));
}

TEST_CASE(Collision_ContainsPoint)
{
    const sf::FloatRect r{{0.0f, 0.0f}, {10.0f, 10.0f}};
    CHECK(Collision::contains(r, {5.0f, 5.0f}));
    CHECK(!Collision::contains(r, {15.0f, 5.0f}));
    // SFML's contains uses strict less-than on the max corner, so the top-right
    // corner (10, 10) is NOT contained.
    CHECK(!Collision::contains(r, {10.0f, 10.0f}));
    CHECK(Collision::contains(r, {9.999f, 9.999f}));
}

TEST_CASE(Collision_CircleFarFromRect_NoCollision)
{
    const CircleCollider circle{{100.0f, 100.0f}, 5.0f};
    const sf::FloatRect rect{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const CollisionResult result = Collision::resolveCircleRect(circle, rect);
    CHECK(!result.collided);
}

TEST_CASE(Collision_CircleAboveRect_CollidesAndNormalPointsUp)
{
    // Circle center y=-3, radius 5. Rect top y=0. Distance from center to closest
    // point on rect (5, 0) is 3, depth = radius - distance = 2. The circle overlaps
    // only the top edge, so the normal must point straight up.
    const CircleCollider circle{{5.0f, -3.0f}, 5.0f};
    const sf::FloatRect rect{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const CollisionResult result = Collision::resolveCircleRect(circle, rect);
    REQUIRE(result.collided);
    CHECK(approxEqual(result.normal.x, 0.0f));
    CHECK(result.normal.y < 0.0f); // pushed upward (out the top)
    CHECK(approxEqual(result.depth, 2.0f));
}

TEST_CASE(Collision_CircleLeftOfRect_CollidesAndNormalPointsLeft)
{
    const CircleCollider circle{{-3.0f, 5.0f}, 5.0f};
    const sf::FloatRect rect{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const CollisionResult result = Collision::resolveCircleRect(circle, rect);
    REQUIRE(result.collided);
    CHECK(result.normal.x < 0.0f);
    CHECK(approxEqual(result.depth, 2.0f));
}

TEST_CASE(Collision_CircleCenterInsideRect_StillReportsCollision)
{
    // When the circle's center is inside the rect, the resolver should still return
    // a collision (with normal pointing toward the closest edge) so the gameplay
    // code can push the player out. This is the "depth = radius" degenerate branch.
    const CircleCollider circle{{5.0f, 5.0f}, 5.0f};
    const sf::FloatRect rect{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const CollisionResult result = Collision::resolveCircleRect(circle, rect);
    REQUIRE(result.collided);
    // Normal is one of the four cardinal unit vectors.
    const sf::Vector2f n = result.normal;
    const bool isCardinal =
        (approxEqual(std::fabs(n.x), 1.0f) && approxEqual(n.y, 0.0f)) ||
        (approxEqual(std::fabs(n.y), 1.0f) && approxEqual(n.x, 0.0f));
    CHECK(isCardinal);
}

TEST_CASE(CollisionSystem_PassesThroughToCollision)
{
    // CollisionSystem is a thin grouped wrapper; verify a basic query works through it.
    const CollisionSystem system;
    const sf::FloatRect a{{0.0f, 0.0f}, {10.0f, 10.0f}};
    const sf::FloatRect b{{5.0f, 5.0f}, {10.0f, 10.0f}};
    const CircleCollider circle{{7.0f, 7.0f}, 2.0f};

    CHECK(system.overlapsAny(circle, {a, b}));

    const CollisionResult first = system.firstCircleRectCollision(circle, {a, b});
    CHECK(first.collided);
}

TEST_CASE(CollisionSystem_NoOverlapsReturnsDefaults)
{
    const CollisionSystem system;
    const CircleCollider circle{{100.0f, 100.0f}, 1.0f};
    const std::vector<sf::FloatRect> rects{{{0.0f, 0.0f}, {10.0f, 10.0f}}};

    CHECK(!system.overlapsAny(circle, rects));
    const CollisionResult first = system.firstCircleRectCollision(circle, rects);
    CHECK(!first.collided);
}
