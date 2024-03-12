#pragma once

#include "include.h"
#include "TextureManager.hpp"

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	int hp;
	int moveSpeed;
	bool dead;

	//Functions
	void initSprite();


public:
	Enemy();
	Enemy(sf::Vector2f position);
	virtual ~Enemy();

	sf::Vector2f getPosition();
	sf::FloatRect getBounds();
	int getHp();
	bool isDead();

	//Functions
	void takeDamage(int damage);
	void die();

	void update();
	void render(sf::RenderTarget* target);
};

