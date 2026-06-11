#include "BounceAdventure/Core/InputManager.hpp"

#include "BounceAdventure/Core/SfmlCompat.hpp"

namespace BounceAdventure
{
InputManager::InputManager()
{
    beginFrame();
}

void InputManager::handleEvent(const sf::Event& event)
{
    sf::Keyboard::Key key = SfmlCompat::keyUnknown();
    const bool pressed = SfmlCompat::isKeyPressed(event, key);
    const bool released = SfmlCompat::isKeyReleased(event, key);

    if (!pressed && !released)
    {
        return;
    }

    for (std::size_t i = 0; i < ActionCount; ++i)
    {
        const auto action = static_cast<InputAction>(i);
        if (key != keyFor(action))
        {
            continue;
        }

        if (pressed)
        {
            if (!m_held[i])
            {
                m_pressed[i] = true;
            }
            m_held[i] = true;
        }
        else
        {
            m_held[i] = false;
        }
    }
}

void InputManager::beginFrame()
{
    m_pressed.fill(false);
}

bool InputManager::isHeld(InputAction action) const
{
    return m_held[indexOf(action)];
}

bool InputManager::wasPressed(InputAction action) const
{
    return m_pressed[indexOf(action)];
}

std::size_t InputManager::indexOf(InputAction action)
{
    return static_cast<std::size_t>(action);
}

sf::Keyboard::Key InputManager::keyFor(InputAction action)
{
    switch (action)
    {
        case InputAction::MoveLeft:
            return SfmlCompat::keyA();
        case InputAction::MoveRight:
            return SfmlCompat::keyD();
        case InputAction::Jump:
            return SfmlCompat::keySpace();
        case InputAction::Pause:
            return SfmlCompat::keyEscape();
        case InputAction::Confirm:
            return SfmlCompat::keyEnter();
        case InputAction::Back:
            return SfmlCompat::keyBackspace();
        case InputAction::Count:
            break;
    }

    return SfmlCompat::keyUnknown();
}
}
