#pragma once
#include "include.h";
#include "Game.h";

class GameServer
{
private:
	Game& game;

	unsigned short port;
	sf::TcpListener* listener;
	void handleClient(sf::TcpSocket& client);
	std::string helloWorld();
	void remotePlaceTower(int col, int row, TowerType type);
	void parsePlaceTowerMessage(std::string message, int& col, int& row, TowerType& type);
public:
	GameServer(Game& game, unsigned short portNumber);
	void run();

};

