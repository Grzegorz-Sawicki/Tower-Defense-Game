#pragma once

#include "include.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TextureManager.hpp"

enum TowerState
{
	PASSIVE=0, ACTIVE, ELEM_COUNT
};

class Tower
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	sf::CircleShape radiusCircle;

	std::vector<Projectile*> projectiles;

	int posX;
	int posY;
	int range;
	int shootSpeed;

	sf::Time shootInterval;
	sf::Time shootTimer;
	sf::Clock clock;

	TowerState state;

	void initSprite();
	void shoot(Enemy* enemy);

public:
	Tower(int posX, int posY);
	virtual ~Tower();

	sf::FloatRect getBounds();

	//Functions

	void update(const std::vector<Enemy*>& enemies);
	void updateProjectiles();
	void render(sf::RenderTarget* target);
};

