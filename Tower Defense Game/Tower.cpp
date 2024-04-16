#include "Tower.h"

void Tower::initSprites(json texture)
{
	//base
	this->spriteBase.setTexture(TextureManager::instance().getTexture("Textures/tower_base.png"));
	this->spriteBase.setPosition(this->posX, this->posY);
	this->spriteBase.setOrigin(this->spriteBase.getGlobalBounds().width / 2, this->spriteBase.getGlobalBounds().height / 2);

	//barrel
	this->spriteBarrel.setTexture(TextureManager::instance().getTexture(texture));
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
	projectiles.emplace_back(new Projectile(
		this->enemies, this->spriteBase.getPosition().x, this->spriteBase.getPosition().y, enemy, this->type, this->damage, this->projectileSpeed, this->effects
	));
}

void Tower::rotateTowardsEnemy(Enemy* enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f towerPos = this->getPosition();

	float angle = utils::getRotation(towerPos, enemyPos);

	this->spriteBarrel.setRotation(angle);
}

Tower::Tower(const std::vector<Enemy*>& enemies, int posX, int posY, TowerType type) : enemies(enemies), posX(posX), posY(posY), type(type)
{
	std::ifstream file(Properties::jsonTowersFileName);
	if (!file.is_open()) {
		std::cerr << "Failed to open JSON file." << std::endl;
		system("pause");
	}

	json jsonData;
	try {
		file >> jsonData;
	}
	catch (json::parse_error& e) {
		std::cerr << "Parse error: " << e.what() << std::endl;
		system("pause");
	}

	file.close();

	json towers = jsonData["towers"];

	json tower = towers[static_cast<int>(type)];
	this->damage = tower["damage"];
	this->cost = tower["cost"];
	this->range = tower["range"];
	this->shootSpeed = tower["shootSpeed"];
	this->speedStr = tower["speedStr"];
	this->projectileSpeed = tower["projectileSpeed"];

	this->effects = tower["effects"];

	//TOWER EFFECTS:
	/*
		slow - float time, power
		stun - float time
		aoe - float radius

		anti-air
		multi-shot - int count
	*/

	for (json effect : this->effects) {
		if (effect["name"] == "aoe") {
			this->isAoe = true;
			this->aoeRange = effect["range"];
		}
		 //give projectiles effects table in argument
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

	this->initSprites(tower["texture"]);


	//this->initSprites();

	//this->range = 100;
	this->initRadiusCircle();

	//this->shootSpeed = 1.f;
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

const std::vector<Enemy*>& Tower::getEnemies()
{
	return this->enemies;
}

TowerType Tower::getType()
{
	return this->type;
}

void Tower::update()
{
	if (this->targetEnemy != nullptr && this->targetEnemy->isDead()) {
		this->targetEnemyDead = true;
	}

	if (this->shootTimer >= this->shootInterval) {
		for (auto& enemy : this->enemies) {
			float distance = std::sqrt(std::pow(enemy->getPosition().x - this->getPosition().x, 2) + std::pow(enemy->getPosition().y - this->getPosition().y, 2));
			if (distance <= this->range) {
				this->enemyDetected = true;
				this->targetEnemy = enemy;
				this->targetEnemyDead = false;

				if (this->shootTimer >= this->shootInterval) {
					this->shoot(enemy);
					this->shootTimer = sf::Time::Zero;
				}
				if (this->enemyDetected) break;
			}
		}
	}

	if(this->targetEnemy != nullptr && !this->targetEnemyDead && !this->isBash)
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
}

void Tower::renderProjectiles(sf::RenderTarget* target)
{
	for (auto* projectile : this->projectiles)
	{
		projectile->render(target);
	}
}
