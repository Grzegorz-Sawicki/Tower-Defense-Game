#include "Tile.h"

Tile::Tile(float x, float y, float size, sf::Color baseColor, bool occupied) : shape(sf::Vector2f(size, size)), occupied(occupied) {
    this->shape.setPosition(x, y);

    this->baseColor = baseColor;
    this->shape.setFillColor(this->baseColor);
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

sf::FloatRect Tile::getBounds() const
{
    return this->shape.getGlobalBounds();
}

bool Tile::isOccupied()
{
    return this->occupied;
}

void Tile::setOccupied(bool value)
{
    this->occupied = value;
}



void Tile::setColor() {
    this->shape.setFillColor(sf::Color(255, 255, 255, 100));
}
