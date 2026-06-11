#include "BounceAdventure/Gameplay/Player.hpp"

#include "BounceAdventure/Physics/Collision.hpp"
#include "BounceAdventure/Physics/PhysicsConstants.hpp"

#include <SFML/Config.hpp>

#include <algorithm>
#include <cmath>

namespace BounceAdventure
{
Player::Player(sf::Vector2f spawnPosition)
    : m_spawnPosition(spawnPosition)
{
    m_body.position = spawnPosition;
    m_body.radius = 22.0f;

    m_shape.setRadius(m_body.radius);
#if SFML_VERSION_MAJOR >= 3
    m_shape.setOrigin({m_body.radius, m_body.radius});
#else
    m_shape.setOrigin(m_body.radius, m_body.radius);
#endif
    m_shape.setFillColor(sf::Color(230, 80, 68));
    m_shape.setOutlineColor(sf::Color(255, 225, 210));
    m_shape.setOutlineThickness(3.0f);
    syncShape();
}

void Player::update(float deltaTime, const InputManager& input, const std::vector<sf::FloatRect>& platformBounds)
{
    // Tick the jump-buffer timer down. A fresh jump press resets it in applyInput().
    if (m_jumpBufferTimer > 0.0f)
    {
        m_jumpBufferTimer = std::max(0.0f, m_jumpBufferTimer - deltaTime);
    }

    m_body.acceleration = {0.0f, PhysicsConstants::Gravity};
    applyInput(deltaTime, input);
    integrate(deltaTime);
    resolvePlatformCollisions(platformBounds);

    // Coyote-time bookkeeping: reset when grounded, otherwise accumulate airborne time.
    if (m_body.grounded)
    {
        m_timeSinceLeftGround = 0.0f;
    }
    else
    {
        m_timeSinceLeftGround += deltaTime;
    }

    syncShape();
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

void Player::respawn(sf::Vector2f position)
{
    m_body.position = position;
    m_body.velocity = {};
    m_body.acceleration = {};
    m_body.grounded = false;
    syncShape();
}

void Player::applyImpulse(sf::Vector2f impulse)
{
    m_body.velocity += impulse;
}

sf::Vector2f Player::position() const
{
    return m_body.position;
}

sf::FloatRect Player::bounds() const
{
    return m_shape.getGlobalBounds();
}

float Player::radius() const
{
    return m_body.radius;
}

bool Player::isGrounded() const
{
    return m_body.grounded;
}

void Player::setVelocity(sf::Vector2f velocity)
{
    m_body.velocity = velocity;
}

sf::Vector2f Player::velocity() const
{
    return m_body.velocity;
}

void Player::applyInput(float deltaTime, const InputManager& input)
{
    if (input.isHeld(InputAction::MoveLeft))
    {
        m_body.velocity.x -= PhysicsConstants::MoveAcceleration * deltaTime;
    }
    if (input.isHeld(InputAction::MoveRight))
    {
        m_body.velocity.x += PhysicsConstants::MoveAcceleration * deltaTime;
    }

    m_body.velocity.x = std::clamp(
        m_body.velocity.x,
        -PhysicsConstants::MaxMoveSpeed,
        PhysicsConstants::MaxMoveSpeed);

    const float friction = m_body.grounded ? PhysicsConstants::GroundFriction : PhysicsConstants::AirFriction;
    if (!input.isHeld(InputAction::MoveLeft) && !input.isHeld(InputAction::MoveRight))
    {
        const float speedDrop = friction * deltaTime;
        if (std::abs(m_body.velocity.x) <= speedDrop)
        {
            m_body.velocity.x = 0.0f;
        }
        else
        {
            m_body.velocity.x -= std::copysign(speedDrop, m_body.velocity.x);
        }
    }

    // Jump buffering: remember the press for JumpBufferTime seconds. The actual jump
    // will be consumed when the player is grounded (or in coyote time) within that window.
    if (input.wasPressed(InputAction::Jump))
    {
        m_jumpBufferTimer = PhysicsConstants::JumpBufferTime;
    }

    const bool canJump = m_jumpBufferTimer > 0.0f
                      && m_timeSinceLeftGround < PhysicsConstants::CoyoteTime;
    if (canJump)
    {
        m_body.velocity.y = PhysicsConstants::JumpVelocity;
        m_body.grounded = false;
        m_timeSinceLeftGround = PhysicsConstants::CoyoteTime; // block re-fire this airborne stretch
        m_jumpBufferTimer = 0.0f;                              // consume the buffered press
    }

    // Variable jump height: releasing Jump mid-air caps the upward velocity so short
    // taps produce short hops and held presses produce full jumps.
    if (input.wasReleased(InputAction::Jump) && m_body.velocity.y < 0.0f)
    {
        m_body.velocity.y = std::max(
            m_body.velocity.y,
            PhysicsConstants::JumpVelocity * PhysicsConstants::JumpCutMultiplier);
    }
}

void Player::integrate(float deltaTime)
{
    m_body.velocity += m_body.acceleration * deltaTime;
    m_body.velocity.y = std::min(m_body.velocity.y, PhysicsConstants::TerminalVelocity);
    m_body.position += m_body.velocity * deltaTime;
    m_body.grounded = false;
}

void Player::resolvePlatformCollisions(const std::vector<sf::FloatRect>& platformBounds)
{
    CircleCollider collider{m_body.position, m_body.radius};

    for (const auto& bounds : platformBounds)
    {
        const CollisionResult result = Collision::resolveCircleRect(collider, bounds);
        if (!result.collided)
        {
            continue;
        }

        m_body.position += result.normal * result.depth;
        collider.center = m_body.position;

        if (result.normal.y < -0.5f)
        {
            const float impactSpeed = m_body.velocity.y;
            m_body.grounded = true;
            m_body.velocity.y = 0.0f;

            if (impactSpeed > PhysicsConstants::MinimumBounceImpact)
            {
                m_body.velocity.y = PhysicsConstants::LandingBounceVelocity;
                m_body.grounded = false;
            }
        }
        else if (result.normal.y > 0.5f && m_body.velocity.y < 0.0f)
        {
            m_body.velocity.y = 0.0f;
        }
        else if (std::abs(result.normal.x) > 0.5f)
        {
            m_body.velocity.x = 0.0f;
        }
    }
}

void Player::syncShape()
{
    m_shape.setPosition(m_body.position);
}
}
