#include "Enemy.h"

void Enemy::initSprite()
{
	this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_basic.png"));
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.rotate(90);
}


Enemy::Enemy()
{
	initSprite();
	this->hp = 10;
	this->dead = false;
}

Enemy::Enemy(sf::Vector2f position) {
	initSprite();
	this->hp = 10;
	this->dead = false;
	this->sprite.setPosition(position);
}

Enemy::~Enemy()
{
	std::cout << "called destructor\n\n";
}

sf::Vector2f Enemy::getPosition()
{
	return this->sprite.getPosition();
}

sf::FloatRect Enemy::getBounds()
{
	return this->sprite.getGlobalBounds();
}

int Enemy::getHp()
{
	return this->hp;
}

bool Enemy::isDead()
{
	return this->dead;
}

//Functions

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;
	if (this->hp <= 0) {
		this->die();
	}
}

void Enemy::die()
{
	this->dead = true;
}

void Enemy::update()
{
	this->sprite.move(sf::Vector2f(1.f, 0.f));
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
