#include "BounceAdventure/Level/LevelLoader.hpp"

#include "BounceAdventure/Level/TileCodes.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

namespace BounceAdventure
{
LevelLoader::LevelLoader(float tileSize)
    : m_tileSize(tileSize)
{
    if (m_tileSize <= 0.0f)
    {
        throw std::invalid_argument("LevelLoader tile size must be positive.");
    }
}

LevelData LevelLoader::loadFromFile(
    const std::filesystem::path& path,
    int levelNumber,
    const std::string& levelName) const
{
    std::ifstream file(path);
    if (!file)
    {
        throw std::runtime_error("Failed to open level file: " + path.string());
    }

    LevelData data;
    data.levelNumber = levelNumber;
    data.name = levelName;

    std::string line;
    int row = 0;
    while (std::getline(file, line))
    {
        for (int column = 0; column < static_cast<int>(line.size()); ++column)
        {
            parseTile(data, line[static_cast<std::size_t>(column)], column, row);
        }
        ++row;
    }

    if (!data.hasGoal)
    {
        throw std::runtime_error("Level is missing a goal: " + path.string());
    }

    return data;
}

void LevelLoader::parseTile(LevelData& data, char tile, int column, int row) const
{
    const sf::Vector2f position{
        static_cast<float>(column) * m_tileSize,
        static_cast<float>(row) * m_tileSize};

    switch (tile)
    {
        case TileCodes::Empty:
            break;
        case TileCodes::PlayerSpawn:
            data.playerSpawn = position;
            break;
        case TileCodes::Platform:
            data.platforms.push_back({position, {m_tileSize, m_tileSize}});
            break;
        case TileCodes::Hazard:
            data.hazards.push_back({position, {m_tileSize, m_tileSize}});
            break;
        case TileCodes::Collectible:
            data.collectibles.push_back({position + sf::Vector2f{m_tileSize * 0.5f, m_tileSize * 0.5f}});
            break;
        case TileCodes::Checkpoint:
            data.checkpoints.push_back({position});
            break;
        case TileCodes::Goal:
            data.goal = {position, {m_tileSize, m_tileSize * 2.0f}};
            data.hasGoal = true;
            break;
        case TileCodes::MovingPlatformHorizontal:
            data.movingPlatforms.push_back({position, {m_tileSize, m_tileSize}, MovingPlatformAxis::Horizontal});
            break;
        case TileCodes::MovingPlatformVertical:
            data.movingPlatforms.push_back({position, {m_tileSize, m_tileSize}, MovingPlatformAxis::Vertical});
            break;
        default:
            throw std::runtime_error(std::string("Unknown level tile code: ") + tile);
    }
}
}
