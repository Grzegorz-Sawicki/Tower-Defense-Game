#pragma once

#include "include.h"
#include "Properties.h"

enum class Arrow {
    DEFAULT, UP, RIGHT, DOWN, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT
};

enum class TileType {
    DEFAULT, ENTRANCE, EXIT
};

class Tile {
private:
    sf::RectangleShape shape;
    sf::Color baseColor;

    int row;
    int col;
    std::map<Arrow, Tile*> neighbors;
    Arrow directionArrow;

    std::queue<bool> occupiedStack;
    bool occupied;
    TileType type;

public:
    Tile(int row, int col, float x, float y, sf::Color baseColor, bool occupied);
 
    void draw(sf::RenderWindow& window);

    void highlight(bool valid);
    void resetColor();

    //void pushOccupied();
    //void popOccupied();

    //Accessors
    int getRow();
    int getCol();
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    bool isOccupied();
    Arrow getArrow();
    TileType getType();
    sf::Vector2f getMoveDirection() const;
    std::map<Arrow, Tile*> getNeighbors() const;
 
    void setOccupied(bool value);
    void setPosition(sf::Vector2f position);
    void setNeighbors(std::map<Arrow, Tile*> neighbors);
    void setArrow(Arrow directionArrow);
    void setType(TileType type);

    void setBaseColor(sf::Color color);
    void setColor(sf::Color color);
};

