#pragma once

#include "include.h"

class FontManager {
public:
    static FontManager& instance() {
        static FontManager instance;
        return instance;
    }

    sf::Font& getFont(const std::string& filename);

private:
    std::unordered_map<std::string, sf::Font> m_fonts;

    FontManager() {} // Private constructor to prevent instantiation
    FontManager(const FontManager&) = delete; // Delete copy constructor
    FontManager& operator=(const FontManager&) = delete; // Delete assignment operator
};
