#include "BounceAdventure/Gameplay/HealthSystem.hpp"

namespace BounceAdventure
{
bool HealthSystem::isAlive() const
{
    return m_health > 0;
}

int HealthSystem::health() const
{
    return m_health;
}

void HealthSystem::takeDamage(int amount)
{
    m_health -= amount;
    if (m_health < 0)
    {
        m_health = 0;
    }
}

void HealthSystem::reset()
{
    m_health = MaxHealth;
}
}
