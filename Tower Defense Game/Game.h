#pragma once

#include "include.h"
#include "Grid.h"
#include "Enemy.h"
#include "Tower.h"
#include "TextureManager.hpp"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;

	sf::Sprite bgSprite;
	sf::Texture bgTexture;

	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;

	unsigned level;
	unsigned lives;
	unsigned gold;
	unsigned score;

	//temp
	bool canSpawn;

	//Functions
	void initWindow();
	void initBackground();
	void initVariables();
	void initGrid();

	sf::Time enemySpawnTimer;
	void spawnEnemy();

public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Functions
	void run();

	void updatePollEvents();
	void update();

	void render();
};

