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
    std::map<std::string, std::vector<Tile*>> entranceTiles;
    std::map<std::string, std::vector<Tile*>> exitTiles;

    void moveToCorrectPlace();

public:
    Grid(unsigned int rows, unsigned int cols, float tileSize);

    void draw(sf::RenderWindow& window);

    void handleMouseMove(const sf::Vector2f& mousePos);

    std::map<std::string, std::vector<Tile*>> getEntranceTiles();
    std::map<std::string, std::vector<Tile*>> getExitTiles();

    bool canPlaceTower(const sf::Vector2i& mousePos);
    Tower* placeTower(const sf::Vector2i& mousePos);
};



