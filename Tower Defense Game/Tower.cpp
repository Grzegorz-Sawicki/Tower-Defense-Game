#include "Tower.h"

void Tower::handleJsonData()
{
	json jsonData = utils::handleJson(Properties::jsonTowersFileName);
	json upgradeData = utils::handleJson(Properties::jsonUpgradesFileName);

	json towers = jsonData["towers"];

	json tower = towers[static_cast<int>(type)];
	this->name = tower["name"];
	this->damage = tower["damage"];
	this->cost = tower["cost"];
	this->range = tower["range"];
	this->shootSpeed = tower["shootSpeed"];
	this->speedStr = tower["speedStr"];
	this->description = tower["description"];

	this->projectileData = tower["projectileData"];
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
		///STUN HAPPENS IN TOWER, NOT IN PROJECTILE
		else if (effect["name"] == "stun") {
			this->isStun = true;
			this->stunChance = effect["chance"];
			this->stunLength = effect["length"];
		}
		else if (effect["name"] == "bash") {
			this->isBash = true;
		}
		else if (effect["name"] == "multi-shot") {
			this->projectileCount = effect["amount"];
		}
		else if (effect["name"] == "anti-air") {
			this->antiAir = true;
		}
	}

	json towerUpgrades = upgradeData["towerUpgrades"];
	json towerUpgrade = towerUpgrades[static_cast<int>(type)];
	json upgrades = towerUpgrade["upgrades"];

	for (json upgrade : upgrades) {
		this->towerUpgrades.emplace_back(TowerUpgrade(upgrade));
	}


	this->initSprites(tower["texture"]);
}

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

void Tower::initTexts()
{
	//upgrade text
	this->font = FontManager::instance().getFont("Fonts/PixellettersFull.ttf");
	this->upgradeText = sf::Text("0", this->font, 22);
	this->upgradeText.setFillColor(sf::Color::Black);

	sf::FloatRect textRect = upgradeText.getLocalBounds();
	upgradeText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	upgradeText.setPosition(this->spriteBase.getPosition());

	this->levelText = sf::Text(std::to_string(this->level), this->font, 15);
	this->levelText.setPosition(this->getPosition() + sf::Vector2f(8.f, -1.f));
	this->levelText.setFillColor(sf::Color::Black);
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
	projectiles.emplace_back(new Projectile(
		this->enemies, this->spriteBase.getPosition().x, this->spriteBase.getPosition().y, enemy, this->type, this->damage, this->effects, this->projectileData
	));
}

void Tower::rotateTowardsEnemy(Enemy* enemy)
{
	sf::Vector2f enemyPos = enemy->getPosition();
	sf::Vector2f towerPos = this->getPosition();

	float angle = utils::getRotation(towerPos, enemyPos);

	this->spriteBarrel.setRotation(angle);
}

sf::Time Tower::getNextUpgradeLength()
{
	return sf::seconds(Properties::towerUpgradeBaseTime + (this->level - 1) * Properties::towerUpgradeIncreaseTime);
}

Tower::Tower(const std::vector<Enemy*>& enemies, int posX, int posY, TowerType type) : enemies(enemies), posX(posX), posY(posY), type(type)
{
	this->handleJsonData();
	this->initTexts();
	this->initRadiusCircle();

	this->sellPrice = this->cost * 0.75;
	this->shootInterval = sf::seconds(1.f / shootSpeed);
	this->shootTimer = this->shootInterval;
	this->targetEnemy = nullptr;
	this->targetEnemyDead = false;
	this->enemyDetected = false;
}

