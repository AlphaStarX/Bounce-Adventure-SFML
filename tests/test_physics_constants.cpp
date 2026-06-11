#include "BounceAdventure/Physics/PhysicsConstants.hpp"

#include "test_harness.hpp"

using namespace BounceAdventure;

TEST_CASE(Physics_GravityIsDownwardAndPositive)
{
    // In screen coordinates positive Y is downward, so gravity is a positive scalar.
    CHECK(PhysicsConstants::Gravity > 0.0f);
}

TEST_CASE(Physics_JumpVelocityIsUpward)
{
    // A jump imparts upward (negative-Y) velocity.
    CHECK(PhysicsConstants::JumpVelocity < 0.0f);
}

TEST_CASE(Physics_TerminalVelocityCapsFallingSpeed)
{
    // Terminal velocity is downward (positive Y) and not absurdly large.
    CHECK(PhysicsConstants::TerminalVelocity > 0.0f);
    CHECK(PhysicsConstants::TerminalVelocity < 10000.0f);
}

TEST_CASE(Physics_FrictionIsStrongerOnGroundThanInAir)
{
    CHECK(PhysicsConstants::GroundFriction > PhysicsConstants::AirFriction);
}

TEST_CASE(Physics_JumpCutClampsBetweenZeroAndOne)
{
    // JumpCutMultiplier should be a (0, 1] value so the cut is meaningful.
    CHECK(PhysicsConstants::JumpCutMultiplier > 0.0f);
    CHECK(PhysicsConstants::JumpCutMultiplier <= 1.0f);

    // The clamped target velocity is therefore between zero and the full jump velocity.
    const float target = PhysicsConstants::JumpVelocity * PhysicsConstants::JumpCutMultiplier;
    CHECK(target < 0.0f);
    CHECK(target > PhysicsConstants::JumpVelocity);
}

TEST_CASE(Physics_CoyoteAndBufferWindowsAreSmallButPositive)
{
    CHECK(PhysicsConstants::CoyoteTime > 0.0f);
    CHECK(PhysicsConstants::CoyoteTime < 0.5f);
    CHECK(PhysicsConstants::JumpBufferTime > 0.0f);
    CHECK(PhysicsConstants::JumpBufferTime < 0.5f);
}

TEST_CASE(Physics_MovementTunablesAreInternallyConsistent)
{
    // The max horizontal speed is achievable from a standstill: a single frame's
    // acceleration should not jump straight to max on the first tick, but rather
    // approach it. A loose sanity: MaxMoveSpeed < (MoveAcceleration * 1 second),
    // otherwise the cap is pointless at 60+ fps.
    CHECK(PhysicsConstants::MaxMoveSpeed < PhysicsConstants::MoveAcceleration);
    CHECK(PhysicsConstants::MaxMoveSpeed > 0.0f);
}
