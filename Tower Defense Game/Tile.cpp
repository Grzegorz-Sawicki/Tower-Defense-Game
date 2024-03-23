#include "Tile.h"

Tile::Tile(int row, int col, float x, float y, sf::Color baseColor, TileType type) : row(row), col(col), type(type) {
    this->shape.setSize(sf::Vector2f(Properties::tileSize, Properties::tileSize));
    this->shape.setPosition(x, y);
    this->shape.setOrigin(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2);
    this->baseColor = baseColor;
    this->shape.setFillColor(this->baseColor);
    this->occupied = false;
    this->occupyNumber = 0;
    this->directionArrow = Arrow::DEFAULT;
    this->neighbors = neighbors;
    this->distanceFromExit = -1;
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Tile::highlight(bool valid)
{
    if(valid)
        this->shape.setFillColor(sf::Color::Green);
    else
        this->shape.setFillColor(sf::Color::Red);
}

void Tile::resetColor()
{
    this->shape.setFillColor(this->baseColor);
}

int Tile::getRow()
{
    return this->row;
}

int Tile::getCol()
{
    return this->col;
}

sf::FloatRect Tile::getBounds() const
{
    return this->shape.getGlobalBounds();
}

sf::Vector2f Tile::getPosition() const
{
    return this->shape.getPosition();
}

bool Tile::isOccupied()
{
    return this->occupied;
}

int Tile::getOccupyNumber()
{
    return this->occupyNumber;
}

Arrow Tile::getArrow()
{
    return this->directionArrow;
}

int Tile::getDistanceFromExit()
{
    return this->distanceFromExit;
}

TileType Tile::getType()
{
    return this->type;
}

sf::Vector2f Tile::getMoveDirection() const
{
    sf::Vector2f directionValue;

    switch (this->directionArrow) {
    case Arrow::UP:
        directionValue = sf::Vector2f(0.f, -1.f);
        break;
    case Arrow::DOWN:
        directionValue = sf::Vector2f(0.f, 1.f);
        break;
    case Arrow::RIGHT:
        directionValue = sf::Vector2f(1.f, 0.f);
        break;
    case Arrow::LEFT:
        directionValue = sf::Vector2f(-1.f, 0.f);
        break;
    case Arrow::UPRIGHT:
        directionValue = sf::Vector2f(1.f, -1.f);
        break;
    case Arrow::UPLEFT:
        directionValue = sf::Vector2f(-1.f, -1.f);
        break;
    case Arrow::DOWNRIGHT:
        directionValue = sf::Vector2f(1.f, 1.f);
        break;
    case Arrow::DOWNLEFT:
        directionValue = sf::Vector2f(-1.f, 1.f);
        break;
    case Arrow::DEFAULT:
        directionValue = sf::Vector2f(1.f, 0.f);
        break;
    }

    return directionValue;
}

std::map<Arrow, Tile*> Tile::getNeighbors() const
{
    return this->neighbors;
}

void Tile::setOccupied(bool value)
{
    this->occupied = value;
}

void Tile::setPosition(sf::Vector2f position)
{
    this->shape.setPosition(position);
}

void Tile::setNeighbors(std::map<Arrow, Tile*> neighbors)
{
    this->neighbors = neighbors;
}

void Tile::setArrow(Arrow directionArrow)
{
    this->directionArrow = directionArrow;
}

void Tile::setDistanceFromExit(int distance)
{
    this->distanceFromExit = distance;
}

void Tile::setType(TileType type)
{
    this->type = type;
}

void Tile::setBaseColor(sf::Color color)
{
    this->baseColor = color;
}

void Tile::setColor(sf::Color color) {
    this->shape.setFillColor(color);
}

void Tile::occupyInc()
{
    this->occupyNumber++;
}

void Tile::occupyDec()
{
    this->occupyNumber--;
}
