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
    bool isOccupied();

    void setOccupied(bool value);

    void setColor();
};

