#include "Enemy.h"

void Enemy::handleJsonData()
{
	std::ifstream file(Properties::jsonEnemiesFileName);
	if (!file.is_open()) {
		std::cerr << "Failed to open JSON file." << std::endl;
		system("pause");
	}

	json jsonData;
	try {
		file >> jsonData;
	}
	catch (json::parse_error& e) {
		std::cerr << "Parse error: " << e.what() << std::endl;
		system("pause");
	}

	file.close();

	json enemies = jsonData["enemies"];

	json enemy = enemies[static_cast<int>(type)];
	this->moveSpeedBase = enemy["speed"];
	this->moveSpeed = this->moveSpeedBase;
	this->initSprite(enemy["texture"]);


	this->effects = enemy["effects"];

	//ENEMY EFFECTS:
	/*
		group - spawn all at once
		immune - immune to slow
		spawn - spawn 2 spawned enemies with half health
		flying - ignores path
	*/

	for (json effect : this->effects) {
		if (effect["name"] == "GROUP") {
			this->group = true;
		}
		else if (effect["name"] == "IMMUNE") {
			this->immune = true;
		}
		else if (effect["name"] == "SPAWN") {
			this->spawn = true;
		}
		else if (effect["name"] == "FLYING") {
			this->flying = true;
		}
	}

	//BOSS HANDLING
	json boss = jsonData["BOSS"];
	if (this->boss) {
		this->sprite.setScale(sf::Vector2f(boss["scale"], boss["scale"]));
		this->moveSpeedBase = boss["speed"];
		this->moveSpeed = this->moveSpeedBase;
	}
}

void Enemy::initSprite(json texture)
{
	this->sprite.setTexture(TextureManager::instance().getTexture(texture));
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
	Tile* neighborTile = this->getCurrentTile()->getNeighbors()[this->currentArrow];

	if (neighborTile != nullptr && utils::getDistance(this->getPosition(true), neighborTile->getPosition()) <= 1.f) {
		if (!this->flying) this->currentTile->occupyDec();
		this->currentTile = neighborTile;

		Tile* nextObjectiveTile;
		if (this->flying) nextObjectiveTile = this->currentTile->getNeighbors()[this->currentArrow];
		else nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];

		if (nextObjectiveTile != nullptr && !this->flying)
			this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)]->occupyInc();

		if (!this->flying) {
			this->currentArrow = this->currentTile->getArrow(this->path);
			this->direction = utils::getArrowDirection(this->currentTile->getArrow(this->path));
		}
	}

	this->move(this->direction * moveSpeed);
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

Enemy::Enemy(std::map<Path, std::vector<Tile*>> entranceTiles, Path path, EnemyType type, int hp, bool boss, int gold, int level) : 
	path(path), type(type), boss(boss), gold(gold), level(level), hp(hp), maxhp(hp)
{
	this->handleJsonData();

	this->currentTile = this->chooseSpawnTile(entranceTiles);
	this->currentTile->occupyInc();
	this->sprite.setPosition(this->currentTile->getPosition() + this->createSpawnOffset());
	this->setPositionOffset(this->createPositionOffset());
	this->direction = this->createSpawnDirection();
	if (this->path == Path::HORIZONTAL) this->currentArrow = Arrow::RIGHT;
	else if (this->path == Path::VERTICAL) this->currentArrow = Arrow::DOWN;

	this->initHealthBar();
}

