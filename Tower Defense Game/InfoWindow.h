#pragma once

#include "include.h"
#include "FontManager.hpp"

/* TOWER

NAME
DESCRIPTION*/

class InfoWindow
{
protected:
	const unsigned int statBoxTextSize = 24U;
	const float statBoxTextSpacing = 25U;
	
	sf::RectangleShape mainBox;
	sf::RectangleShape statBox;

	void setupBoxes();
public:
	InfoWindow();

	void setPosition(sf::Vector2f pos);

	void update();
	void render(sf::RenderTarget* target);
};

