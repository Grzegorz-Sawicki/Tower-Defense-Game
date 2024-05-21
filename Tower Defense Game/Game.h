#pragma once

#include "include.h"
#include "Grid.h"
#include "Enemy.h"
#include "Tower.h"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "LevelManager.h"
#include "InfoWindowEnemy.h"
#include "InfoWindowTower.h"
#include "GameServer.h"

class Game
{
	friend class GameServer;
private:
	GameServer* gameServer;

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
	sf::Sprite startButtonSprite;
	sf::Texture startButtonTexture;

	sf::Sprite resetButtonSprite;
	sf::Texture resetButtonTexture;
	sf::Sprite levelButtonSprite;
	sf::Texture levelButtonTexture;
	sf::Sprite gridButtonSprite;
	sf::Texture gridButtonTexture;
	sf::Sprite muteButtonSprite;
	sf::Texture muteButtonTexture;

	InfoWindowEnemy* infoWindowEnemy;
	InfoWindowTower* infoWindowTower;
	InfoWindowTower* infoWindowUpgrade;
	bool showInfoWindow = false;
	bool showInfoTowerSell = false;
	bool showInfoTower = false;
	bool showInfoUpgrade = false;
	bool showInfoEnemy = false;
	Tower* selectedTower;

	std::map<TowerType, Tower*> dummyTowers;
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

	//GameOver screen
	sf::Text* textGameOver;

	sf::RectangleShape scrollBlockBox;

	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;

	unsigned timer;
	unsigned level;
	unsigned lives;
	unsigned gold;
	unsigned score=0;
	unsigned scoreSkip=0;

	bool gameOver = false;
	bool started = false;
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

	float timeScale = 1.0;
	void setTimeScale(float scale);

	bool mouseOnSprite(sf::Sprite sprite);
	bool mouseOnShape(sf::RectangleShape shape);

	bool shouldReset=false;
	void reset();
	void start();
	void endGame();
	void pause();
	void unpause();
	void skip();
	bool speedUp();
	bool speedDown();

	Tower* getTowerByTile(Tile& tile);
	void sellTower();
	void printEnemies();
	void sortEnemies();

	sf::Clock clock;
	std::atomic<bool>* isRunning;
	bool placeTower(int col, int row, TowerType type);
	bool sellTower(int col, int row);
	bool upgradeTower(int col, int row);

public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	void gameLoop();

	//Functions
	void run();

	std::vector<Enemy*>& getEnemies();

	void updatePollEvents();
	void update();

	void render();
};

