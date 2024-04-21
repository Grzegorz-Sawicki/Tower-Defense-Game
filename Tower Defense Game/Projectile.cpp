#include "Projectile.h"

void Projectile::pulseAoE()
{
	this->aoe->launch();
}

void Projectile::slowEnemy()
{
	this->targetEnemy->setSlow(this->slowValue, this->slowLength);
}

void Projectile::stunEnemy()
{
	float randomValue = static_cast<float>(rand()) / RAND_MAX;
	if (randomValue <= this->stunChance) {
		this->targetEnemy->setStun(this->stunLength);
	}
}

void Projectile::initSprite(json texture)
{
	this->sprite.setTexture(TextureManager::instance().getTexture(texture));
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
}

Projectile::Projectile(const std::vector<Enemy*>& enemies, float startX, float startY, Enemy* targetEnemy, TowerType type, int damage, json effects, json projectileData)
	: type(type), damage(damage), enemies(enemies), effects(effects), projectileData(projectileData)
{
	this->initSprite(this->projectileData["texture"]);
	this->sprite.setPosition(startX, startY);

	this->speed = this->projectileData["speed"];
	this->moveType = this->projectileData["moveType"];
	this->rotate = this->projectileData["rotate"];

	for (json effect : this->effects) {
		if (effect["name"] == "aoe") {
			this->isAoe = true;
			this->aoeRange = effect["range"];
			this->aoe = new AoE(enemies, this->getPosition(), this->aoeRange, this->damage, effects);
			this->damage = 0;
		}
		// give projectiles effects table in argument
		else if (effect["name"] == "slow") {
			this->isSlow = true;
			this->slowValue = effect["value"];
			this->slowLength = effect["length"];
		}
		else if (effect["name"] == "stun") {
			this->isStun = true;
			this->stunChance = effect["chance"];
			this->stunLength = effect["length"];
		}
		else if (effect["name"] == "bash") {
			this->isBash = true;
		}
	}

	this->destroyed = false;
	this->targetEnemy = targetEnemy;
	this->enemyDead = false;
	this->targetPos = this->targetEnemy->getPosition();
}

Projectile::~Projectile()
{

}

const sf::Vector2f Projectile::getPosition()
{
	return this->sprite.getPosition();
}

Enemy* Projectile::getTargetEnemy() const
{
	return this->targetEnemy;
}

bool Projectile::isDestroyed()
{
	return this->destroyed;
}

void Projectile::update()
{
	if (this->rotate) this->sprite.rotate(10);
	if (this->isBash) {
		this->pulseAoE();
		this->destroyed = true;
		return;
	}

	if (this->targetEnemy->isDead()) {
		this->enemyDead = true;
	}

	if (!this->enemyDead) {
		this->targetPos = this->targetEnemy->getPosition();
	}

	float dx = targetPos.x - this->getPosition().x;
	float dy = targetPos.y - this->getPosition().y;
	float length = std::sqrt(dx * dx + dy * dy);

	this->velocity = sf::Vector2f(dx / length * speed, dy / length * speed);
	this->sprite.move(velocity);
	if (this->isAoe) this->aoe->move(velocity);

	//temp
	if (length <= 1)
	{
		this->destroyed = true;
		this->targetEnemy->takeDamage(this->damage);
		if (this->isAoe) this->pulseAoE();
		if (this->isSlow && !this->isAoe) this->slowEnemy();
		if (this->isStun && !this->isAoe) this->stunEnemy();
		//std::cout << "Enemy " << this->targetEnemy << " takes " << damage << " damage. It now has " << this->targetEnemy->getHp() << " health!\n";
	}

}

void Projectile::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
