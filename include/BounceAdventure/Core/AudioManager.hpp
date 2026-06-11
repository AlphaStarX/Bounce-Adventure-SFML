#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace BounceAdventure
{
class AudioManager
{
public:
    void loadSound(const std::string& id, const std::filesystem::path& path);
    void playSound(const std::string& id);

    void playMusic(const std::filesystem::path& path, bool loop);
    void stopMusic();

    void setSoundVolume(float volume);
    void setMusicVolume(float volume);

private:
    void removeStoppedSounds();

    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::vector<sf::Sound> m_activeSounds;
    std::unique_ptr<sf::Music> m_music;
    float m_soundVolume = 80.0f;
    float m_musicVolume = 60.0f;
};
}
