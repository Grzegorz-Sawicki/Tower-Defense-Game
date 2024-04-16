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

	unsigned enemyCount;
	unsigned enemyHealth;
	EnemyType enemyType;
	//unsigned enemyType;

	bool active;

	void spawnEnemy();

public:
	Level(std::vector<Enemy*>& enemies, unsigned count, unsigned health, EnemyType type);

	unsigned getEnemyCount();
	EnemyType getEnemyType();
	sf::Time getSpawnClock();

	void activate();
	void pauseClock();
	void resumeClock();

	void update();
};

