#pragma once

#include "include.h"
#include "Enemy.h"
#include "Grid.h"

class Level
{
private:
	std::vector<Enemy*>* enemies;
	PausableClock spawnClock;
	sf::Time enemySpawnTimer;

	unsigned count;
	unsigned health;
	EnemyType type;
	bool boss;
	int number;
	//unsigned enemyType;

	bool active;

	void spawnEnemy();

public:
	Level(std::vector<Enemy*>& enemies, int number, unsigned count, unsigned health, EnemyType type, bool boss);

	unsigned getEnemyCount();
	EnemyType getEnemyType();
	int getNumber();
	sf::Time getSpawnClock();

	void activate();
	void pauseClock();
	void resumeClock();

	void update();
};

