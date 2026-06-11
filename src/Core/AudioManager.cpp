#include "BounceAdventure/Core/AudioManager.hpp"

#include <SFML/Config.hpp>
#include <SFML/Audio/SoundSource.hpp>

#include <algorithm>
#include <stdexcept>

namespace BounceAdventure
{
void AudioManager::loadSound(const std::string& id, const std::filesystem::path& path)
{
    if (m_soundBuffers.find(id) != m_soundBuffers.end())
    {
        return;
    }

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path.string()))
    {
        throw std::runtime_error("Failed to load sound: " + path.string());
    }

    m_soundBuffers.emplace(id, std::move(buffer));
}

void AudioManager::playSound(const std::string& id)
{
    removeStoppedSounds();

    const auto buffer = m_soundBuffers.find(id);
    if (buffer == m_soundBuffers.end())
    {
        throw std::runtime_error("Sound has not been loaded: " + id);
    }

    sf::Sound sound(buffer->second);
#if SFML_VERSION_MAJOR < 3
    sound.setBuffer(buffer->second);
#endif
    sound.setVolume(m_soundVolume);
    sound.play();
    m_activeSounds.push_back(sound);
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
}

void AudioManager::setMusicVolume(float volume)
{
    m_musicVolume = std::clamp(volume, 0.0f, 100.0f);
    if (m_music)
    {
        m_music->setVolume(m_musicVolume);
    }
}

void AudioManager::removeStoppedSounds()
{
    m_activeSounds.erase(
        std::remove_if(
            m_activeSounds.begin(),
            m_activeSounds.end(),
            [](const sf::Sound& sound)
            {
#if SFML_VERSION_MAJOR >= 3
                return sound.getStatus() == sf::SoundSource::Status::Stopped;
#else
                return sound.getStatus() == sf::SoundSource::Stopped;
#endif
            }),
        m_activeSounds.end());
}
}
