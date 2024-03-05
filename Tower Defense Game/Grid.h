#pragma once

#include "include.h"
#include "Tile.h"
#include "Tower.h"

class Grid {
private:
    unsigned int m_rows;
    unsigned int m_cols;
    float m_tileSize;
    std::vector<std::vector<Tile>> m_tiles;

public:
    Grid(unsigned int rows, unsigned int cols, float tileSize);

    void draw(sf::RenderWindow& window);

    void handleMouseMove(const sf::Vector2f& mousePos);

    bool canPlaceTower(const sf::Vector2i& mousePos);
    Tower* placeTower(const sf::Vector2i& mousePos);
};



