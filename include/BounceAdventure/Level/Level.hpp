#pragma once

#include "BounceAdventure/Gameplay/Checkpoint.hpp"
#include "BounceAdventure/Gameplay/Collectible.hpp"
#include "BounceAdventure/Gameplay/Goal.hpp"
#include "BounceAdventure/Gameplay/Hazard.hpp"
#include "BounceAdventure/Gameplay/MovingPlatform.hpp"
#include "BounceAdventure/Gameplay/Platform.hpp"
#include "BounceAdventure/Level/LevelData.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace BounceAdventure
{
class Level
{
public:
    explicit Level(const LevelData& data);

    const std::string& name() const;
    int number() const;

    const std::vector<Platform>& platforms() const;
    const std::vector<Hazard>& hazards() const;
    const std::vector<Collectible>& collectibles() const;
    const std::vector<Checkpoint>& checkpoints() const;
    const std::vector<MovingPlatform>& movingPlatforms() const;
    const Goal& goal() const;

    std::vector<Collectible>& collectibles();
    std::vector<Checkpoint>& checkpoints();

    sf::Vector2f playerSpawn() const;

    std::vector<sf::FloatRect> platformBounds() const;

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

private:
    std::vector<Platform> m_platforms;
    std::vector<Hazard> m_hazards;
    std::vector<Collectible> m_collectibles;
    std::vector<Checkpoint> m_checkpoints;
    std::vector<MovingPlatform> m_movingPlatforms;
    Goal m_goal;
    sf::Vector2f m_playerSpawn{};
    int m_levelNumber = 1;
    std::string m_name;
};
}
