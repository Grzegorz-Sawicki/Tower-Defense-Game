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
sf::Time Properties::levelTimer = sf::seconds(10);

int Properties::enemyBarrierX = 580;
int Properties::enemyBarrierY = 540;

std::string Properties::textTime = "Time: ";
std::string Properties::textLevel = "Level: ";
std::string Properties::textLives = "Lives: ";
std::string Properties::textGold = "Gold: ";
std::string Properties::textScore = "Score: ";

std::string Properties::textPause = "Paused: ";
sf::Vector2f Properties::textPausePosition = sf::Vector2f(230.f, 260.f);

std::string	Properties::jsonTowersFileName = "Data/towers.json";