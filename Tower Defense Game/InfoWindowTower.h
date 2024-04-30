#pragma once

#include "InfoWindow.h"
#include "Tower.h"

class InfoWindowTower : public InfoWindow
{
private:
	Tower* tower;

	sf::Font font;

	std::string name;
	std::string description;
	std::string cost;
	std::string damage;
	std::string range;
	std::string speed;

	std::string costStr = "Cost:";
	std::string damageStr = "Damage:";
	std::string rangeStr = "Range:";
	std::string speedStr = "Speed:";

	sf::Text nameText;
	sf::Text descriptionText;
	sf::Text costText;
	sf::Text damageText;
	sf::Text rangeText;
	sf::Text speedText;
	sf::Text costValText;
	sf::Text damageValText;
	sf::Text rangeValText;
	sf::Text speedValText;

	sf::RectangleShape sellButton;
	sf::Text sellButtonText;
	std::string sellbuttonString;

	sf::RectangleShape upgradeButton;
	sf::Text upgradeButtonText;
	std::string upgradeButtonString;

	void getTowerInfo();
	void getUpgradeInfo();
	void setupTexts();
	void setupButtons();

public:
	InfoWindowTower(Tower& tower, bool mode);

	void setPosition(sf::Vector2f pos);
	sf::RectangleShape& getUpgradeButtonShape();

	void render(sf::RenderTarget* target);
	void renderSellButton(sf::RenderTarget* target);
	void renderUpgradeButton(sf::RenderTarget* target);
};

