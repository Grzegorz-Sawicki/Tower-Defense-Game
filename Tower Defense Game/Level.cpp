#include "Level.h"

void Level::spawnEnemy()
{
	//Path path = static_cast<Path>(rand() % 2);

	Path path = Path::HORIZONTAL;

	if (path == Path::HORIZONTAL) {
		int randSpawn = rand() % 6;
		Tile* spawnTile = Grid::getEntranceTiles()[Path::HORIZONTAL][randSpawn];
		sf::Vector2f spawnOffset = sf::Vector2f(-Properties::windowWidth / 10, 0);
		Enemy* tmp = new Enemy(spawnTile, spawnOffset, Path::HORIZONTAL);
		tmp->setPositionOffset(sf::Vector2f(0.f, -5 + rand() % 11));
		this->enemies->emplace_back(tmp);
	}
	//else if (path == Path::VERTICAL) {
	//	int randSpawn = rand() % 8;
	//	Tile* spawnTile = Grid::getEntranceTiles()[Path::VERTICAL][randSpawn];
	//	sf::Vector2f spawnOffset = sf::Vector2f(0, -Properties::windowHeight / 10);
	//	Enemy* tmp = new Enemy(spawnTile, spawnOffset, Path::VERTICAL);
	//	tmp->setPositionOffset(sf::Vector2f(-5 + rand() % 11, 0.f));
	//	enemies.emplace_back(tmp);
	//}
}

Level::Level(std::vector<Enemy*>& enemies, unsigned count, unsigned health)
{
	this->enemyCount = count;
	this->enemyHealth = health;
	this->active = false;
	this->enemies = &enemies;
	this->enemySpawnTimer = Properties::enemySpawnTimer;
	this->spawnClock.pause();
}

unsigned Level::getEnemyCount()
{
	return this->enemyCount;
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

