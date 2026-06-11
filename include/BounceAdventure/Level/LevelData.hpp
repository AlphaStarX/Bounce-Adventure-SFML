#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>
#include <vector>

namespace BounceAdventure
{
enum class MovingPlatformAxis
{
    Horizontal,
    Vertical
};

struct RectObjectData
{
    sf::Vector2f position{};
    sf::Vector2f size{};
};

struct PointObjectData
{
    sf::Vector2f position{};
};

struct MovingPlatformData
{
    sf::Vector2f position{};
    sf::Vector2f size{};
    MovingPlatformAxis axis = MovingPlatformAxis::Horizontal;
    float travelDistance = 160.0f;
    float speed = 80.0f;
};

struct LevelData
{
    int levelNumber = 1;
    std::string name;
    sf::Vector2f playerSpawn{};
    std::vector<RectObjectData> platforms;
    std::vector<RectObjectData> hazards;
    std::vector<PointObjectData> collectibles;
    std::vector<PointObjectData> checkpoints;
    std::vector<MovingPlatformData> movingPlatforms;
    RectObjectData goal;
    bool hasGoal = false;
};
}
