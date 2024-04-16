#pragma once

#include "include.h"
#include "TextureManager.hpp"
#include "Tile.h"
#include "utils.hpp"

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f positionOffset;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarRed;

	int hp;
	int maxhp;
	float moveSpeed;
	float moveSpeedBase;
	bool dead;
	Path path;
	EnemyType type;
	Arrow currentArrow;
	sf::Vector2f direction;
	Tile* currentTile;
	bool reachedEntrance;

	bool slowed=false;
	float slowValue=0.f;
	sf::Time slowLength;
	sf::Clock slowClock;

	bool stunned = false;
	sf::Time stunLength;
	sf::Clock stunClock;


	//Functions
	void initSprite();
	void initHealthBar();
	void move(sf::Vector2f offset);
	void moveCase();
	Tile* chooseSpawnTile(std::map<Path, std::vector<Tile*>> entranceTiles);
	sf::Vector2f createSpawnOffset();
	sf::Vector2f createPositionOffset();
	sf::Vector2f createSpawnDirection();


public:
	Enemy(Tile* tile, sf::Vector2f spawnOffset, Path path);
	Enemy(std::map<Path, std::vector<Tile*>> entranceTiles, Path path, EnemyType type, int hp);
	virtual ~Enemy();

	sf::Vector2f getPosition(bool ignoreOffset=false);
	sf::Vector2f getPositionOffset();
	sf::FloatRect getBounds();
	int getHp();
	bool isDead();
	sf::Vector2f getDirection();
	EnemyType getType();
	Tile* getCurrentTile();
	bool didReachedEntrance();

	void setSlow(float value, float length);
	void setStun(float length);

	void setPositionOffset(sf::Vector2f offset);
	void setDirection(sf::Vector2f direction);
	void setCurrentTile(Tile* tile);

	//Functions
	void takeDamage(int damage);
	void die();

	void updateHealthBar();

	void update();
	void render(sf::RenderTarget* target);
};

