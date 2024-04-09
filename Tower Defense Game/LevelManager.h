#pragma once

#include "include.h"
#include "Level.h"

class LevelManager
{
private:
	std::vector<Enemy*> *enemies;
	Level* levels[50];

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

	void setSpawn(bool can);

	void update();
};

