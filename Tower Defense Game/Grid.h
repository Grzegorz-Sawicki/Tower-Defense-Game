#pragma once

#include "include.h"
#include "Tile.h"
#include "Tower.h"

class Grid {
private:
    Grid();

    static unsigned int m_rows;
    static unsigned int m_cols;
    static float m_tileSize;
    static std::vector<std::vector<Tile>> m_tiles;
    static std::map<Path, std::vector<Tile*>> entranceTiles;
    static std::map<Path, std::vector<Tile*>> exitTiles;

    const std::vector<Enemy*>& enemies;

    static void moveToCorrectPlace();

public:
    Grid(std::vector<Enemy*>& enemies);
    // Deleted copy constructor and assignment operator to prevent cloning
    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    // Static method to access the singleton instance
    static Grid& getInstance(std::vector<Enemy*>& enemies);

    static void draw(sf::RenderWindow& window);

    static void handleMouseMove(const sf::Vector2f& mousePos);

    static std::map<Path, std::vector<Tile*>> getEntranceTiles();
    static std::map<Path, std::vector<Tile*>> getExitTiles();
    static Tile* getNearestTile(sf::Vector2f position);

    static std::map<Arrow, Tile*> setupTileNeighbors(int row, int col);
    static void resetTiles();
    static void resetPath(Path path);
    static void resetPaths();
    static void createPath(Path path);
    static void createPaths();
    static void visualizePath(Path path);
    static void visualizePaths();
    static void visualizeOccupy();

    static bool canPlaceTower(const sf::Vector2i& mousePos);
    Tower* placeTower(const sf::Vector2i& mousePos, TowerType type);
};



