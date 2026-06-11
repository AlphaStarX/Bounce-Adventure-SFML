#include "BounceAdventure/Core/AudioManager.hpp"

#include <SFML/Config.hpp>

#include <algorithm>
#include <stdexcept>

namespace BounceAdventure
{
void AudioManager::loadSound(const std::string& id, const std::filesystem::path& path)
{
    if (m_sounds.find(id) != m_sounds.end())
    {
        return;
    }

    auto slot = std::make_unique<SoundSlot>();
    slot->buffer = std::make_unique<sf::SoundBuffer>();
    if (!slot->buffer->loadFromFile(path.string()))
    {
        throw std::runtime_error("Failed to load sound: " + path.string());
    }

    slot->sound = std::make_unique<sf::Sound>(*slot->buffer);
    slot->sound->setVolume(m_soundVolume);

    m_sounds.emplace(id, std::move(*slot));
}

void AudioManager::playSound(const std::string& id)
{
    const auto it = m_sounds.find(id);
    if (it == m_sounds.end())
    {
        return; // sound not loaded — silently ignore (avoid crash on missing asset)
    }

    it->second.sound->play();
}

void AudioManager::playMusic(const std::filesystem::path& path, bool loop)
{
    m_music = std::make_unique<sf::Music>();
    if (!m_music->openFromFile(path.string()))
    {
        m_music.reset();
        throw std::runtime_error("Failed to load music: " + path.string());
    }

#if SFML_VERSION_MAJOR >= 3
    m_music->setLooping(loop);
#else
    m_music->setLoop(loop);
#endif
    m_music->setVolume(m_musicVolume);
    m_music->play();
}

void AudioManager::stopMusic()
{
    if (m_music)
    {
        m_music->stop();
    }
}

void AudioManager::setSoundVolume(float volume)
{
    m_soundVolume = std::clamp(volume, 0.0f, 100.0f);
    for (auto& [id, slot] : m_sounds)
    {
        slot.sound->setVolume(m_soundVolume);
    }
}

void AudioManager::setMusicVolume(float volume)
{
    m_musicVolume = std::clamp(volume, 0.0f, 100.0f);
    if (m_music)
    {
        m_music->setVolume(m_musicVolume);
    }
}
}
