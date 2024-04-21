#pragma once

#include "include.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TextureManager.hpp"
#include "utils.hpp"
#include "AoE.h"

class Tower
{
private:
	const std::vector<Enemy*>& enemies;

	void handleJsonData();
	json effects;
	json projectileData;

	sf::Sprite spriteBase;
	sf::Sprite spriteBarrel;
	sf::Texture texture;

	sf::CircleShape radiusCircle;

	std::vector<Projectile*> projectiles;
	TowerType type;

	int posX;
	int posY;

	int damage;
	int cost;
	int range;
	double shootSpeed;
	std::string speedStr;

	bool isAoe=false;
	float aoeRange;
	bool isSlow = false;
	float slowValue;
	float slowLength;
	bool isStun = false;
	float stunChance;
	float stunLength;
	bool isBash = false;
	int projectileCount=1;
	bool antiAir=false;

	Enemy* targetEnemy;
	bool targetEnemyDead;
	bool enemyDetected;

	sf::Time shootInterval;
	sf::Time shootTimer;
	sf::Clock clock;

	void initSprites(json texture);
	void initRadiusCircle();
	void shoot(Enemy* enemy);
	void rotateTowardsEnemy(Enemy* enemy);

public:
	Tower(const std::vector<Enemy*>& enemies, int posX, int posY, TowerType type);
	virtual ~Tower();

	sf::FloatRect getBounds();
	sf::Vector2f getPosition();
	const std::vector<Enemy*>& getEnemies();
	TowerType getType();

	//Functions

	void update();
	void updateProjectiles();
	void render(sf::RenderTarget* target);
	void renderProjectiles(sf::RenderTarget* target);
};
