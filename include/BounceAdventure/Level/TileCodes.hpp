#pragma once

namespace BounceAdventure
{
struct TileCodes
{
    static constexpr char Empty = '.';
    static constexpr char PlayerSpawn = 'P';
    static constexpr char Platform = '#';
    static constexpr char Hazard = '^';
    static constexpr char Collectible = 'C';
    static constexpr char Checkpoint = 'K';
    static constexpr char Goal = 'G';
    static constexpr char MovingPlatformHorizontal = 'H';
    static constexpr char MovingPlatformVertical = 'V';
};
}
