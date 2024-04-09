#include "LevelManager.h"

Level* LevelManager::getCurrentLevel()
{
	return this->levels[this->currentLevel-1];
}

LevelManager::LevelManager(std::vector<Enemy*> &enemies)
{
	this->canSpawn = false;
	this->currentLevel = 0;

	for (int i = 0; i < 50; i++) {
		levels[i] = new Level(enemies, 10, 20);
	}

	//levels[0] = new Level(enemies, 10, 20);
	//levels[1] = new Level(enemies, 10, 26);
	//levels[2] = new Level(enemies, 10, 30);
	//levels[3] = new Level(enemies, 10, 33);
	//levels[4] = new Level(enemies, 10, 36);

	this->enemies = &enemies;

	this->levelTimer = Properties::levelTimer;
	this->nextLevel();
}

void LevelManager::nextLevel()
{
	if (this->currentLevel < 50) {
		this->currentLevel++;
		this->levelClock.restart();
		this->getCurrentLevel()->activate();
	}
}

void LevelManager::pause()
{
	for (auto* level : this->levels) {
		level->pauseClock();
	}
	this->levelClock.pause();
}

void LevelManager::resume()
{
	for (auto* level : this->levels) {
		level->resumeClock();
	}
	this->levelClock.resume();
}

int LevelManager::getLevel()
{
	return this->currentLevel;
}

sf::Time LevelManager::getLevelTimer()
{
	return this->getCurrentLevel()->getSpawnClock();
}

sf::Time LevelManager::getRemainingTime()
{
	return this->levelTimer - this->levelClock.getElapsedTime();
}

bool LevelManager::canSpawnEnemies()
{
	return this->canSpawn;
}

void LevelManager::setSpawn(bool can)
{
	this->canSpawn = can;
}

void LevelManager::update()
{
	if (this->canSpawn) {
		this->levelClock.resume();
		for (auto* level : this->levels)
		{
			level->update();
		}

		if (this->levelClock.getElapsedTime() >= this->levelTimer) {
			this->levelClock.restart();
			this->nextLevel();
		}
	}
	else {
		this->levelClock.pause();
	}
}
