#include "InfoWindowEnemy.h"

InfoWindowEnemy::InfoWindowEnemy(Enemy& enemy) : enemy(&enemy) {
	this->getEnemyInfo();
	this->setupTexts();
}

void InfoWindowEnemy::getEnemyInfo() {
	this->level = std::to_string(this->enemy->getLevel());
	this->flying = this->enemy->getFlying() ? "Yes" : "No";
	this->immune = this->enemy->getImmune() ? "Yes" : "No";
	this->health = std::to_string(this->enemy->getHp());
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << this->enemy->getSpeedBase();
	this->speed = ss.str();
}

void InfoWindowEnemy::setupTexts() {
	this->font = FontManager::instance().getFont("Fonts/PixellettersFull.ttf");

	this->nameText = sf::Text(this->nameStr + this->level, this->font, 24U);
	this->nameText.setPosition(this->mainBox.getPosition() + sf::Vector2f(5.f, -5.f));
	this->nameText.Bold;
	this->nameText.setFillColor(sf::Color::Black);

	this->flyingText = sf::Text(this->flyingStr, this->font, this->statBoxTextSize);
	this->flyingText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f));
	this->flyingText.setFillColor(sf::Color::Black);
	this->flyingValText = sf::Text(this->flying, this->font, this->statBoxTextSize);
	this->flyingValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f) + sf::Vector2f(this->statBox.getSize().x / 2, 0.f));
	this->flyingValText.setFillColor(sf::Color::Yellow);

	this->immuneText = sf::Text(this->immuneStr, this->font, this->statBoxTextSize);
	this->immuneText.setPosition(this->statBox.getPosition() + sf::Vector2f(5, -5.f + 1 * this->statBoxTextSpacing));
	this->immuneText.setFillColor(sf::Color::Black);
	this->immuneValText = sf::Text(this->immune, this->font, this->statBoxTextSize);
	this->immuneValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f + 1 * this->statBoxTextSpacing) + sf::Vector2f(this->statBox.getSize().x / 2, 0.f));
	this->immuneValText.setFillColor(sf::Color::Red);

	this->healthText = sf::Text(this->healthStr, this->font, this->statBoxTextSize);
	this->healthText.setPosition(this->statBox.getPosition() + sf::Vector2f(5, -5.f + 2 * this->statBoxTextSpacing));
	this->healthText.setFillColor(sf::Color::Black);
	this->healthValText = sf::Text(this->health, this->font, this->statBoxTextSize);
	this->healthValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f + 2 * this->statBoxTextSpacing) + sf::Vector2f(this->statBox.getSize().x / 2, 0.f));
	this->healthValText.setFillColor(sf::Color::Blue);

	this->speedText = sf::Text(this->speedStr, this->font, this->statBoxTextSize);
	this->speedText.setPosition(this->statBox.getPosition() + sf::Vector2f(5, -5.f + 3 * this->statBoxTextSpacing));
	this->speedText.setFillColor(sf::Color::Black);
	this->speedValText = sf::Text(this->speed, this->font, this->statBoxTextSize - 4);
	this->speedValText.setPosition(this->statBox.getPosition() + sf::Vector2f(5.f, -5.f + 3 * this->statBoxTextSpacing) + sf::Vector2f(this->statBox.getSize().x / 2, 3.f));
	this->speedValText.setFillColor(sf::Color::Black);
}

void InfoWindowEnemy::render(sf::RenderTarget* target) {
	InfoWindow::render(target);
	target->draw(this->nameText);
	target->draw(this->flyingText);
	target->draw(this->flyingValText);
	target->draw(this->immuneText);
	target->draw(this->immuneValText);
	target->draw(this->healthText);
	target->draw(this->healthValText);
	target->draw(this->speedText);
	target->draw(this->speedValText);
}