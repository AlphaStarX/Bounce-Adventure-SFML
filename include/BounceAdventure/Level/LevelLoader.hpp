#pragma once

#include "BounceAdventure/Level/LevelData.hpp"

#include <filesystem>

namespace BounceAdventure
{
class LevelLoader
{
public:
    explicit LevelLoader(float tileSize);

    LevelData loadFromFile(const std::filesystem::path& path, int levelNumber, const std::string& levelName) const;

private:
    void parseTile(LevelData& data, char tile, int column, int row) const;

    float m_tileSize;
};
}
