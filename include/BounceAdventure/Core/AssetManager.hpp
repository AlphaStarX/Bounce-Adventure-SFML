#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <string>
#include <unordered_map>

namespace BounceAdventure
{
class AssetManager
{
public:
    const sf::Texture& texture(const std::string& id, const std::filesystem::path& path);
    const sf::Font& font(const std::string& id, const std::filesystem::path& path);

    bool hasTexture(const std::string& id) const;
    bool hasFont(const std::string& id) const;

private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
};
}
