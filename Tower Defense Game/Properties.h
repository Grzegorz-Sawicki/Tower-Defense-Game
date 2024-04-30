#pragma once

#include <SFML/Graphics.hpp>

struct Properties
{
	static int windowWidth;
	static int windowHeight;

	static int gridTopOffset;
	static int gridLeftOffset;

	static sf::Vector2f towerSizeX;

	static sf::Vector2f buttonPausePosition;
	static sf::Vector2f buttonResetPosition;
	static sf::Vector2f buttonLevelPosition;
	static sf::Vector2f buttonGridPosition;
	static sf::Vector2f buttonMutePosition;
	static sf::Vector2f buttonTowerPosition;
	static sf::Vector2f buttonTowerOffset;

	static int UIValueBoxHeight;
	static int UIButtonBoxWidth;
	static int UILevelBoxHeight;

	static sf::Color colorGridWall;
	static sf::Color colorGridTile;
	static sf::Color colorUIBox;
	static sf::Color colorEnemyHealthBar;
	static sf::Vector2f sizeEnemyHealthBar;

	static float tileSize;
	static int gridTileNumHorizontal;
	static int gridTileNumVertical;
	static sf::Time enemySpawnTimer;
	static sf::Time levelTimer;

	static int enemyBarrierX;
	static int enemyBarrierY;

	static std::string textTime;
	static std::string textLevel;
	static std::string textLives;
	static std::string textGold;
	static std::string textScore;

	static std::string textPause;
	static sf::Vector2f textPausePosition;

	static std::string jsonTowersFileName;
	static std::string jsonUpgradesFileName;
	static std::string jsonEnemiesFileName;
	static std::string jsonLevelsEasyFileName;

	//INFO BOXES
	static sf::Vector2f mainInfoBoxPosition;
	static sf::Vector2f mainInfoBoxSize;
	static sf::Color mainInfoBoxBgColor;
	static sf::Vector2f subInfoBoxPosition;
	static sf::Vector2f subInfoBoxSize;
	static sf::Color subInfoBoxBgColor;
	static sf::Vector2f upgradeInfoBoxPosition;

	static sf::Color gray;
	static sf::Color darkGray;
	static sf::Color orange;
	static sf::Vector2f levelScrollBoxSize;
	static sf::Vector2f levelScrollBoxPosition;

	static sf::Color levelScrollNormalColor;
	static sf::Color levelScrollGroupColor;
	static sf::Color levelScrollImmuneColor;
	static sf::Color levelScrollFastColor;
	static sf::Color levelScrollSpawnColor;
	static sf::Color levelScrollFlyingColor;

	static float towerUpgradeBaseTime;
	static float towerUpgradeIncreaseTime;
};




