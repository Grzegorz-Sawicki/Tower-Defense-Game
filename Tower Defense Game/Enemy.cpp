#include "Enemy.h"

void Enemy::initSprite()
{
	switch (this->type) {
	case EnemyType::DEFAULT:
		this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_basic.png"));
		break;
	case EnemyType::GROUP:
		this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_group.png"));
		break;
	case EnemyType::IMMUNE:
		this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_immune.png"));
		break;
	case EnemyType::FAST:
		this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_fast.png"));
		break;
	case EnemyType::FLYING:
		this->sprite.setTexture(TextureManager::instance().getTexture("Textures/enemy_flying.png"));
		break;
	}

	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
	this->sprite.rotate(90);
}

void Enemy::initHealthBar()
{
	this->healthBarRed.setFillColor(sf::Color::Red);
	this->healthBarRed.setSize(Properties::sizeEnemyHealthBar);
	this->healthBarRed.setOrigin(this->healthBarRed.getGlobalBounds().width / 2, this->healthBarRed.getGlobalBounds().height / 2);
	this->healthBarRed.setPosition(this->sprite.getPosition() + sf::Vector2f(0, -15.f));

	this->healthBar.setFillColor(Properties::colorEnemyHealthBar);
	this->healthBar.setSize(Properties::sizeEnemyHealthBar);
	this->healthBar.setOrigin(this->healthBar.getGlobalBounds().width / 2, this->healthBar.getGlobalBounds().height / 2);
	this->healthBar.setPosition(this->sprite.getPosition() + sf::Vector2f(0, -15.f));
}

void Enemy::move(sf::Vector2f offset)
{
	this->sprite.move(offset);
	this->healthBar.move(offset);
	this->healthBarRed.move(offset);
}

void Enemy::moveCase()
{
	if (this->type == EnemyType::FLYING) {
		this->move(this->direction * moveSpeed);
	}
	else {
		Tile* right = this->getCurrentTile()->getNeighbors()[Arrow::RIGHT];
		Tile* left = this->getCurrentTile()->getNeighbors()[Arrow::LEFT];
		Tile* up = this->getCurrentTile()->getNeighbors()[Arrow::UP];
		Tile* down = this->getCurrentTile()->getNeighbors()[Arrow::DOWN];
		Tile* upright = this->getCurrentTile()->getNeighbors()[Arrow::UPRIGHT];
		Tile* downright = this->getCurrentTile()->getNeighbors()[Arrow::DOWNRIGHT];
		Tile* upleft = this->getCurrentTile()->getNeighbors()[Arrow::UPLEFT];
		Tile* downleft = this->getCurrentTile()->getNeighbors()[Arrow::DOWNLEFT];

		Tile* neighborTile = this->getCurrentTile()->getNeighbors()[this->currentArrow];

		if (neighborTile != nullptr && this->getPosition(true) == neighborTile->getPosition()) {
			this->currentTile->occupyDec();
			this->currentTile = neighborTile;

			Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];

			if (nextObjectiveTile != nullptr)
				this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)]->occupyInc();

			this->currentArrow = this->currentTile->getArrow(this->path);
			this->direction = utils::getArrowDirection(this->currentTile->getArrow(this->path));
		}

		this->move(this->direction * moveSpeed);
	}

}

Tile* Enemy::chooseSpawnTile(std::map<Path, std::vector<Tile*>> entranceTiles)
{
	if (path == Path::HORIZONTAL) {
		int randSpawn = rand() % 6;
		Tile* spawnTile = entranceTiles[Path::HORIZONTAL][randSpawn];
		return spawnTile;
	}
	else if (path == Path::VERTICAL) {
		int randSpawn = rand() % 8;
		Tile* spawnTile = entranceTiles[Path::VERTICAL][randSpawn];
		return spawnTile;
	}
}

sf::Vector2f Enemy::createPositionOffset()
{
	return sf::Vector2f(-5 + rand() % 11, -5 + rand() % 11);
}

