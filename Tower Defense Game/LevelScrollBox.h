#pragma once

#include "include.h"
#include "Level.h"
#include "FontManager.hpp"

class LevelScrollBox
{
private:
    const int levelNumber;
    const std::string enemyTypeString;

    sf::RectangleShape shape;
    sf::Text text;
    sf::Text levelNumberText;
    sf::Font font;

public:
    LevelScrollBox(Level* level, float offset);

    void setPosition(sf::Vector2f position);
    void setFillColor(sf::Color color);
    void setBorderColor(sf::Color color);
    void draw(sf::RenderWindow& window);
};

