#include "InfoWindow.h"

void InfoWindow::setupBoxes()
{
	this->mainBox.setPosition(Properties::mainInfoBoxPosition);
	this->mainBox.setSize(Properties::mainInfoBoxSize);
	this->mainBox.setFillColor(Properties::mainInfoBoxBgColor);

	this->statBox.setPosition(Properties::subInfoBoxPosition);
	this->statBox.setSize(Properties::subInfoBoxSize);
	this->statBox.setFillColor(Properties::subInfoBoxBgColor);
}

InfoWindow::InfoWindow()
{
	this->setupBoxes();
}

void InfoWindow::setPosition(sf::Vector2f pos)
{
	sf::Vector2f offset = pos - this->mainBox.getPosition();
	this->mainBox.move(offset);
	this->statBox.move(offset);
}

void InfoWindow::update()
{
}

void InfoWindow::render(sf::RenderTarget* target)
{
	target->draw(mainBox);
	target->draw(statBox);
;}