Tower::Tower(const std::vector<Enemy*>& enemies, std::vector<Tile*> tiles, TowerType type) : enemies(enemies), type(type)
{
	this->tiles = tiles;

	Tile baseTile = *this->tiles[0];
	this->posX = baseTile.getPosition().x + baseTile.getOrigin().x;
	this->posY = baseTile.getPosition().y + baseTile.getOrigin().y;

	for (auto* tile : this->tiles) {
		tile->setType(TileType::TOWER);
	}

	this->handleJsonData();
	this->initTexts();
	this->initRadiusCircle();

	this->sellPrice = this->cost * 0.75;
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

void Tower::pauseClocks()
{
	this->clock.pause();
	this->upgradeClock.pause();
}

void Tower::resumeClocks()
{
	this->clock.resume();
	this->upgradeClock.resume();
}

const std::vector<Enemy*>& Tower::getEnemies()
{
	return this->enemies;
}

TowerType Tower::getType()
{
	return this->type;
}

sf::Sprite& Tower::getSpriteBase()
{
	return this->spriteBase;
}

sf::Sprite& Tower::getSpriteBarrel()
{
	return this->spriteBarrel;
}



std::string Tower::getName()
{
	return this->name;
}

int Tower::getLevel()
{
	return this->level;
}

int Tower::getCost()
{
	return this->cost;
}

int Tower::getDamage()
{
	return this->damage;
}

int Tower::getRange()
{
	return this->range;
}

std::string Tower::getSpeedStr()
{
	return this->speedStr;
}

int Tower::getSellPrice()
{
	return this->sellPrice;
}

std::string Tower::getDescription()
{
	return this->description;
}

void Tower::setShowRadiusCircle(bool show)
{
	this->showRadiusCircle = show;
}

std::vector<Tile*> Tower::getTiles()
{
	return this->tiles;
}

TowerUpgrade Tower::getNextUpgrade()
{
	return this->towerUpgrades[this->level - 1];
}

void Tower::upgrade(unsigned int& gold, bool instant)
{
	if (instant) this->upgradeTime = sf::seconds(0);
	else this->upgradeTime = this->getNextUpgradeLength();
	this->upgrading = true;
	this->upgradeClock.restart();

	TowerUpgrade upgrade = this->towerUpgrades[this->level - 1];
	this->level++;
	this->levelText.setString(std::to_string(this->level));
	this->cost += upgrade.cost;
	this->damage = upgrade.damage;
	this->range = upgrade.range;
	this->radiusCircle.setRadius(this->range);
	this->radiusCircle.setOrigin(this->range, this->range);
	this->speedStr = upgrade.speedStr;
	if (upgrade.shootSpeed != 0) {
		this->shootSpeed = upgrade.shootSpeed;
	}
	if (upgrade.stunChance != 0) {
		this->stunChance = upgrade.stunChance;
		for (json& effect : this->effects) {
			if (effect["name"] == "stun") {
				effect["chance"] = this->stunChance;
			}
		}
	}
	if (upgrade.slowValue != 0) {
		this->slowValue = upgrade.slowValue;
		for (json& effect : this->effects) {
			if (effect["name"] == "slow") {
				effect["value"] = this->slowValue;
			}
		}
	}
	if (upgrade.aoeRange != 0) {
		this->aoeRange = upgrade.aoeRange;
		//Tower wasn't originally AOE, but is due to an upgrade:
		if (this->isAoe == false) {
			this->isAoe = true;
			json newObject;
			newObject["name"] = "aoe";
			newObject["range"] = this->aoeRange;
			this->effects.push_back(newObject);
		}
		else {
			for (json& effect : this->effects) {
				if (effect["name"] == "aoe") {
					effect["range"] = this->aoeRange;
				}
			}
		}
	}

	this->sellPrice = this->cost * 0.75;

	gold -= upgrade.cost;
}

bool Tower::canUpgrade(unsigned int& gold)
{
	if (this->hasNextUpgrade()) {
		if (this->getNextUpgrade().cost <= gold) return true;
		else return false;
	}
	return false;
}

bool Tower::hasNextUpgrade()
{
	if (this->level < this->towerUpgrades.size() + 1) return true;
	return false;
}

void Tower::sell()
{
	for (auto* tile : this->tiles) {
		tile->setType(TileType::DEFAULT);
	}
}

void Tower::update()
{
	if (this->targetEnemy != nullptr && this->targetEnemy->isDead()) {
		this->targetEnemyDead = true;
	}

	if (!this->upgrading) {
		if (this->shootTimer >= this->shootInterval) {
			int targetedEnemiesCount = 0;
			std::vector<Enemy*> targetedEnemies;

			for (auto& enemy : this->enemies) {
				float distance = std::sqrt(std::pow(enemy->getPosition().x - this->getPosition().x, 2) + std::pow(enemy->getPosition().y - this->getPosition().y, 2));
				if (distance <= this->range) {
					if (this->antiAir && enemy->getType() == EnemyType::FLYING || !this->antiAir) {
						this->enemyDetected = true;
						this->targetEnemy = enemy;
						this->targetEnemyDead = false;

						targetedEnemies.emplace_back(enemy);
						targetedEnemiesCount++;

						this->shoot(enemy);
						this->shootTimer = sf::Time::Zero;

						if (this->enemyDetected && targetedEnemiesCount == this->projectileCount) break;
					}

				}
			}

		}

		if (this->targetEnemy != nullptr && !this->targetEnemyDead && !this->isBash && this->type != TowerType::SWARM)
			this->rotateTowardsEnemy(this->targetEnemy);
	}
	else {
		sf::Time remainingTime = this->upgradeTime - this->upgradeClock.getElapsedTime();
		int remainingTimeInt = static_cast<int>(remainingTime.asSeconds() + 1);
		this->upgradeText.setString(std::to_string(remainingTimeInt));
		if (this->upgradeClock.getElapsedTime() >= this->upgradeTime) {
			this->upgrading = false;
		}
	}

	this->updateProjectiles();

	//Increment shoot timer
	this->shootTimer += this->clock.getElapsedTime();
	this->clock.restart();
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

	if (this->upgrading) target->draw(this->upgradeText);
	else target->draw(this->spriteBarrel);

	target->draw(this->levelText);
}

void Tower::renderProjectiles(sf::RenderTarget* target)
{
	for (auto* projectile : this->projectiles)
	{
		projectile->render(target);
	}
}

void Tower::renderRadiusCircle(sf::RenderTarget* target)
{
	if (this->showRadiusCircle) target->draw(this->radiusCircle);
}

TowerUpgrade::TowerUpgrade()
{

}

TowerUpgrade::TowerUpgrade(json upgradeJson)
{
	this->cost = upgradeJson["cost"];
	this->damage = upgradeJson["damage"];
	this->description = upgradeJson["description"];
	this->level = upgradeJson["level"];
	this->speedStr = upgradeJson["speedStr"];
	this->range = upgradeJson["range"];

	if (!upgradeJson["aoeRange"].is_null()) this->aoeRange = upgradeJson["aoeRange"];
	if (!upgradeJson["slowValue"].is_null()) this->slowValue = upgradeJson["slowValue"];
	if (!upgradeJson["stunChance"].is_null()) this->stunChance = upgradeJson["stunChance"];
	if (!upgradeJson["shootSpeed"].is_null()) this->shootSpeed = upgradeJson["shootSpeed"];
}
