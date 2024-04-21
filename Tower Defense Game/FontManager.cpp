#include "FontManager.hpp"

sf::Font& FontManager::getFont(const std::string& filename) {
    if (m_fonts.find(filename) == m_fonts.end()) {
        // Font not found, load it
        sf::Font font;
        if (!font.loadFromFile(filename)) {
            // Error loading font
            // Handle error or throw exception
            std::cout << "ERROR LOADING FONT" << std::endl;
        }
        m_fonts[filename] = font;
    }
    return m_fonts[filename];
}