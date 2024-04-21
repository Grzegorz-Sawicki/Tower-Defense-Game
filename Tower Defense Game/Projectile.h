#pragma once

#include "include.h"
#include "Enemy.h"
#include "AoE.h"

class Projectile
{
private:
    sf::Sprite sprite;

    const std::vector<Enemy*>& enemies;
    json effects;
    json projectileData;

    TowerType type;
    sf::Vector2f velocity;
    float speed;
    int damage;
    int moveType;
    bool rotate;

    AoE* aoe;
    bool isAoe=false;
    float aoeRange=0.f;
    bool isSlow=false;
    float slowValue=0.f;
    float slowLength=0.f;
    bool isStun=false;
    float stunChance;
    float stunLength;
    bool isBash=false;

    Enemy* targetEnemy;
    bool enemyDead;
    sf::Vector2f targetPos;

    void pulseAoE();
    void slowEnemy();
    void stunEnemy();


    bool destroyed;

    //Functions
    void initSprite(json texture);
public:
	Projectile(const std::vector<Enemy*>& enemies, float startX, float startY, Enemy* targetEnemy, TowerType type, int damage, json effects, json projectileData);
	virtual ~Projectile();

    const sf::Vector2f getPosition();
    Enemy* getTargetEnemy() const;
    bool isDestroyed();

    //Functions
    void update();
    void render(sf::RenderTarget* target);
};

