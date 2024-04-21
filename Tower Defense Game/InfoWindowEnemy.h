#pragma once

#include "InfoWindow.h"
#include "Enemy.h"

class InfoWindowEnemy: public InfoWindow
{
private:
	Enemy* enemy;

	std::string name;
	std::string flying = "Flying";
	std::string immune = "Immune";
	std::string health = "Health";
	std::string speed = "Speed";

	std::string flyingVal;
	std::string immuneVal;
	std::string healthVal;
	std::string speedVal;

	sf::Text nameText;
	sf::Text flyingText;
	sf::Text immuneText;
	sf::Text healthText;
	sf::Text speedText;

	void setupTexts();
public:
	InfoWindowEnemy(Enemy& enemy);
	InfoWindowEnemy();

	void update();
};

