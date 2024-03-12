#include "Tower.h"

void Tower::initSprites()
{
	//base
	this->spriteBase.setTexture(TextureManager::instance().getTexture("Textures/tower_basic_base.png"));
	this->spriteBase.setPosition(this->posX, this->posY);
	this->spriteBase.setOrigin(this->spriteBase.getGlobalBounds().width / 2, this->spriteBase.getGlobalBounds().height / 2);

	//barrel
	this->spriteBarrel.setTexture(TextureManager::instance().getTexture("Textures/tower_basic_barrel.png"));
	this->spriteBarrel.setPosition(this->posX, this->posY);
	this->spriteBarrel.setOrigin(this->spriteBarrel.getGlobalBounds().width / 2, this->spriteBarrel.getGlobalBounds().height / 2);
}

void Tower::initRadiusCircle()
{
	this->radiusCircle.setFillColor(sf::Color::Transparent);
	this->radiusCircle.setOutlineColor(sf::Color::Red);
	this->radiusCircle.setOutlineThickness(1);
	this->radiusCircle.setRadius(this->range);
	this->radiusCircle.setOrigin(this->range, this->range);
	this->radiusCircle.setPosition(posX, posY);
}

void Tower::shoot(Enemy* enemy)
{
	std::cout << "Tower shoots at enemy!" << std::endl;
	projectiles.emplace_back(new Projectile(this->spriteBase.getPosition().x, this->spriteBase.getPosition().y, enemy));
}

void Tower::rotateTowardsEnemy(Enemy* enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f towerPos = this->getPosition();

	float angle = utils::getRotation(towerPos, enemyPos);

	this->spriteBarrel.setRotation(angle);
}

Tower::Tower(int posX, int posY) : posX(posX), posY(posY)
{
	this->state = PASSIVE;
	this->initSprites();

	this->range = 100;
	this->initRadiusCircle();

	this->shootSpeed = 1.f;
	this->shootInterval = sf::seconds(1.f / shootSpeed);
	this->shootTimer = this->shootInterval;
	this->targetEnemy = nullptr;
	this->targetEnemyDead = false;
	this->enemyDetected = false;
}

Tower::~Tower()
{

}

sf::FloatRect Tower::getBounds()
{
	return this->spriteBase.getGlobalBounds();
}

sf::Vector2f Tower::getPosition()
{
	return this->spriteBase.getPosition();
}

void Tower::update(const std::vector<Enemy*>& enemies)
{
	if (this->targetEnemy != nullptr && this->targetEnemy->isDead()) {
		this->targetEnemyDead = true;
	}

	if (this->shootTimer >= this->shootInterval) {
		for (auto& enemy : enemies) {
			float distance = std::sqrt(std::pow(enemy->getPosition().x - this->getPosition().x, 2) + std::pow(enemy->getPosition().y - this->getPosition().y, 2));
			if (distance <= this->range) {
				this->enemyDetected = true;
				this->targetEnemy = enemy;
				this->targetEnemyDead = false;

				if (this->shootTimer >= this->shootInterval) {
					shoot(enemy);
					this->shootTimer = sf::Time::Zero;
				}
				if (this->enemyDetected) break;
			}
		}
	}

	if(this->targetEnemy != nullptr && !this->targetEnemyDead)
		this->rotateTowardsEnemy(this->targetEnemy);

	this->updateProjectiles();

	//Increment shoot timer
	this->shootTimer += this->clock.restart();
}

void Tower::updateProjectiles()
{
	for (auto* projectile : this->projectiles)
	{
		projectile->update();

		if (projectile->isDestroyed()) {
			projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
			delete projectile;
		}
			
	}
}

void Tower::render(sf::RenderTarget* target)
{
	target->draw(this->spriteBase);
	target->draw(this->spriteBarrel);
	target->draw(this->radiusCircle);

	for (auto* projectile : this->projectiles)
	{
		projectile->render(target);
	}
}
