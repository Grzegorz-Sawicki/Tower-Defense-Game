#pragma once
#include "include.h";
#include "Game.h";

class GameServer
{
private:
	Game& game;

	unsigned short port;
	sf::TcpListener* listener;
	sf::TcpSocket client;

	void handleClient();
	void remotePlaceTower(int col, int row, TowerType type);
	void remoteSellTower(int col, int row);

	void parsePlaceTowerMessage(std::string message, int& col, int& row, TowerType& type);
	void parseSellTowerMessage(std::string message, int& col, int& row);
	void parseUpgradeTowerMessage(std::string message, int& col, int& row);

	void sendMessage(std::string message);
public:
	GameServer(Game& game, unsigned short portNumber);
	void run();
	static void test();

	friend class Game;
};

