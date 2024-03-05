#include "TextureManager.hpp"

sf::Texture& TextureManager::getTexture(const std::string& filename) {
    if (m_textures.find(filename) == m_textures.end()) {
        // Texture not found, load it
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            // Error loading texture
            // Handle error or throw exception
        }
        m_textures[filename] = texture;
    }
    return m_textures[filename];
}