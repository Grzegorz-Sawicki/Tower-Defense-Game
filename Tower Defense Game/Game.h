#pragma once

#include "include.h"
#include "Grid.h"
#include "Enemy.h"
#include "Tower.h"
#include "TextureManager.hpp"
#include "LevelManager.h"

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

	//

	std::vector<Enemy*> enemies;
	std::vector<Tower*> towers;

	unsigned timer;
	unsigned level;
	unsigned lives;
	unsigned gold;
	unsigned score;

	bool paused;

	//Functions
	void initWindow();
	void initSprites();
	void initFonts();
	void initUI();
	void initVariables();
	void initGrid();

	sf::Clock clock;


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

