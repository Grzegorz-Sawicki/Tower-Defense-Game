#include "LevelScrollBox.h"

LevelScrollBox::LevelScrollBox(Level* level, float offset) : 
    levelNumber(level->getNumber()), enemyTypeString(utils::enemyTypeToString(level->getEnemyType())) 
{

    this->font = FontManager::instance().getFont("Fonts/PixellettersFull.ttf");

    shape.setSize(Properties::levelScrollBoxSize);
    this->setFillColor(Properties::darkGray);
    this->setPosition(Properties::levelScrollBoxPosition + sf::Vector2f(offset, 0.f));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);

    this->text.setString(enemyTypeString);
    this->text.setFont(font);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = this->text.getLocalBounds();
    this->text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    levelNumberText.setString(std::to_string(levelNumber));
    levelNumberText.setFont(font);
    levelNumberText.setCharacterSize(48);
    levelNumberText.setFillColor(sf::Color::Red);
    sf::FloatRect levelNumberBounds = levelNumberText.getLocalBounds();
    levelNumberText.setOrigin(levelNumberBounds.left + levelNumberBounds.width / 2.0f, levelNumberBounds.top + levelNumberBounds.height / 2.0f);
}

void LevelScrollBox::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
    text.setPosition(position.x + shape.getSize().x / 2.0f, position.y + shape.getSize().y / 2.0f);
    levelNumberText.setPosition(position.x + shape.getSize().x / 2.0f, position.y + shape.getSize().y / 2.0f);
}

void LevelScrollBox::setFillColor(sf::Color color) {
    shape.setFillColor(color);
}

void LevelScrollBox::setBorderColor(sf::Color color) {
    shape.setOutlineColor(color);
}

void LevelScrollBox::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(levelNumberText);
    window.draw(text);
}