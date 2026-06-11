#pragma once

#include "BounceAdventure/Core/AssetManager.hpp"
#include "BounceAdventure/Core/InputManager.hpp"
#include "BounceAdventure/Core/Scene.hpp"
#include "BounceAdventure/Gameplay/HealthSystem.hpp"
#include "BounceAdventure/Gameplay/Player.hpp"
#include "BounceAdventure/Level/Level.hpp"
#include "BounceAdventure/UI/HUD.hpp"

#include <SFML/Graphics/View.hpp>

#include <filesystem>
namespace BounceAdventure
{
class SceneManager;

class GameScene final : public Scene
{
public:
    explicit GameScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, sf::RenderWindow& window, int startLevel = 1, int coins = 0);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    static Level loadLevel(const std::filesystem::path& path, int number, const std::string& name);

    void beginLevel(int levelNumber);
    void respawnPlayer();
    void checkHazardCollisions();
    void checkCollectibleCollisions();
    void checkCheckpointCollisions();
    bool playerReachedGoal() const;

    void updateCamera(float deltaTime);

    SceneManager& m_sceneManager;
    InputManager& m_input;
    AssetManager& m_assets;
    sf::RenderWindow& m_window;
    HUD m_hud;
    HealthSystem m_health;

    Level m_level;
    Player m_player;
    sf::View m_camera;

    sf::Vector2f m_checkpointPosition{};
    int m_coinsCollected = 0;

    bool m_levelComplete = false;
    float m_levelCompleteTimer = 0.0f;
    int m_currentLevelNumber = 0;
    bool m_gameComplete = false;
    bool m_gameOver = false;
};
}
