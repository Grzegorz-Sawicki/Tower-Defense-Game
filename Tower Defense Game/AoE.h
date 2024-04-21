#pragma once

#include "include.h"
#include "Enemy.h"
#include "utils.hpp"

class AoE
{
private:
	const std::vector<Enemy*>& enemies;
	json effects;

	sf::Vector2f position;
	float radius;
	int damage;

	bool isSlow = false;
	float slowValue = 0.f;
	float slowLength = 0.f;
	void slowEnemy();

	bool isStun=false;
	float stunChance=0.f;
	float stunLength=0.f;
	void stunEnemy();

public:
	AoE(const std::vector<Enemy*>& enemies, sf::Vector2f position, float radius, int damage, json effects);
	void move(sf::Vector2f offset);

	void launch();
};

