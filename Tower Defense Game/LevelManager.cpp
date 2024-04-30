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

		this->levels.emplace_back(new Level(*this->enemies, lvlCount, count, hp, type, boss));
		this->levelScrollBoxes.emplace_back(new LevelScrollBox(this->levels[lvlCount - 1], (lvlCount - 1) * Properties::levelScrollBoxSize.x));
		
	}
}

Level* LevelManager::getCurrentLevel()
{
	return this->levels[this->currentLevel-1];
}

LevelManager::LevelManager(std::vector<Enemy*> &enemies) : enemies(&enemies)
{
	this->handleJsonData();

	this->levelScrollOutline = new LevelScrollBox();
	this->scrollTimer = Properties::levelTimer / Properties::levelScrollBoxSize.x;

	this->canSpawn = false;
	this->currentLevel = 0;
	this->levelTimer = Properties::levelTimer;
	this->nextLevel();
}

LevelManager::~LevelManager()
{
	for (auto* level : this->levels) {
		delete level;
	}

	for (auto* box : this->levelScrollBoxes) {
		delete box;
	}

	delete levelScrollOutline;
}

void LevelManager::nextLevel()
{
	if (this->currentLevel < this->levels.size()) {
		this->currentLevel++;
		this->levelClock.restart();
		this->getCurrentLevel()->activate();

		if (this->currentLevel > 1) {
			int requiredScrolls = static_cast<int>(Properties::levelScrollBoxSize.x);
			std::cout << this->currentScrollCount << " / " << requiredScrolls << std::endl;

			if (this->currentScrollCount < requiredScrolls) {
				for (auto* lbox : this->levelScrollBoxes) {
					lbox->move(sf::Vector2f(-(requiredScrolls - currentScrollCount), 0.f));
				}
			}
		}

		this->currentScrollCount = 0;
	}
}

void LevelManager::pause()
{
	for (auto* level : this->levels) {
		level->pauseClock();
	}
	this->levelClock.pause();
	this->scrollClock.pause();
}

void LevelManager::resume()
{
	for (auto* level : this->levels) {
		level->resumeClock();
	}
	this->levelClock.resume();
	this->scrollClock.resume();
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

LevelScrollBox& LevelManager::getLevelScrollOutline()
{
	return *this->levelScrollOutline;
}

std::vector<LevelScrollBox*>& LevelManager::getLevelScrollBoxes()
{
	return this->levelScrollBoxes;
}

void LevelManager::setSpawn(bool can)
{
	this->canSpawn = can;
}

void LevelManager::update()
{
	if (this->canSpawn) {
		this->levelClock.resume();
		this->scrollClock.resume();
		for (auto* level : this->levels)
		{
			level->update();
		}

		if (this->currentLevel < this->levels.size() && this->scrollClock.getElapsedTime() >= this->scrollTimer) {
			this->scrollClock.restart();
			for (auto* lbox : this->levelScrollBoxes) {
				lbox->move(sf::Vector2f(-1.f, 0.f));
			}
			this->currentScrollCount++;
		}

		if (this->levelClock.getElapsedTime() >= this->levelTimer) {
			this->levelClock.restart();
			this->nextLevel();
		}
	}
	else {
		this->levelClock.pause();
		this->scrollClock.pause();
	}
}
