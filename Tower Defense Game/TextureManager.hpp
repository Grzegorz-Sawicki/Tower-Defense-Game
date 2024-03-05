#pragma once

#include "include.h"

class TextureManager {
public:
    static TextureManager& instance() {
        static TextureManager instance;
        return instance;
    }

    sf::Texture& getTexture(const std::string& filename);

private:
    std::unordered_map<std::string, sf::Texture> m_textures;

    TextureManager() {} // Private constructor to prevent instantiation
    TextureManager(const TextureManager&) = delete; // Delete copy constructor
    TextureManager& operator=(const TextureManager&) = delete; // Delete assignment operator
};

