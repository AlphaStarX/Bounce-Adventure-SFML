#include "BounceAdventure/Scenes/GameScene.hpp"

#include "BounceAdventure/Core/GameConfig.hpp"
#include "BounceAdventure/Core/SfmlCompat.hpp"
#include "BounceAdventure/Level/LevelLoader.hpp"
#include "BounceAdventure/Physics/Collision.hpp"

#include "BounceAdventure/Scenes/PauseScene.hpp"
#include "BounceAdventure/Scenes/LevelCompleteScene.hpp"
#include "BounceAdventure/Scenes/GameCompleteScene.hpp"

#include <SFML/Config.hpp>
#include <algorithm>
#include <filesystem>

namespace BounceAdventure
{
static constexpr float RespawnFallY = 1500.0f;
static constexpr float InvulnerabilityDuration = 1.5f;

static const std::vector<std::pair<std::string, std::string>> levelDefs = {
    {"level_01.txt", "Learning Basics"},
    {"level_02.txt", "Collectibles"},
    {"level_03.txt", "Hazards"},
    {"level_04.txt", "Moving Platforms"},
    {"level_05.txt", "Advanced Platforming"},
    {"level_06.txt", "Final Challenge"},
};

GameScene::GameScene(SceneManager& sceneManager, InputManager& input, AssetManager& assets, AudioManager& audio, sf::RenderWindow& window, int startLevel, int coins)
    : m_sceneManager(sceneManager)
    , m_input(input)
    , m_assets(assets)
    , m_audio(audio)
    , m_window(window)
    , m_hud(assets)
    , m_level(loadLevel(std::filesystem::path("assets") / "levels" / "level_01.txt", 1, "Learning Basics"))
    , m_player(m_level.playerSpawn())
    , m_camera(SfmlCompat::makeRect(
          {0.0f, 0.0f},
          {static_cast<float>(GameConfig::WindowWidth), static_cast<float>(GameConfig::WindowHeight)}))
{
    // Load sound effects (idempotent — AudioManager silently ignores duplicates)
    m_audio.loadSound("jump", "assets/sounds/jump.wav");
    m_audio.loadSound("coin", "assets/sounds/coin.wav");
    m_audio.loadSound("hazard", "assets/sounds/hazard.wav");
    m_audio.loadSound("checkpoint", "assets/sounds/checkpoint.wav");
    m_audio.loadSound("goal", "assets/sounds/goal.wav");

    m_coinsCollected = coins;
    beginLevel(startLevel);
}

void GameScene::handleEvent(const sf::Event& event)
{
    static_cast<void>(event);
}
void GameScene::update(float deltaTime)
{
    if (m_gameOver)
    {
        if (m_input.wasPressed(InputAction::Confirm))
        {
            m_health.reset();
            m_coinsCollected = 0;
            m_gameOver = false;
            beginLevel(m_currentLevelNumber);
        }
        return;
    }

    if (m_gameComplete)
    {
        if (m_input.wasPressed(InputAction::Confirm))
        {
            m_health.reset();
            m_coinsCollected = 0;
            m_gameComplete = false;
            beginLevel(1);
        }
        return;
    }

    // Tick invulnerability timer
    if (m_invulnerabilityTimer > 0.0f)
    {
        m_invulnerabilityTimer = std::max(0.0f, m_invulnerabilityTimer - deltaTime);
    }

    if (m_input.wasPressed(InputAction::Pause))
    {
        m_sceneManager.push(std::make_unique<PauseScene>(m_sceneManager, m_input, m_assets, m_audio, m_window));
        return;
    }

    if (m_input.wasPressed(InputAction::Back))
    {
        respawnPlayer();
        m_levelComplete = false;
        m_levelCompleteTimer = 0.0f;
    }

    m_level.update(deltaTime);

    std::vector<sf::FloatRect> platforms = m_level.platformBounds();
    const bool wasGrounded = m_player.isGrounded();
    const bool jumpPressed = m_input.wasPressed(InputAction::Jump);
    m_player.update(deltaTime, m_input, platforms);

    // Jump sound: only on an actual jump keypress, not walking off a ledge.
    if (jumpPressed && wasGrounded && !m_player.isGrounded())
    {
        m_audio.playSound("jump");
    }

    auto getMovingPlatformImpulse = [&]() -> sf::Vector2f {
        const CircleCollider playerCircle{m_player.position(), m_player.radius()};
        for (const auto& mp : m_level.movingPlatforms())
        {
            if (Collision::intersects(playerCircle, mp.bounds()) && m_player.isGrounded())
            {
                return mp.velocity();
            }
        }
        return {};
    };

    const sf::Vector2f platformImpulse = getMovingPlatformImpulse();
    if (platformImpulse.x != 0.0f || platformImpulse.y != 0.0f)
    {
        m_player.applyImpulse(platformImpulse);
    }

    if (m_player.position().y > RespawnFallY)
    {
        m_health.takeDamage(1);
        m_audio.playSound("hazard");
        if (m_health.isAlive())
        {
            m_invulnerabilityTimer = InvulnerabilityDuration;
            respawnPlayer();
        }
        else
        {
            m_gameOver = true;
        }
    }

    checkHazardCollisions();
    checkCollectibleCollisions();
    checkCheckpointCollisions();

    if (playerReachedGoal())
    {
        m_audio.playSound("goal");
        if (m_currentLevelNumber < 6)
        {
            m_sceneManager.push(std::make_unique<LevelCompleteScene>(
                m_sceneManager, m_input, m_assets, m_audio, m_window, m_currentLevelNumber, m_coinsCollected));
        }
        else
        {
            m_sceneManager.push(std::make_unique<GameCompleteScene>(
                m_sceneManager, m_input, m_assets, m_audio, m_window, m_coinsCollected));
        }
        return;
    }

    if (m_gameOver)
    {
        m_hud.setMessage("Game Over! Press Enter");
    }
    else
    {
        m_hud.clearMessage();
    }

    updateCamera(deltaTime);
    m_hud.update(m_health.health(), HealthSystem::MaxHealth, m_coinsCollected,
                 static_cast<int>(m_level.collectibles().size()), m_level.number(), m_level.name());
}
void GameScene::render(sf::RenderWindow& window)
{
    const sf::View previousView = window.getView();
    window.setView(m_camera);
    m_level.draw(window);

    // Flash the player during invulnerability (toggle visibility on a fast cycle)
    const bool flashOn = m_invulnerabilityTimer <= 0.0f
        || static_cast<int>(m_invulnerabilityTimer * 10.0f) % 2 == 0;
    if (flashOn)
    {
        m_player.draw(window);
    }

    window.setView(previousView);

    m_hud.draw(window);
}

Level GameScene::loadLevel(const std::filesystem::path& path, int number, const std::string& name)
{
    LevelLoader loader(48.0f);
    return Level(loader.loadFromFile(path, number, name));
}

void GameScene::beginLevel(int levelNumber)
{
    m_health.reset();
    m_invulnerabilityTimer = 0.0f;
    m_currentLevelNumber = levelNumber;

    const auto& def = levelDefs[static_cast<std::size_t>(levelNumber) - 1];
    const std::filesystem::path path = std::filesystem::path("assets") / "levels" / def.first;
    m_level = loadLevel(path, levelNumber, def.second);

    m_checkpointPosition = m_level.playerSpawn();
    m_player.respawn(m_checkpointPosition);
    m_camera.setCenter(m_player.position());
    m_levelComplete = false;
    m_levelCompleteTimer = 0.0f;
}

void GameScene::respawnPlayer()
{
    m_player.respawn(m_checkpointPosition);
    m_invulnerabilityTimer = InvulnerabilityDuration;
    m_camera.setCenter(m_player.position());
}

void GameScene::checkHazardCollisions()
{
    if (!m_health.isAlive())
    {
        return;
    }

    // Invulnerability frames: don't take damage while the timer is active
    if (m_invulnerabilityTimer > 0.0f)
    {
        return;
    }

    const CircleCollider playerCircle{m_player.position(), m_player.radius()};
    for (const auto& hazard : m_level.hazards())
    {
        if (Collision::intersects(playerCircle, hazard.bounds()))
        {
            m_health.takeDamage(1);
            m_audio.playSound("hazard");
            if (m_health.isAlive())
            {
                m_invulnerabilityTimer = InvulnerabilityDuration;
                respawnPlayer();
            }
            else
            {
                m_gameOver = true;
            }
            break;
        }
    }
}

void GameScene::checkCollectibleCollisions()
{
    const CircleCollider playerCircle{m_player.position(), m_player.radius()};
    for (auto& collectible : m_level.collectibles())
    {
        if (!collectible.isCollected() && Collision::intersects(playerCircle, collectible.bounds()))
        {
            collectible.collect();
            ++m_coinsCollected;
            m_audio.playSound("coin");
        }
    }
}

void GameScene::checkCheckpointCollisions()
{
    const CircleCollider playerCircle{m_player.position(), m_player.radius()};
    for (auto& checkpoint : m_level.checkpoints())
    {
        if (!checkpoint.isActivated() && Collision::intersects(playerCircle, checkpoint.bounds()))
        {
            checkpoint.activate();
            m_checkpointPosition = checkpoint.respawnPosition();
            m_audio.playSound("checkpoint");
        }
    }
}

bool GameScene::playerReachedGoal() const
{
    const CircleCollider playerCircle{m_player.position(), m_player.radius()};
    return Collision::intersects(playerCircle, m_level.goal().bounds());
}

void GameScene::updateCamera(float deltaTime)
{
    const sf::Vector2f target = m_player.position();
    const sf::Vector2f current = m_camera.getCenter();
    const float smoothing = std::min(deltaTime * 6.0f, 1.0f);
    m_camera.setCenter(current + (target - current) * smoothing);
}
}
