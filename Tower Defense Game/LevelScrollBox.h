#pragma once

#include "include.h"
#include "Level.h"
#include "FontManager.hpp"

class LevelScrollBox
{
private:
    int levelNumber;
    std::string enemyTypeString;
    Level* level;

    std::string decideEnemyTypeString();

    sf::RectangleShape shape;
    sf::Text text;
    sf::Text levelNumberText;
    sf::Font font;

public:
    LevelScrollBox(Level* level, float offset);
    LevelScrollBox();

    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f offset);
    void setFillColor(sf::Color color);
    void setBorderColor(sf::Color color);
    void draw(sf::RenderWindow& window);
};

