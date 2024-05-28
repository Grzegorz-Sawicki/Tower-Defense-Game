#pragma once

#include "include.h"
#include "Level.h"
#include "LevelScrollBox.h"

class LevelManager
{
private:
	void handleJsonData();

	std::vector<Enemy*> *enemies;
	std::vector<Level*> levels;

	LevelScrollBox* levelScrollOutline;
	std::vector<LevelScrollBox*> levelScrollBoxes;
	sf::Time scrollTimer;
	PausableClock scrollClock;
	int currentScrollCount=0;

	int currentLevel=0;
	int maxLevel;
	bool canSpawn = false;
	int remainingEnemies;
	sf::Time levelTimer;
	PausableClock levelClock;

	Level* getCurrentLevel();

public:
	LevelManager(std::vector<Enemy*> &enemies);
	~LevelManager();

	bool nextLevel();
	void pause();
	void resume();

	int getLevel();
	Level* getLevelObject();
	int getMaxLevel();
	sf::Time getLevelTimer();
	sf::Time getRemainingTime();
	bool canSpawnEnemies();

	LevelScrollBox& getLevelScrollOutline();
	std::vector<LevelScrollBox*>& getLevelScrollBoxes();

	void setSpawn(bool can);

	void update();
};

