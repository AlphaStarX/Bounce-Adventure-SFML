#include "BounceAdventure/Core/AssetManager.hpp"

#include <SFML/Config.hpp>

#include <stdexcept>

namespace BounceAdventure
{
const sf::Texture& AssetManager::texture(const std::string& id, const std::filesystem::path& path)
{
    const auto existing = m_textures.find(id);
    if (existing != m_textures.end())
    {
        return existing->second;
    }

    sf::Texture loaded;
    if (!loaded.loadFromFile(path.string()))
    {
        throw std::runtime_error("Failed to load texture: " + path.string());
    }

    auto [inserted, unused] = m_textures.emplace(id, std::move(loaded));
    static_cast<void>(unused);
    return inserted->second;
}

const sf::Font& AssetManager::font(const std::string& id, const std::filesystem::path& path)
{
    const auto existing = m_fonts.find(id);
    if (existing != m_fonts.end())
    {
        return existing->second;
    }

    sf::Font loaded;
#if SFML_VERSION_MAJOR >= 3
    if (!loaded.openFromFile(path))
#else
    if (!loaded.loadFromFile(path.string()))
#endif
    {
        throw std::runtime_error("Failed to load font: " + path.string());
    }

    auto [inserted, unused] = m_fonts.emplace(id, std::move(loaded));
    static_cast<void>(unused);
    return inserted->second;
}

bool AssetManager::hasTexture(const std::string& id) const
{
    return m_textures.find(id) != m_textures.end();
}

bool AssetManager::hasFont(const std::string& id) const
{
    return m_fonts.find(id) != m_fonts.end();
}
}
