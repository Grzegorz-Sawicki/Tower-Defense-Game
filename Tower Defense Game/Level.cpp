#include "Level.h"

void Level::spawnEnemy()
{
	Path path = Path::HORIZONTAL;
	Enemy* tmp = new Enemy(Grid::getEntranceTiles(), Path::HORIZONTAL, this->type, this->health, this->boss, this->gold, this->number);
	this->enemies->emplace_back(tmp);
}

Level::Level(std::vector<Enemy*>& enemies, int gold, int number, unsigned count, unsigned health, EnemyType type, bool boss) : 
	gold(gold), number(number), count(count), health(health), type(type), boss(boss)
{
	this->enemies = &enemies;
	if (this->type == EnemyType::GROUP) this->enemySpawnTimer = sf::seconds(0);
	else this->enemySpawnTimer = Properties::enemySpawnTimer;
	this->spawnClock.pause();
}

unsigned Level::getEnemyCount()
{
	return this->count;
}

EnemyType Level::getEnemyType()
{
	return this->type;
}

int Level::getNumber()
{
	return this->number;
}

sf::Time Level::getSpawnClock()
{
	return this->spawnClock.getElapsedTime();
}

bool Level::isBoss()
{
	return this->boss;
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
	if (this->active && this->count > 0) {
		if (this->spawnClock.getElapsedTime() >= this->enemySpawnTimer) {
			this->spawnClock.restart();

			this->spawnEnemy();
			this->count--;
		}
	}
}

