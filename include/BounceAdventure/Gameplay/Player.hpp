#pragma once

#include "BounceAdventure/Core/InputManager.hpp"
#include "BounceAdventure/Physics/PhysicsBody.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace BounceAdventure
{
class Player
{
public:
    explicit Player(sf::Vector2f spawnPosition);

    void update(float deltaTime, const InputManager& input, const std::vector<sf::FloatRect>& platformBounds);
    void draw(sf::RenderWindow& window) const;
    void respawn(sf::Vector2f position);
    void applyImpulse(sf::Vector2f impulse);

    sf::Vector2f position() const;
    sf::FloatRect bounds() const;
    float radius() const;
    bool isGrounded() const;

    void setVelocity(sf::Vector2f velocity);
    sf::Vector2f velocity() const;

private:
    void applyInput(float deltaTime, const InputManager& input);
    void integrate(float deltaTime);
    void resolvePlatformCollisions(const std::vector<sf::FloatRect>& platformBounds);
    void syncShape();

    PhysicsBody m_body;
    sf::CircleShape m_shape;
    sf::Vector2f m_spawnPosition;
};
}
