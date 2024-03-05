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

	//Functions
	void initSprite();


public:
	Enemy();
	virtual ~Enemy();

	sf::Vector2f getPosition();
	int getHp();

	//Functions
	void takeDamage(int damage);

	void update();
	void render(sf::RenderTarget* target);
};

