#pragma once

#include "include.h"

class Tile {
private:
    sf::RectangleShape shape;

    sf::Color baseColor;

    bool occupied;

public:
    Tile(float x, float y, float size, sf::Color baseColor, bool occupied);

    void draw(sf::RenderWindow& window);

    void highlight(bool valid);
    void resetColor();

    //Accessors
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isOccupied();

    void setOccupied(bool value);
    void setPosition(sf::Vector2f position);

    void setBaseColor(sf::Color color);
    void setColor(sf::Color color);
};

