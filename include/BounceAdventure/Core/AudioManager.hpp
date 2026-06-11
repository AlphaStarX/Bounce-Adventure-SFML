#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

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
    // Heap-allocated so neither buffer nor sound can ever move, even if the
    // unordered_map rehashes. sf::Sound holds a raw pointer to its buffer
    // internally — moving the buffer would leave a dangling reference.
    struct SoundSlot
    {
        std::unique_ptr<sf::SoundBuffer> buffer;
        std::unique_ptr<sf::Sound> sound;
    };

    std::unordered_map<std::string, SoundSlot> m_sounds;
    std::unique_ptr<sf::Music> m_music;
    float m_soundVolume = 80.0f;
    float m_musicVolume = 60.0f;
};
}
