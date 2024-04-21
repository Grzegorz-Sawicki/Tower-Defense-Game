#include "LevelManager.h"

void LevelManager::handleJsonData()
{
	std::ifstream file(Properties::jsonLevelsEasyFileName);
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

	json levels = jsonData["levels"];

	int lvlCount = 0;
	for (auto level : levels) {
		EnemyType type = utils::stringToEnemyType(level["type"]);
		int hp = level["health"];
		int count = level["count"];
		bool boss = level["boss"];

		lvlCount++;

		this->levels[lvlCount-1] = new Level(*this->enemies, lvlCount, count, hp, type, boss);
		
	}
}

Level* LevelManager::getCurrentLevel()
{
	return this->levels[this->currentLevel-1];
}

LevelManager::LevelManager(std::vector<Enemy*> &enemies) : enemies(&enemies)
{
	this->handleJsonData();

	this->levelScrollBox = new LevelScrollBox(this->levels[0], 0);

	this->canSpawn = false;
	this->currentLevel = 0;
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

LevelScrollBox& LevelManager::getLevelScrollBox()
{
	return *this->levelScrollBox;
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
