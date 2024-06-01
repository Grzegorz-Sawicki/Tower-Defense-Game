#include "AoE.h"

AoE::AoE(const std::vector<Enemy*>& enemies, sf::Vector2f position, float radius, int damage, json effects) :
	enemies(enemies), position(position), radius(radius), damage(damage), effects(effects)
{
	for (json effect : this->effects) {
		if (effect["name"] == "slow") {
			this->isSlow = true;
			this->slowValue = effect["value"];
			this->slowLength = effect["length"];
		}
		else if (effect["name"] == "stun") {
			this->isStun = true;
			this->stunChance = effect["chance"];
			this->stunLength = effect["length"];
		}
	}
}

void AoE::move(sf::Vector2f offset)
{
	this->position = this->position + offset;
}

void AoE::launch()
{
	float randomValue = static_cast<float>(rand()) / RAND_MAX;

	for (auto* enemy : enemies) {
		if (utils::getDistance(this->position, enemy->getPosition()) <= this->radius) {
			if (isSlow) {
				enemy->setSlow(this->slowValue, this->slowLength);
			}
			if (isStun) {
				if (randomValue <= this->stunChance) {
					enemy->setStun(this->stunLength);
				}
			}
			enemy->takeDamage(this->damage);
		}
	}
}
