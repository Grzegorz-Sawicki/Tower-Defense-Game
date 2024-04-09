#pragma once

#include <SFML/Graphics.hpp>

struct Properties
{
	static int windowWidth;
	static int windowHeight;

	static int gridTopOffset;
	static int gridLeftOffset;

	static sf::Vector2f buttonPausePosition;
	static sf::Vector2f buttonResetPosition;
	static sf::Vector2f buttonLevelPosition;
	static sf::Vector2f buttonGridPosition;
	static sf::Vector2f buttonMutePosition;

	static int UIValueBoxHeight;
	static int UIButtonBoxWidth;
	static int UILevelBoxHeight;

	static sf::Color colorGridWall;
	static sf::Color colorGridTile;
	static sf::Color colorUIBox;

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
};




