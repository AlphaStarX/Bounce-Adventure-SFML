#pragma once

#include <string>

namespace BounceAdventure
{
struct GameConfig
{
    static constexpr unsigned int WindowWidth = 1280;
    static constexpr unsigned int WindowHeight = 720;
    static constexpr unsigned int FrameRateLimit = 120;
    static constexpr float FixedTimeStep = 1.0f / 120.0f;

    inline static const std::string WindowTitle = "Bounce Adventure";
};
}
