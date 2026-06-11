#pragma once

#include "BounceAdventure/Core/Scene.hpp"
#include "BounceAdventure/Core/SceneManager.hpp"
#include "BounceAdventure/Core/InputManager.hpp"
#include "BounceAdventure/Core/AssetManager.hpp"
#include "BounceAdventure/Core/AudioManager.hpp"
#include "BounceAdventure/UI/TextLabel.hpp"
#include "BounceAdventure/UI/Button.hpp"

#include <vector>

namespace BounceAdventure
{
class LevelCompleteScene : public Scene
{
public:
    LevelCompleteScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, AudioManager& audio, sf::RenderWindow& window, int completedLevel, int coins);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    SceneManager& m_sceneManager;
    InputManager& m_input;
    AssetManager& m_assets;
    AudioManager& m_audio;
    sf::RenderWindow& m_window;

    TextLabel m_title;
    TextLabel m_statsLabel;
    std::vector<Button> m_buttons;
};
}
