#pragma once

#include "include.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TextureManager.hpp"
#include "utils.hpp"

enum TowerState
{
	PASSIVE=0, ACTIVE, ELEM_COUNT
};

class Tower
{
private:
	sf::Sprite spriteBase;
	sf::Sprite spriteBarrel;
	sf::Texture texture;

	sf::CircleShape radiusCircle;

	std::vector<Projectile*> projectiles;

	int posX;
	int posY;
	int range;
	int shootSpeed;

	Enemy* targetEnemy;
	bool targetEnemyDead;
	bool enemyDetected;

	sf::Time shootInterval;
	sf::Time shootTimer;
	sf::Clock clock;

	TowerState state;

	void initSprites();
	void initRadiusCircle();
	void shoot(Enemy* enemy);
	void rotateTowardsEnemy(Enemy* enemy);

public:
	Tower(int posX, int posY);
	virtual ~Tower();

	sf::FloatRect getBounds();
	sf::Vector2f getPosition();

	//Functions

	void update(const std::vector<Enemy*>& enemies);
	void updateProjectiles();
	void render(sf::RenderTarget* target);
};

