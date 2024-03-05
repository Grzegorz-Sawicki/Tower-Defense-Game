#pragma once

#include "include.h"
#include "Enemy.h"

class Projectile
{
private:
    //sf::Sprite sprite;
    //sf::Texture texture;

    //temp
    sf::CircleShape shape;

    sf::Vector2f velocity;
    float speed;
    Enemy* targetEnemy;
    sf::Vector2f targetPos;
    int damage;

    bool destroyed;

    //Functions
    void initSprite();
public:
	Projectile(float startX, float startY, Enemy* targetEnemy);
	virtual ~Projectile();

    sf::Vector2f getPosition();
    Enemy* getTargetEnemy() const;
    bool isDestroyed();

    //Functions
    void update();
    void render(sf::RenderTarget* target);
};

