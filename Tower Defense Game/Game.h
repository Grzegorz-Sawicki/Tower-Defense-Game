#pragma once

#include "include.h"
#include "Grid.h"
#include "Enemy.h"
#include "Tower.h"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "LevelManager.h"
#include "InfoWindowEnemy.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	LevelManager* levelManager;

	//UI STUFF

	sf::Sprite bgSprite;
	sf::Texture bgTexture;

	std::vector <sf::RectangleShape*> UIBoxes;
	sf::RectangleShape* UIValueBox;
	sf::RectangleShape* UIButtonBox;
	sf::RectangleShape* UILevelBox;


	std::vector <sf::Sprite*> buttons;
	sf::Sprite pauseButtonSprite;
	sf::Texture pauseButtonTexture;
	sf::Sprite resumeButtonSprite;
	sf::Texture resumeButtonTexture;

	sf::Sprite resetButtonSprite;
	sf::Texture resetButtonTexture;
	sf::Sprite levelButtonSprite;
	sf::Texture levelButtonTexture;
	sf::Sprite gridButtonSprite;
	sf::Texture gridButtonTexture;
	sf::Sprite muteButtonSprite;
	sf::Texture muteButtonTexture;

	InfoWindowEnemy infoWindowEnemy;
	bool showInfoWindow = false;

	std::map<TowerType, sf::Sprite*> towerButtons;
	std::map<TowerType, sf::Sprite*> towerBases;

	std::vector <sf::Text*> texts;
	sf::Font font;
	sf::Text* textTime;
	sf::Text* textLevel;
	sf::Text* textLives;
	sf::Text* textGold;
	sf::Text* textScore;

	//Pause screen
	sf::RectangleShape* UIPauseBox;
	sf::Text* textPause;

	sf::RectangleShape scrollBlockBox;

	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;

	unsigned timer;
	unsigned level;
	unsigned lives;
	unsigned gold;
	unsigned score;

	bool paused;
	bool placeMode;
	TowerType placingTower;

	//Functions
	void initWindow();
	void initSprites();
	void initFonts();
	void initUI();
	void initVariables();
	void initGrid();

	bool mouseOnSprite(sf::Sprite sprite);

	sf::Clock clock;


public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Functions
	void run();

	std::vector<Enemy*>& getEnemies();

	void updatePollEvents();
	void update();

	void render();
};

