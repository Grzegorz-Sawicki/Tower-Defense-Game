#include "Enemy.h"

void Enemy::initSprite()
{
	this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_basic.png"));
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.rotate(90);
}

void Enemy::move()
{
	Tile* right = this->getCurrentTile()->getNeighbors()[Arrow::RIGHT];
	Tile* left = this->getCurrentTile()->getNeighbors()[Arrow::LEFT];
	Tile* up = this->getCurrentTile()->getNeighbors()[Arrow::UP];
	Tile* down = this->getCurrentTile()->getNeighbors()[Arrow::DOWN];
	Tile* upright = this->getCurrentTile()->getNeighbors()[Arrow::UPRIGHT];
	Tile* downright = this->getCurrentTile()->getNeighbors()[Arrow::DOWNRIGHT];
	Tile* upleft = this->getCurrentTile()->getNeighbors()[Arrow::UPLEFT];
	Tile* downleft = this->getCurrentTile()->getNeighbors()[Arrow::DOWNLEFT];

	moveCase(this->getCurrentTile()->getNeighbors()[this->currentTile->getArrow()]);

	this->sprite.move(this->direction * moveSpeed);
}

void Enemy::moveCase(Tile* tile)
{
	if (tile != nullptr && tile->getBounds().contains(this->sprite.getPosition())) {
		//this->currentTile->popOccupied();

		this->currentTile = tile;
		//this->currentTile->pushOccupied();
		this->direction = this->currentTile->getMoveDirection();
		//std::cout << this->currentTile << "\n";
	}
}

Enemy::Enemy(Tile* tile, sf::Vector2f spawnOffset) {
	initSprite();
	this->hp = 300;
	this->dead = false;
	this->currentTile = tile;
	this->sprite.setPosition(this->currentTile->getPosition() + spawnOffset);
	this->direction = sf::Vector2f(1.f, 0.f);
	this->moveSpeed = 1.f;
	this->reachedEntrance = false;
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

sf::Vector2f Enemy::getDirection()
{
	return this->direction;
}

Tile* Enemy::getCurrentTile()
{
	return this->currentTile;
}

bool Enemy::didReachedEntrance()
{
	return this->reachedEntrance;
}

void Enemy::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void Enemy::setCurrentTile(Tile* tile)
{
	this->currentTile = tile;
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
	if (!this->didReachedEntrance()) {
		this->sprite.move(this->direction * moveSpeed);
		if (this->sprite.getGlobalBounds().contains(this->getCurrentTile()->getPosition())) {
			this->reachedEntrance = true;
			this->direction = this->currentTile->getMoveDirection();
		}
	}
	else {
		this->move();
	}
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
