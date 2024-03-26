#pragma once

#include "include.h"
#include "Properties.h"

class Tile {
private:
    sf::RectangleShape shape;
    sf::Color baseColor;

    int row;
    int col;
    std::map<Arrow, Tile*> neighbors;
    std::map<Path, Arrow> pathArrows;
    std::map<Path, int> distanceFromExits;

    int occupyNumber;
    bool occupied;
    TileType type;

public:
    Tile(int row, int col, float x, float y, sf::Color baseColor, TileType type);
 
    void draw(sf::RenderWindow& window);

    void highlight(bool valid);
    void resetColor();

    //Accessors
    int getRow();
    int getCol();
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isOccupied();
    int getOccupyNumber();

    Arrow getArrow(Path path);
    int getDistanceFromExit(Path path);

    TileType getType();
    std::map<Arrow, Tile*> getNeighbors() const;
 
    //Setters
    void setOccupied(bool value);
    void setPosition(sf::Vector2f position);
    void setNeighbors(std::map<Arrow, Tile*> neighbors);

    void setArrow(Arrow directionArrow, Path path);
    void setDistanceFromExit(int distance, Path path);

    void setType(TileType type);
    void setBaseColor(sf::Color color);
    void setColor(sf::Color color);

    void occupyInc();
    void occupyDec();
};

