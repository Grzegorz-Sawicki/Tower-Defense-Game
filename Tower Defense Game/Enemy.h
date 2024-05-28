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

	json effects;
	void handleJsonData();

	bool dead=false;

	int hp;
	int maxhp;
	float moveSpeed;
	float moveSpeedBase;
	int level = 0;
	int gold = 0;

	bool boss;
	bool group=false;
	bool flying=false;
	bool spawn=false;
	bool immune=false;
	EnemyType type;

	bool slowed = false;
	float slowValue = 0.f;
	sf::Time slowLength;
	PausableClock slowClock;

	bool stunned = false;
	sf::Time stunLength;
	PausableClock stunClock;

	Path path;
	Tile* currentTile;
	Arrow currentArrow;
	sf::Vector2f direction;
	bool reachedEntrance = false;
	int distanceFromExit;

	//Functions
	void initSprite(json texture);
	void initHealthBar();
	void move(sf::Vector2f offset);
	void moveCase();
	Tile* chooseSpawnTile(std::map<Path, std::vector<Tile*>> entranceTiles);
	sf::Vector2f createSpawnOffset();
	sf::Vector2f createPositionOffset();
	sf::Vector2f createSpawnDirection();

	void unDie();

public:
	Enemy(std::map<Path, std::vector<Tile*>> entranceTiles, Path path, EnemyType type, int hp, bool boss, int gold, int level);
	Enemy(const Enemy& other, sf::Vector2f offset);

	sf::Vector2f getPosition(bool ignoreOffset=false);
	sf::Vector2f getPositionOffset();
	sf::FloatRect getBounds();

	bool getFlying();
	bool getImmune();
	float getSpeedBase();

	int getLevel();
	int getGold();
	int getHp();
	int getMaxHp();
	bool isDead();
	bool isBoss();
	sf::Vector2f getDirection();
	EnemyType getType();
	Tile* getCurrentTile();
	bool didReachedEntrance();
	sf::Sprite getSprite();
	int getDistanceFromExit();

	void setSlow(float value, float length);
	void setStun(float length);

	void setPositionOffset(sf::Vector2f offset);
	void setDirection(sf::Vector2f direction);
	void setCurrentTile(Tile* tile);
	void updateDistanceFromExit();

	void setDead(bool dead);
	void setMaxHp(int maxHp);
	void setHp(int hp);
	void setPosition(sf::Vector2f position);

	//Functions
	void takeDamage(int damage);
	void die();

	void updateHealthBar();

	void update();
	void render(sf::RenderTarget* target);
};

