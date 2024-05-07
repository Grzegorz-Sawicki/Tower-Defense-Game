#pragma once

#include "include.h"
#include "Enemy.h"
#include "Projectile.h"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "utils.hpp"
#include "AoE.h"
#include "Tile.h"
#include "PausableClock.h"

class TowerUpgrade 
{
private:
	int level=0;
	std::string description="";
	int cost=0;
	int damage=0;
	int range=0;
	double shootSpeed=0;
	std::string speedStr = "";
	float stunChance=0;
	float slowValue=0;
	float aoeRange=0;
public:
	TowerUpgrade();
	TowerUpgrade(json upgradeJson);

	friend class Tower;
	friend class InfoWindowTower;
	friend class Game;
};

class Tower
{
private:
	const std::vector<Enemy*>& enemies;
	std::vector<Tile*> tiles;

	void handleJsonData();
	json effects;
	json projectileData;

	std::vector<TowerUpgrade> towerUpgrades;

	sf::Sprite spriteBase;
	sf::Sprite spriteBarrel;
	sf::Texture texture;

	sf::CircleShape radiusCircle;
	bool showRadiusCircle = false;
	std::vector<Projectile*> projectiles;
	TowerType type;

	int posX;
	int posY;

	int level=1;
	std::string name;
	int cost;
	int damage;
	int range;
	double shootSpeed;
	std::string speedStr;
	std::string description;
	int sellPrice;

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
	PausableClock clock;

	sf::Font font;
	bool upgrading = false;
	PausableClock upgradeClock;
	sf::Time upgradeTime;
	sf::Text upgradeText;

	void initSprites(json texture);
	void initText();
	void initRadiusCircle();
	void shoot(Enemy* enemy);
	void rotateTowardsEnemy(Enemy* enemy);
	sf::Time getNextUpgradeLength();

public:
	Tower(const std::vector<Enemy*>& enemies, int posX, int posY, TowerType type);
	Tower(const std::vector<Enemy*>& enemies, std::vector<Tile*> tiles, TowerType type);
	virtual ~Tower();

	sf::FloatRect getBounds();
	sf::Vector2f getPosition();
	const std::vector<Enemy*>& getEnemies();
	TowerType getType();

	sf::Sprite& getSpriteBase();
	sf::Sprite& getSpriteBarrel();

	std::string getName();
	int getLevel();
	int getCost();
	int getDamage();
	int getRange();
	std::string getSpeedStr();
	int getSellPrice();
	std::string getDescription();

	void setShowRadiusCircle(bool show);

	//Functions
	TowerUpgrade getNextUpgrade();
	void upgrade(unsigned int& gold);
	bool canUpgrade(unsigned int& gold);
	bool hasNextUpgrade();

	void sell();

	void update();
	void updateProjectiles();
	void render(sf::RenderTarget* target);
	void renderProjectiles(sf::RenderTarget* target);
};