sf::Vector2f Enemy::createSpawnDirection()
{
	if (this->path == Path::HORIZONTAL) return sf::Vector2f(1.f, 0.f);
	else if (this->path == Path::VERTICAL) return sf::Vector2f(0.f, 1.f);
}

sf::Vector2f Enemy::createSpawnOffset()
{
	if (path == Path::HORIZONTAL) {
		sf::Vector2f spawnOffset = sf::Vector2f(-Properties::windowWidth / 10, 0);
		return spawnOffset;
	}
	else if (path == Path::VERTICAL) {
		sf::Vector2f spawnOffset = sf::Vector2f(0, -Properties::windowHeight / 10);
		return spawnOffset;
	}
}

Enemy::Enemy(std::map<Path, std::vector<Tile*>> entranceTiles, Path path, EnemyType type, int hp) : path(path), type(type)
{
	this->moveSpeedBase = 1.f;
	this->moveSpeed = this->moveSpeedBase;

	this->initSprite();
	this->currentTile = this->chooseSpawnTile(entranceTiles);
	this->currentTile->occupyInc();
	this->sprite.setPosition(this->currentTile->getPosition() + this->createSpawnOffset());
	this->setPositionOffset(this->createPositionOffset());

	this->initHealthBar();
	this->dead = false;
	this->direction = this->createSpawnDirection();
	this->currentArrow = Arrow::DEFAULT;
	this->reachedEntrance = false;
	this->maxhp = hp;
	this->hp = hp;
}

Enemy::~Enemy()
{

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

EnemyType Enemy::getType()
{
	return this->type;
}

Tile* Enemy::getCurrentTile()
{
	return this->currentTile;
}

bool Enemy::didReachedEntrance()
{
	return this->reachedEntrance;
}

void Enemy::setSlow(float value, float length)
{
	this->moveSpeed = this->moveSpeedBase;

	this->slowed = true;
	this->slowValue = value;
	this->slowLength = sf::seconds(length);
	this->moveSpeed *= (1-slowValue);
	this->slowClock.restart();
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

void Enemy::setStun(float length)
{
	this->stunned = true;
	this->stunLength = sf::seconds(length);
	this->stunClock.restart();
}

//Functions

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;
	if (!this->dead && this->hp <= 0) {
		this->die();
	}
	else {
		this->updateHealthBar();
	}
}

void Enemy::die()
{
	this->currentTile->occupyDec();
	Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];
	if (nextObjectiveTile != nullptr && this->reachedEntrance)
		nextObjectiveTile->occupyDec();
	this->dead = true;
}

void Enemy::updateHealthBar()
{
	this->healthBar.setSize(sf::Vector2f(Properties::sizeEnemyHealthBar.x * this->hp / this->maxhp, this->healthBar.getSize().y));
}

void Enemy::update()
{
	if (!dead) {
		if (this->stunned) {
			if (this->stunClock.getElapsedTime() >= this->stunLength) {
				this->stunned = false;
			}
		}
		if (!this->stunned) {
			sf::Vector2f dir = this->getDirection();
			this->sprite.setRotation(utils::getRotation(dir));

			if (this->slowed) {
				if (this->slowClock.getElapsedTime() >= this->slowLength) {
					this->slowed = false;
					this->moveSpeed = this->moveSpeedBase;
				}
			}

			if (!this->didReachedEntrance()) {
				this->move(this->direction * moveSpeed);
				if (this->getCurrentTile()->getPosition() == this->getPosition(true)) {
					this->reachedEntrance = true;
					if (this->type != EnemyType::FLYING) {
						this->currentArrow = this->currentTile->getArrow(this->path);
						this->direction = utils::getArrowDirection(this->currentTile->getArrow(this->path));

						Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];

						if (nextObjectiveTile != nullptr)
							this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)]->occupyInc();
					}
				}
			}
			else {
				this->moveCase();
			}
		}
	}
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->healthBarRed);
	target->draw(this->healthBar);
}
