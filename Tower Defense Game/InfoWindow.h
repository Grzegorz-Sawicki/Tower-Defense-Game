#pragma once

#include "include.h"

class InfoWindow
{
protected:
	
	sf::RectangleShape mainBox;
	sf::RectangleShape statBox;

	void setupBoxes();
public:
	InfoWindow();

	void update();
	void render(sf::RenderTarget* target);
};

