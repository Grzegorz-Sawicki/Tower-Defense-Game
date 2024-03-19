#include "Tile.h"

Tile::Tile(int row, int col, float x, float y, sf::Color baseColor, bool occupied) : row(row), col(col), occupied(occupied) {
    this->shape.setSize(sf::Vector2f(Properties::tileSize, Properties::tileSize));
    this->shape.setPosition(x, y);
    this->shape.setOrigin(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2);
    this->baseColor = baseColor;
    this->shape.setFillColor(this->baseColor);
    this->directionArrow = Arrow::DEFAULT;
    this->type = TileType::DEFAULT;
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

//void Tile::pushOccupied()
//{
//    this->occupiedStack.push(true);
//    this->occupied = true;
//}
//
//void Tile::popOccupied()
//{
//    if (!this->occupiedStack.empty())
//        this->occupiedStack.pop();
//    else {
//        this->occupied = false;
//    }
//}

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

Arrow Tile::getArrow()
{
    return this->directionArrow;
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
