#include "Tile.h"

Tile::Tile(int row, int col, float x, float y, sf::Color baseColor, TileType type) : row(row), col(col), type(type) {
    this->shape.setSize(sf::Vector2f(Properties::tileSize, Properties::tileSize));
    this->shape.setPosition(x, y);
    this->shape.setOrigin(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2);
    this->baseColor = baseColor;
    this->shape.setFillColor(this->baseColor);
    this->occupied = false;
    this->occupyNumber = 0;
    this->pathArrows[Path::HORIZONTAL] = Arrow::DEFAULT;
    this->pathArrows[Path::VERTICAL] = Arrow::DEFAULT;
    this->distanceFromExits[Path::HORIZONTAL] = -1;
    this->distanceFromExits[Path::VERTICAL] = -1;
    this->neighbors = neighbors;
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

sf::Vector2f Tile::getOrigin() const
{
    return this->shape.getOrigin();
}

bool Tile::isOccupied()
{
    return this->occupied;
}

int Tile::getOccupyNumber()
{
    return this->occupyNumber;
}

Arrow Tile::getArrow(Path path)
{
    return this->pathArrows[path];
}

int Tile::getDistanceFromExit(Path path)
{
    return this->distanceFromExits[path];
}

TileType Tile::getType()
{
    return this->type;
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

void Tile::setArrow(Arrow directionArrow, Path path)
{
    this->pathArrows[path] = directionArrow;
}

void Tile::setDistanceFromExit(int distance, Path path)
{
    this->distanceFromExits[path] = distance;
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
    //ENTRANCE DOESN"T SEEM TO WORK
    if (this->occupyNumber > 0) this->occupyNumber--;
}
