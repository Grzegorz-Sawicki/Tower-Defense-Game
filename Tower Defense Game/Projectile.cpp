#include "Projectile.h"

void Projectile::initSprite()
{
	this->shape.setFillColor(sf::Color::Yellow);
	this->shape.setRadius(4.f);
	this->shape.setOrigin(4.f, 4.f);
}

Projectile::Projectile(float startX, float startY, Enemy* targetEnemy)
{
	this->initSprite();
	this->shape.setPosition(startX, startY);
	this->speed = 3.f;
	this->damage = 5;
	this->destroyed = false;
	this->targetEnemy = targetEnemy;
	this->targetPos = this->targetEnemy->getPosition();

	float dx = targetPos.x - startX;
	float dy = targetPos.y - startY;
	float length = std::sqrt(dx * dx + dy * dy);

	// Normalize the direction vector
	this->velocity = sf::Vector2f(dx / length * speed, dy / length * speed);
}

Projectile::~Projectile()
{

}

sf::Vector2f Projectile::getPosition()
{
	return this->shape.getPosition();
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
	this->targetPos = this->targetEnemy->getPosition();

	float dx = targetPos.x - this->getPosition().x;
	float dy = targetPos.y - this->getPosition().y;
	float length = std::sqrt(dx * dx + dy * dy);

	this->velocity = sf::Vector2f(dx / length * speed, dy / length * speed);
	this->shape.setPosition(this->shape.getPosition() + velocity);

	//temp
	if (std::abs(this->shape.getPosition().x - this->targetEnemy->getPosition().x <= 5)
		||
		std::abs(this->shape.getPosition().y - this->targetEnemy->getPosition().y <= 5))
	{
		this->destroyed = true;
		this->targetEnemy->takeDamage(this->damage);
		std::cout << "Enemy " << this->targetEnemy << " takes " << damage << " damage. It now has " << this->targetEnemy->getHp() << " health!\n";
	}

}

void Projectile::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
