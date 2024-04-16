#include "Level.h"

void Level::spawnEnemy()
{
	//Path path = static_cast<Path>(rand() % 2);

	Path path = Path::HORIZONTAL;

	Enemy* tmp = new Enemy(Grid::getEntranceTiles(), Path::HORIZONTAL, this->enemyType, this->enemyHealth);
	this->enemies->emplace_back(tmp);
}

Level::Level(std::vector<Enemy*>& enemies, unsigned count, unsigned health, EnemyType type)
{
	this->enemyCount = count;
	this->enemyHealth = health;
	this->enemyType = type;
	this->active = false;
	this->enemies = &enemies;
	if (this->enemyType == EnemyType::GROUP) this->enemySpawnTimer = sf::seconds(0);
	else this->enemySpawnTimer = Properties::enemySpawnTimer;
	this->spawnClock.pause();
}

unsigned Level::getEnemyCount()
{
	return this->enemyCount;
}

EnemyType Level::getEnemyType()
{
	return this->enemyType;
}

sf::Time Level::getSpawnClock()
{
	return this->spawnClock.getElapsedTime();
}

void Level::activate()
{
	this->active = true;
	this->spawnClock.resume();
	this->spawnClock.restart();
}

void Level::pauseClock()
{
	this->spawnClock.pause();
}

void Level::resumeClock()
{
	this->spawnClock.resume();
}

void Level::update()
{
	if (this->active && this->enemyCount > 0) {
		if (this->spawnClock.getElapsedTime() >= this->enemySpawnTimer) {
			this->spawnClock.restart();

			this->spawnEnemy();
			this->enemyCount--;
		}
	}
}

