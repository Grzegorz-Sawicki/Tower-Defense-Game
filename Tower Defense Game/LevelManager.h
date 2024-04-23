#pragma once

#include "include.h"
#include "Level.h"
#include "LevelScrollBox.h"

class LevelManager
{
private:
	std::vector<Enemy*> *enemies;
	Level* levels[50];

	LevelScrollBox* levelScrollOutline;
	std::vector<LevelScrollBox*> levelScrollBoxes;
	sf::Time scrollTimer;
	PausableClock scrollClock;
	int currentScrollCount=0;

	void handleJsonData();

	int currentLevel;
	int remainingEnemies;
	sf::Time levelTimer;
	PausableClock levelClock;

	Level* getCurrentLevel();

	bool canSpawn;

public:
	LevelManager(std::vector<Enemy*> &enemies);

	void nextLevel();
	void pause();
	void resume();

	int getLevel();
	sf::Time getLevelTimer();
	sf::Time getRemainingTime();
	bool canSpawnEnemies();

	LevelScrollBox& getLevelScrollOutline();
	std::vector<LevelScrollBox*>& getLevelScrollBoxes();

	void setSpawn(bool can);

	void update();
};

