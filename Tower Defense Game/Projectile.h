#pragma once

#include "include.h"
#include "Enemy.h"
#include "AoE.h"

class Projectile
{
private:
    //sf::Sprite sprite;
    //sf::Texture texture;

    const std::vector<Enemy*>& enemies;
    json effects;

    //temp
    sf::CircleShape sprite;

    TowerType type;
    sf::Vector2f velocity;
    float speed;
    int damage;

    AoE* aoe;
    bool isAoe=false;
    float aoeRange=0.f;
    bool isSlow=false;
    float slowValue=0.f;
    float slowLength=0.f;
    bool isStun;
    float stunChance;
    float stunLength;
    bool isBash;

    Enemy* targetEnemy;
    bool enemyDead;
    sf::Vector2f targetPos;

    void pulseAoE();
    void slowEnemy();
    void stunEnemy();


    bool destroyed;

    //Functions
    void initSprite();
public:
	Projectile(const std::vector<Enemy*>& enemies, float startX, float startY, Enemy* targetEnemy, TowerType type, int damage, float speed, json effects);
	virtual ~Projectile();

    const sf::Vector2f getPosition();
    Enemy* getTargetEnemy() const;
    bool isDestroyed();

    //Functions
    void update();
    void render(sf::RenderTarget* target);
};

