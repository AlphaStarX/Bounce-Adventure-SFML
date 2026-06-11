#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <array>
#include <cstddef>

namespace BounceAdventure
{
enum class InputAction
{
    MoveLeft,
    MoveRight,
    Jump,
    Pause,
    Confirm,
    Back,
    Count
};

class InputManager
{
public:
    InputManager();

    void handleEvent(const sf::Event& event);
    void beginFrame();

    bool isHeld(InputAction action) const;
    bool wasPressed(InputAction action) const;

private:
    static constexpr std::size_t ActionCount = static_cast<std::size_t>(InputAction::Count);

    static std::size_t indexOf(InputAction action);
    static sf::Keyboard::Key keyFor(InputAction action);

    std::array<bool, ActionCount> m_held{};
    std::array<bool, ActionCount> m_pressed{};
};
}
