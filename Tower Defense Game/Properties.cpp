#include "Properties.h"

int Properties::windowWidth = 862;
int Properties::windowHeight = 612;

int Properties::gridTopOffset = 83;
int Properties::gridLeftOffset = 61;

sf::Vector2f Properties::towerSizeX = sf::Vector2f(36.f,0);

sf::Vector2f Properties::buttonPausePosition = sf::Vector2f(622.f, 4.f);
sf::Vector2f Properties::buttonResetPosition = sf::Vector2f(734.f, 4.f);
sf::Vector2f Properties::buttonLevelPosition = sf::Vector2f(622.f, 36.f);
sf::Vector2f Properties::buttonMutePosition = sf::Vector2f(734.f, 574.f);
sf::Vector2f Properties::buttonGridPosition = sf::Vector2f(622.f, 574.f);
sf::Vector2f Properties::buttonTowerPosition = sf::Vector2f(605.f, 83.f);
sf::Vector2f Properties::buttonTowerOffset = sf::Vector2f(7.f, 0.f);

int Properties::UIValueBoxHeight = 36;
int Properties::UIButtonBoxWidth = 264;
int Properties::UILevelBoxHeight = 60;

sf::Color Properties::colorGridWall = sf::Color(150, 150, 150, 100);
sf::Color Properties::colorGridTile = sf::Color(0, 0, 255, 100);
sf::Color Properties::colorUIBox = sf::Color(100, 100, 100, 100);
sf::Color Properties::colorEnemyHealthBar = sf::Color(0, 210, 27);
sf::Vector2f Properties::sizeEnemyHealthBar = sf::Vector2f(20.f, 4.f);

float Properties::tileSize = 18.f;
int Properties::gridTileNumHorizontal = 28;
int Properties::gridTileNumVertical = 24;
sf::Time Properties::enemySpawnTimer = sf::seconds(0.7);
sf::Time Properties::levelTimer = sf::seconds(25);

int Properties::enemyBarrierX = 580;
int Properties::enemyBarrierY = 540;

std::string Properties::textTime = "Time: ";
std::string Properties::textLevel = "Level: ";
std::string Properties::textLives = "Lives: ";
std::string Properties::textGold = "Gold: ";
std::string Properties::textScore = "Score: ";

std::string Properties::textPause = "Paused: ";
sf::Vector2f Properties::textPausePosition = sf::Vector2f(230.f, 260.f);
sf::Vector2f Properties::textEndGameScorePosition = sf::Vector2f(230.f, 300.f);

std::string	Properties::jsonTowersFileName = "Data/towers.json";
std::string Properties::jsonUpgradesFileName = "Data/tower_upgrades.json";
std::string	Properties::jsonEnemiesFileName = "Data/enemies.json";
std::string	Properties::jsonLevelsEasyFileName = "Data/levels_easy.json";

//INFO BOXES
sf::Vector2f Properties::mainInfoBoxPosition = sf::Vector2f(630.f, 140.f);
sf::Vector2f Properties::mainInfoBoxSize = sf::Vector2f(210.f, 200.f);
sf::Color Properties::mainInfoBoxBgColor = sf::Color(180.f, 180.f, 180.f);
sf::Vector2f Properties::subInfoBoxPosition = sf::Vector2f(652.f, 200.f);
sf::Vector2f Properties::subInfoBoxSize = sf::Vector2f(150.f, 108.f);
sf::Color Properties::subInfoBoxBgColor = sf::Color(236, 129, 57);
sf::Vector2f Properties::upgradeInfoBoxPosition = sf::Vector2f(630.f, 354.f);

sf::Color Properties::gray = sf::Color(200,200,200);
sf::Color Properties::darkGray = sf::Color(100, 100, 100);
sf::Color Properties::orange = sf::Color(255,127,0);
sf::Vector2f Properties::levelScrollBoxSize = sf::Vector2f(75.f, 40.f);
sf::Vector2f Properties::levelScrollBoxPosition = sf::Vector2f(Properties::gridLeftOffset, 564.f);

sf::Color Properties::levelScrollNormalColor = sf::Color(34,34,34);
sf::Color Properties::levelScrollGroupColor = sf::Color(0,85,170);
sf::Color Properties::levelScrollImmuneColor = sf::Color(170,0,170);
sf::Color Properties::levelScrollFastColor = sf::Color(170,0,0);
sf::Color Properties::levelScrollSpawnColor = sf::Color(0,85,0);
sf::Color Properties::levelScrollFlyingColor = sf::Color(170,170,0);

float Properties::towerUpgradeBaseTime = 1.5;
float Properties::towerUpgradeIncreaseTime = 3;