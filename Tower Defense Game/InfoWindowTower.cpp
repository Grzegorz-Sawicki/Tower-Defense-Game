#include "InfoWindowTower.h"

InfoWindowTower::InfoWindowTower(Tower& tower, bool mode) : tower(&tower)
{
	if (mode == 0) {
		this->getTowerInfo();
	}
	else {
		this->getUpgradeInfo();
	}

	this->setupTexts();
	this->setupButtons();
}

void InfoWindowTower::getTowerInfo()
{
	this->level = std::to_string(this->tower->getLevel());
	this->name = this->tower->getName();
	this->description = this->tower->getDescription();
	this->cost = std::to_string(this->tower->getCost());
	this->damage = std::to_string(this->tower->getDamage());
	this->range = std::to_string(this->tower->getRange());
	this->speed = this->tower->getSpeedStr();
	this->sellbuttonString = "sell for " + std::to_string(this->tower->getSellPrice());
}

void InfoWindowTower::setupTexts()
{
	this->font = FontManager::instance().getFont("Fonts/PixellettersFull.ttf");

	this->nameText = sf::Text(this->name + " Tower " + this->level, this->font, 24U);
	this->nameText.setPosition(this->mainBox.getPosition() + sf::Vector2f(5.f, -5.f));
	this->nameText.Bold;
	this->nameText.setFillColor(sf::Color::Black);

	std::string wrappedDesc = utils::wrapText(this->description, 270, this->font);
	this->descriptionText = sf::Text(wrappedDesc, this->font, 17U);
	this->descriptionText.setPosition(this->mainBox.getPosition() + sf::Vector2f(10.f, 20.f));
	this->descriptionText.setFillColor(sf::Color::Black);

	this->costText = sf::Text(this->costStr, this->font, this->statBoxTextSize);
	this->costText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f));
	this->costText.setFillColor(sf::Color::Black);
	this->costValText = sf::Text(this->cost, this->font, this->statBoxTextSize);
	this->costValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f) + sf::Vector2f(this->statBox.getSize().x / 2, 0.f));
	this->costValText.setFillColor(sf::Color::Yellow);

	this->damageText = sf::Text(this->damageStr, this->font, this->statBoxTextSize);
	this->damageText.setPosition(this->statBox.getPosition() + sf::Vector2f(5, -5.f + 1 * this->statBoxTextSpacing));
	this->damageText.setFillColor(sf::Color::Black);
	this->damageValText = sf::Text(this->damage, this->font, this->statBoxTextSize);
	this->damageValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f + 1 * this->statBoxTextSpacing) + sf::Vector2f(this->statBox.getSize().x / 2, 0.f));
	this->damageValText.setFillColor(sf::Color::Red);

	this->rangeText = sf::Text(this->rangeStr, this->font, this->statBoxTextSize);
	this->rangeText.setPosition(this->statBox.getPosition() + sf::Vector2f(5, -5.f + 2 * this->statBoxTextSpacing));
	this->rangeText.setFillColor(sf::Color::Black);
	this->rangeValText = sf::Text(this->range, this->font, this->statBoxTextSize);
	this->rangeValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f + 2 * this->statBoxTextSpacing) + sf::Vector2f(this->statBox.getSize().x / 2, 0.f));
	this->rangeValText.setFillColor(sf::Color::Blue);

	this->speedText = sf::Text(this->speedStr, this->font, this->statBoxTextSize);
	this->speedText.setPosition(this->statBox.getPosition() + sf::Vector2f(5, -5.f + 3 * this->statBoxTextSpacing));
	this->speedText.setFillColor(sf::Color::Black);
	this->speedValText = sf::Text(this->speed, this->font, this->statBoxTextSize-4);
	this->speedValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f + 3 * this->statBoxTextSpacing) + sf::Vector2f(this->statBox.getSize().x / 2, 3.f));
	this->speedValText.setFillColor(sf::Color::Black);

}

void InfoWindowTower::render(sf::RenderTarget* target)
{
	InfoWindow::render(target);
	target->draw(this->nameText);
	target->draw(this->descriptionText);
	target->draw(this->costText);
	target->draw(this->costValText);
	target->draw(this->damageText);
	target->draw(this->damageValText);
	target->draw(this->rangeText);
	target->draw(this->rangeValText);
	target->draw(this->speedText);
	target->draw(this->speedValText);
}

void InfoWindowTower::getUpgradeInfo()
{
	TowerUpgrade nextUpgrade = this->tower->getNextUpgrade();

	this->level = std::to_string(nextUpgrade.level);
	this->name = this->tower->getName();
	this->description = nextUpgrade.description;
	this->cost = std::to_string(nextUpgrade.cost);
	this->damage = std::to_string(nextUpgrade.damage);
	this->range = std::to_string(nextUpgrade.range);
	this->speed = nextUpgrade.speedStr;

	this->upgradeButtonString = "upgrade";
}

void InfoWindowTower::setupButtons()
{
	this->sellButton.setPosition(sf::Vector2f(690.f, 318.f));
	this->sellButton.setSize(sf::Vector2f(100.f, 25.f));
	this->sellButton.setFillColor(sf::Color::Red);

	this->sellButtonText = sf::Text(this->sellbuttonString, this->font, this->statBoxTextSize);
	this->sellButtonText.setFillColor(sf::Color::White);

	sf::FloatRect textRect = sellButtonText.getLocalBounds();
	sellButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	sellButtonText.setPosition(sellButton.getPosition().x + sellButton.getSize().x / 2.0f,
		sellButton.getPosition().y + sellButton.getSize().y / 2.0f);


	this->upgradeButton.setPosition(sf::Vector2f(772.f, 540.f));
	this->upgradeButton.setSize(sf::Vector2f(75.f, 25.f));
	this->upgradeButton.setFillColor(sf::Color::Green);

	this->upgradeButtonText = sf::Text(this->upgradeButtonString, this->font, this->statBoxTextSize);
	this->upgradeButtonText.setFillColor(sf::Color::White);

	textRect = upgradeButtonText.getLocalBounds();
	upgradeButtonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	upgradeButtonText.setPosition(upgradeButton.getPosition().x + upgradeButton.getSize().x / 2.0f,
		upgradeButton.getPosition().y + upgradeButton.getSize().y / 2.0f);

}

void InfoWindowTower::setPosition(sf::Vector2f pos)
{
	sf::Vector2f offset = pos - this->mainBox.getPosition();
	InfoWindow::setPosition(pos);


	(this->nameText).move(offset);
	(this->descriptionText).move(offset);
	(this->costText).move(offset);
	(this->costValText).move(offset);
	(this->damageText).move(offset);;
	(this->damageValText).move(offset);;
	(this->rangeText).move(offset);;
	(this->rangeValText).move(offset);;
	(this->speedText).move(offset);;
	(this->speedValText).move(offset);;
}

sf::RectangleShape& InfoWindowTower::getUpgradeButtonShape()
{
	return this->upgradeButton;
}

void InfoWindowTower::renderSellButton(sf::RenderTarget* target)
{
	target->draw(this->sellButton);
	target->draw(this->sellButtonText);
}

void InfoWindowTower::renderUpgradeButton(sf::RenderTarget* target)
{
	target->draw(this->upgradeButton);
	target->draw(this->upgradeButtonText);
}