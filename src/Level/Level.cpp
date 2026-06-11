#include "BounceAdventure/Level/Level.hpp"

namespace BounceAdventure
{
Level::Level(const LevelData& data)
    : m_goal(data.goal.position, data.goal.size)
    , m_playerSpawn(data.playerSpawn)
    , m_levelNumber(data.levelNumber)
    , m_name(data.name)
{
    m_platforms.reserve(data.platforms.size());
    for (const auto& p : data.platforms)
    {
        m_platforms.emplace_back(p.position, p.size);
    }

    m_hazards.reserve(data.hazards.size());
    for (const auto& h : data.hazards)
    {
        m_hazards.emplace_back(h.position, h.size);
    }

    m_collectibles.reserve(data.collectibles.size());
    for (const auto& c : data.collectibles)
    {
        m_collectibles.emplace_back(c.position, 12.0f);
    }

    m_checkpoints.reserve(data.checkpoints.size());
    for (const auto& k : data.checkpoints)
    {
        m_checkpoints.emplace_back(k.position, sf::Vector2f{48.0f, 48.0f});
    }

    m_movingPlatforms.reserve(data.movingPlatforms.size());
    for (const auto& mp : data.movingPlatforms)
    {
        m_movingPlatforms.emplace_back(mp.position, mp.size, mp.axis == MovingPlatformAxis::Vertical, mp.travelDistance, mp.speed);
    }
}

const std::string& Level::name() const
{
    return m_name;
}

int Level::number() const
{
    return m_levelNumber;
}

const std::vector<Platform>& Level::platforms() const
{
    return m_platforms;
}

const std::vector<Hazard>& Level::hazards() const
{
    return m_hazards;
}

const std::vector<Collectible>& Level::collectibles() const
{
    return m_collectibles;
}

const std::vector<Checkpoint>& Level::checkpoints() const
{
    return m_checkpoints;
}

const std::vector<MovingPlatform>& Level::movingPlatforms() const
{
    return m_movingPlatforms;
}

const Goal& Level::goal() const
{
    return m_goal;
}

std::vector<Collectible>& Level::collectibles()
{
    return m_collectibles;
}

std::vector<Checkpoint>& Level::checkpoints()
{
    return m_checkpoints;
}

sf::Vector2f Level::playerSpawn() const
{
    return m_playerSpawn;
}

std::vector<sf::FloatRect> Level::platformBounds() const
{
    std::vector<sf::FloatRect> bounds;
    bounds.reserve(m_platforms.size() + m_movingPlatforms.size());
    for (const auto& p : m_platforms)
    {
        bounds.push_back(p.bounds());
    }
    for (const auto& mp : m_movingPlatforms)
    {
        bounds.push_back(mp.bounds());
    }
    return bounds;
}

void Level::update(float deltaTime)
{
    for (auto& mp : m_movingPlatforms)
    {
        mp.update(deltaTime);
    }
}

void Level::draw(sf::RenderWindow& window) const
{
    for (const auto& p : m_platforms)
    {
        p.draw(window);
    }
    for (const auto& mp : m_movingPlatforms)
    {
        mp.draw(window);
    }
    for (const auto& h : m_hazards)
    {
        h.draw(window);
    }
    for (const auto& k : m_checkpoints)
    {
        k.draw(window);
    }
    for (const auto& c : m_collectibles)
    {
        c.draw(window);
    }
    m_goal.draw(window);
}
}