Enemy::Enemy(const Enemy& other, sf::Vector2f offset)
{
	this->level = other.level;
	this->boss = other.boss;
	this->currentArrow = other.currentArrow;
	this->currentTile = other.currentTile;
	this->reachedEntrance = other.reachedEntrance;
	this->path = other.path;
	this->direction = other.direction;
	this->effects = other.effects;
	this->healthBar = other.healthBar;
	this->healthBarRed = other.healthBarRed;
	this->moveSpeedBase = other.moveSpeedBase;
	this->moveSpeed = other.moveSpeedBase;
	this->slowClock = other.slowClock;
	this->slowLength = other.slowLength;
	this->stunClock = other.stunClock;
	this->stunLength = other.stunLength;

	this->unDie();

	this->maxhp = other.maxhp / 2;
	this->hp = this->maxhp;
	this->gold = 0;
	this->dead = false;
	this->sprite = sf::Sprite();
	this->type = EnemyType::SPAWNED;
	this->handleJsonData();
	this->sprite.setPosition(other.sprite.getPosition());
	this->sprite.move(-other.positionOffset);
	this->positionOffset = offset;
	this->setPositionOffset(offset);


	this->initHealthBar();
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

void Enemy::unDie()
{
	this->currentTile->occupyInc();
	Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];
	if (nextObjectiveTile != nullptr && this->reachedEntrance)
		nextObjectiveTile->occupyInc();
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
	if (!this->immune) {
		this->moveSpeed = this->moveSpeedBase;

		this->slowed = true;
		this->slowValue = value;
		this->slowLength = sf::seconds(length);
		this->moveSpeed *= (1 - slowValue);
		this->slowClock.restart();
	}
}

void Enemy::setPositionOffset(sf::Vector2f offset)
{
	this->positionOffset = offset;
	this->sprite.setPosition(this->sprite.getPosition() + offset);
}

int Enemy::getMaxHp()
{
	return this->maxhp;
}

void Enemy::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void Enemy::setCurrentTile(Tile* tile)
{
	this->currentTile = tile;
}

bool Enemy::isBoss()
{
	return this->boss;
}

int Enemy::getGold()
{
	return this->gold;
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
	if (!this->dead) {
		this->hp -= damage;
		if (this->hp <= 0) {
			this->die();
		}
		else {
			this->updateHealthBar();
		}
	}
}

int Enemy::getLevel()
{
	return this->level;
}

bool Enemy::getFlying()
{
	return this->flying;
}

void Enemy::die()
{
	if (!this->flying) {
		this->currentTile->occupyDec();
		Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];
		if (nextObjectiveTile != nullptr && this->reachedEntrance)
			nextObjectiveTile->occupyDec();
	}

	this->dead = true;

	this->healthBar.setSize(sf::Vector2f(0, 0));
	this->healthBarRed.setSize(sf::Vector2f(0, 0));
}

bool Enemy::getImmune()
{
	return this->immune;
}

float Enemy::getSpeedBase()
{
	return this->moveSpeedBase;
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
			this->updateDistanceFromExit();

			if (this->slowed) {
				if (this->slowClock.getElapsedTime() >= this->slowLength) {
					this->slowed = false;
					this->moveSpeed = this->moveSpeedBase;
				}
			}

			if (!this->didReachedEntrance()) {
				this->move(this->direction * moveSpeed);
				if (utils::getDistance(this->getCurrentTile()->getPosition(), this->getPosition(true)) <= 1.f) {
					this->reachedEntrance = true;
					if (!this->flying) {
						this->currentArrow = this->currentTile->getArrow(this->path);
						this->direction = utils::getArrowDirection(this->currentTile->getArrow(this->path));

						Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)];

						if (nextObjectiveTile != nullptr)
							this->currentTile->getNeighbors()[this->currentTile->getArrow(this->path)]->occupyInc();
					}
					else {
						Tile* nextObjectiveTile = this->currentTile->getNeighbors()[this->currentArrow];
					}
				}
			}
			else {
				this->moveCase();
			}
		}
	}
}

sf::Sprite Enemy::getSprite()
{
	return this->sprite;
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->healthBarRed);
	target->draw(this->healthBar);
}

void Enemy::setDead(bool dead)
{
	this->dead = dead;
}

void Enemy::setMaxHp(int maxHp)
{
	this->maxhp = maxHp;
}

void Enemy::setHp(int hp)
{
	this->hp = hp;
}

void Enemy::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

int Enemy::getDistanceFromExit()
{
	return this->distanceFromExit;
}

void Enemy::updateDistanceFromExit()
{
	if (this->flying) {
		this->distanceFromExit = this->currentTile->getStraightDistanceFromExit(this->path);
	}
	else {
		this->distanceFromExit = this->currentTile->getDistanceFromExit(this->path);
	}
}
