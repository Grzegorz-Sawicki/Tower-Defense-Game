#include "Enemy.h"

void Enemy::initSprite()
{
	this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_basic.png"));
	this->sprite.rotate(90);
}


Enemy::Enemy()
{
	initSprite();
	this->hp = 10;
}

Enemy::~Enemy()
{
	
}

sf::Vector2f Enemy::getPosition()
{
	return this->sprite.getPosition();
}

int Enemy::getHp()
{
	return this->hp;
}

//Functions

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;
}

void Enemy::update()
{
	this->sprite.move(sf::Vector2f(1.f, 0.f));
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
