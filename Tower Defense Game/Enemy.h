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

	int hp;
	float moveSpeed;
	bool dead;
	Arrow currentArrow;
	sf::Vector2f direction;
	Tile* currentTile;
	bool reachedEntrance;

	//Functions
	void initSprite();
	void move();
	void moveCase(Tile* tile);


public:
	Enemy(Tile* tile, sf::Vector2f spawnOffset);
	virtual ~Enemy();

	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	int getHp();
	bool isDead();
	sf::Vector2f getDirection();
	Tile* getCurrentTile();
	bool didReachedEntrance();

	void setDirection(sf::Vector2f direction);
	void setCurrentTile(Tile* tile);

	//Functions
	void takeDamage(int damage);
	void die();

	void update();
	void render(sf::RenderTarget* target);
};

