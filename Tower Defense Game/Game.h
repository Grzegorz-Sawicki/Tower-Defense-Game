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

	Grid* grid;

	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;

	unsigned level;
	unsigned lives;
	unsigned gold;
	unsigned score;

	//Functions
	void initWindow();
	void initBackground();
	void initVariables();
	void initGrid(int rowNum, int colNum, float tileSize);

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

