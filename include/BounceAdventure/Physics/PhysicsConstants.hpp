#pragma once

namespace BounceAdventure
{
struct PhysicsConstants
{
    static constexpr float Gravity = 1800.0f;
    static constexpr float MoveAcceleration = 2600.0f;
    static constexpr float MaxMoveSpeed = 420.0f;
    static constexpr float GroundFriction = 2200.0f;
    static constexpr float AirFriction = 450.0f;
    static constexpr float JumpVelocity = -720.0f;
    static constexpr float TerminalVelocity = 1300.0f;
    static constexpr float LandingBounceVelocity = -170.0f;
    static constexpr float MinimumBounceImpact = 520.0f;

    // Jump-feel tunables (see Player.cpp for usage).
    // CoyoteTime:   window after walking off a ledge in which Jump still works.
    // JumpBufferTime: window before landing in which a Jump press is remembered.
    // JumpCutMultiplier: fraction of upward velocity retained when Jump is released mid-air.
    static constexpr float CoyoteTime = 0.10f;
    static constexpr float JumpBufferTime = 0.10f;
    static constexpr float JumpCutMultiplier = 0.4f;
};
}
