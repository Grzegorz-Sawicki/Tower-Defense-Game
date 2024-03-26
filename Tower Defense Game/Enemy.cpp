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

	moveCase(this->getCurrentTile()->getNeighbors()[this->currentArrow]);

	this->sprite.move(this->direction * moveSpeed);
}

void Enemy::moveCase(Tile* tile)
{
	//if (tile != nullptr && tile->getBounds().contains(this->sprite.getPosition())) {
	if (tile != nullptr && this->getPosition(true) == tile->getPosition()) {
		this->currentTile->occupyDec();
		this->currentTile = tile;
		
		Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];

		if(nextObjectiveTile != nullptr)
			this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)]->occupyInc();

		this->currentArrow = this->currentTile->getArrow(this->path);
		this->direction = utils::getArrowDirection(this->currentTile->getArrow(this->path));
	}
}

Enemy::Enemy(Tile* tile, sf::Vector2f spawnOffset, Path path) {
	initSprite();
	this->hp = 300;
	this->dead = false;
	this->currentTile = tile;
	this->currentTile->occupyInc();
	this->sprite.setPosition(this->currentTile->getPosition() + spawnOffset);
	this->path = path;
	if (this->path == Path::HORIZONTAL) this->direction = sf::Vector2f(1.f, 0.f);
	else if (this->path == Path::VERTICAL) this->direction = sf::Vector2f(0.f, 1.f);

	this->currentArrow = Arrow::DEFAULT;
	this->moveSpeed = 1.f;
	this->reachedEntrance = false;
}

Enemy::~Enemy()
{
	std::cout << "called destructor\n\n";
}

sf::Vector2f Enemy::getPosition(bool ignoreOffset)
{
	if (ignoreOffset) return this->getPosition() - this->getPositionOffset();
	return this->sprite.getPosition();
}

sf::Vector2f Enemy::getPositionOffset()
{
	return this->positionOffset;
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

void Enemy::setPositionOffset(sf::Vector2f offset)
{
	this->positionOffset = offset;
	this->sprite.setPosition(this->sprite.getPosition() + offset);
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
	sf::Vector2f dir = this->getDirection();
	this->sprite.setRotation(utils::getRotation(dir));

	if (!this->didReachedEntrance()) {
		this->sprite.move(this->direction * moveSpeed);
		if (this->getCurrentTile()->getPosition() == this->getPosition(true)) {
			this->reachedEntrance = true;
			this->currentArrow = this->currentTile->getArrow(this->path);
			this->direction = utils::getArrowDirection(this->currentTile->getArrow(this->path));

			Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];

			if (nextObjectiveTile != nullptr)
				this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)]->occupyInc();
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
