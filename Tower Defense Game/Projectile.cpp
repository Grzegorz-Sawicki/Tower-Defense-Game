#include "Projectile.h"

void Projectile::initSprite()
{
	this->sprite.setFillColor(sf::Color::Yellow);
	this->sprite.setRadius(4.f);
	this->sprite.setOrigin(4.f, 4.f);
}

Projectile::Projectile(float startX, float startY, Enemy* targetEnemy)
{
	this->initSprite();
	this->sprite.setPosition(startX, startY);
	this->speed = 2.f;
	this->damage = 5;
	this->destroyed = false;
	this->targetEnemy = targetEnemy;
	this->enemyDead = false;
	this->targetPos = this->targetEnemy->getPosition();
}

Projectile::~Projectile()
{

}

sf::Vector2f Projectile::getPosition()
{
	return this->sprite.getPosition();
}

Enemy* Projectile::getTargetEnemy() const
{
	return this->targetEnemy;
}

bool Projectile::isDestroyed()
{
	return this->destroyed;
}

void Projectile::update()
{
	if (this->targetEnemy->isDead()) {
		this->enemyDead = true;
	}

	if (!this->enemyDead) {
		this->targetPos = this->targetEnemy->getPosition();
	}

	float dx = targetPos.x - this->getPosition().x;
	float dy = targetPos.y - this->getPosition().y;
	float length = std::sqrt(dx * dx + dy * dy);

	this->velocity = sf::Vector2f(dx / length * speed, dy / length * speed);
	this->sprite.setPosition(this->sprite.getPosition() + velocity);

	//temp
	if (length <= 1)
	{
		this->destroyed = true;
		this->targetEnemy->takeDamage(this->damage);
		std::cout << "Enemy " << this->targetEnemy << " takes " << damage << " damage. It now has " << this->targetEnemy->getHp() << " health!\n";
	}

}

void Projectile::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
