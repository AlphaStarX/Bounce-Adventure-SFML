#pragma once

namespace BounceAdventure
{
class HealthSystem
{
public:
    static constexpr int MaxHealth = 3;

    HealthSystem() = default;

    bool isAlive() const;
    int health() const;
    void takeDamage(int amount = 1);
    void reset();

private:
    int m_health = MaxHealth;
};
}
