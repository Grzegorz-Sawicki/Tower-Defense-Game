#include "Tower.h"

void Tower::initSprite()
{
	this->sprite.setTexture(TextureManager::instance().getTexture("Textures/tower_basic.png"));
	this->sprite.setPosition(this->posX, this->posY);
}

void Tower::shoot(Enemy* enemy)
{
	std::cout << "Tower shoots at enemy!" << std::endl;
	projectiles.emplace_back(new Projectile(this->sprite.getPosition().x, this->sprite.getPosition().y, enemy));
}

Tower::Tower(int posX, int posY) : posX(posX), posY(posY)
{
	this->state = PASSIVE;
	this->initSprite();
	this->range = 60;
	this->shootSpeed = 1.f;
	this->shootInterval = sf::seconds(1.f / shootSpeed);

	this->radiusCircle.setFillColor(sf::Color::Transparent);
	this->radiusCircle.setOutlineColor(sf::Color::Red);
	this->radiusCircle.setOutlineThickness(1);
	this->radiusCircle.setRadius(this->range);
	this->radiusCircle.setOrigin(this->range, this->range);
	this->radiusCircle.setPosition(
		posX + 18,
		posY + 18);

}

Tower::~Tower()
{

}

sf::FloatRect Tower::getBounds()
{
	return this->sprite.getGlobalBounds();
}

void Tower::update(const std::vector<Enemy*>& enemies)
{
	for (auto& enemy : enemies) {
		float distance = std::sqrt(std::pow(enemy->getPosition().x - this->sprite.getPosition().x, 2) + std::pow(enemy->getPosition().y - this->sprite.getPosition().y, 2));
		if (distance <= this->range) {
			if (this->shootTimer >= this->shootInterval) {
				shoot(enemy);
				this->shootTimer = sf::Time::Zero;
			}
			break; // If one enemy is within range, stop checking for others
		}
	}

	this->updateProjectiles();

	//Increment shoot timer
	this->shootTimer += this->clock.restart();
}

void Tower::updateProjectiles()
{
	for (auto* projectile : this->projectiles)
	{
		projectile->update();

		if (projectile->isDestroyed()) {
			projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
		}
			
	}
}

void Tower::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->radiusCircle);

	for (auto* projectile : this->projectiles)
	{
		projectile->render(target);
	}
}
