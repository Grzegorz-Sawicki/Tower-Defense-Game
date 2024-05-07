#pragma once

#include "InfoWindow.h"
#include "Enemy.h"

class InfoWindowEnemy : public InfoWindow
{
private:
	Enemy* enemy;

	sf::Font font;

	std::string level;
	std::string flying;
	std::string immune;
	std::string health;
	std::string speed;

	std::string nameStr = "Creep Level ";
	std::string flyingStr = "Flying:";
	std::string immuneStr = "Immune:";
	std::string healthStr = "Health:";
	std::string speedStr = "Speed:";

	sf::Text nameText;
	sf::Text flyingText;
	sf::Text healthText;
	sf::Text immuneText;
	sf::Text speedText;
	sf::Text flyingValText;
	sf::Text healthValText;
	sf::Text immuneValText;
	sf::Text speedValText;

	sf::RectangleShape sellButton;
	sf::Text sellButtonText;
	std::string sellbuttonString;

	sf::RectangleShape upgradeButton;
	sf::Text upgradeButtonText;
	std::string upgradeButtonString;

	void getEnemyInfo();
	void setupTexts();

public:
	InfoWindowEnemy(Enemy& enemy);

	void render(sf::RenderTarget* target);
};

