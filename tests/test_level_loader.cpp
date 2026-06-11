#include "BounceAdventure/Level/LevelData.hpp"
#include "BounceAdventure/Level/LevelLoader.hpp"
#include "BounceAdventure/Level/TileCodes.hpp"

#include "test_harness.hpp"

#include <SFML/System/Vector2.hpp>

#include <exception>
#include <filesystem>
#include <string>

using namespace BounceAdventure;

namespace
{
constexpr float kTileSize = 48.0f;
const std::filesystem::path kFixturesDir = "fixtures";

LevelData loadFixture(const std::string& name, int number, const std::string& label)
{
    const LevelLoader loader(kTileSize);
    return loader.loadFromFile(kFixturesDir / name, number, label);
}

bool tryLoad(const std::filesystem::path& path)
{
    const LevelLoader loader(kTileSize);
    try
    {
        loader.loadFromFile(path, 1, "x");
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}
} // namespace

TEST_CASE(LevelLoader_RejectsNonPositiveTileSize)
{
    bool threw = false;
    try
    {
        LevelLoader loader(0.0f);
    }
    catch (const std::invalid_argument&)
    {
        threw = true;
    }
    CHECK(threw);

    threw = false;
    try
    {
        LevelLoader loader(-1.0f);
    }
    catch (const std::invalid_argument&)
    {
        threw = true;
    }
    CHECK(threw);
}

TEST_CASE(LevelLoader_ThrowsWhenFileMissing)
{
    CHECK(!tryLoad("fixtures/this_file_does_not_exist_xyz.txt"));
}

TEST_CASE(LevelLoader_ThrowsWhenGoalMissing)
{
    CHECK(!tryLoad("fixtures/level_missing_goal.txt"));
}

TEST_CASE(LevelLoader_ThrowsOnUnknownTile)
{
    CHECK(!tryLoad("fixtures/level_unknown_tile.txt"));
}

TEST_CASE(LevelLoader_MinimalLevel_ParsesPlayerAndGoal)
{
    // level_3x3.txt:
    //   PG.
    //   ...
    //   ...
    const LevelData data = loadFixture("level_3x3.txt", 1, "minimal");

    CHECK(data.levelNumber == 1);
    CHECK(data.name == "minimal");
    CHECK(data.hasGoal);
    // Note: paren-init (Vector2f(x, y)) is used instead of brace-init so the comma
    // is not parsed as a macro argument separator by the preprocessor.
    CHECK(data.playerSpawn == sf::Vector2f(0.0f, 0.0f));
    CHECK(data.platforms.empty());
    CHECK(data.hazards.empty());
    CHECK(data.collectibles.empty());
    CHECK(data.checkpoints.empty());
    CHECK(data.movingPlatforms.empty());

    // Goal at column 1, row 0 → position (48, 0) with the documented (1, 2) tile aspect.
    CHECK(data.goal.position == sf::Vector2f(kTileSize, 0.0f));
    CHECK(data.goal.size == sf::Vector2f(kTileSize, kTileSize * 2.0f));
}

TEST_CASE(LevelLoader_FullLevel_CountsEveryEntityKind)
{
    // level_full.txt (tile size 48):
    //   PCK#^      row 0
    //   C..K#^     row 1
    //   .....G     row 2
    //   ....#.     row 3
    //   ....#.     row 4
    //
    // Hand-counted:
    //   1 player spawn
    //   2 collectibles
    //   2 checkpoints
    //   4 platforms
    //   2 hazards
    //   0 moving platforms
    //   1 goal at column 5, row 2 → (240, 96)
    const LevelData data = loadFixture("level_full.txt", 2, "full");

    CHECK(data.hasGoal);
    CHECK(data.playerSpawn == sf::Vector2f(0.0f, 0.0f));
    CHECK(data.collectibles.size() == 2);
    CHECK(data.checkpoints.size() == 2);
    CHECK(data.platforms.size() == 4);
    CHECK(data.hazards.size() == 2);
    CHECK(data.movingPlatforms.empty());
    CHECK(data.goal.position == sf::Vector2f(5.0f * kTileSize, 2.0f * kTileSize));
}

TEST_CASE(LevelLoader_CollectibleIsCenteredInTile)
{
    // The 'C' tile is rendered as a 1x1 sprite centered in the cell.
    // For a tile at (col, row) the stored position is (col*tile + tile/2, row*tile + tile/2).
    const LevelData data = loadFixture("level_full.txt", 1, "full");
    REQUIRE(data.collectibles.size() == 2);
    // First collectible: row 0, col 1 → (1*48 + 24, 0*48 + 24) = (72, 24).
    CHECK(data.collectibles[0].position == sf::Vector2f(kTileSize * 1.5f, kTileSize * 0.5f));
}
