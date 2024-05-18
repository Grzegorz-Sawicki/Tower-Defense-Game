#include "GameServer.h"

void GameServer::handleClient(sf::TcpSocket& client)
{
	while (true) {
		sf::Packet packet;
		if (client.receive(packet) != sf::Socket::Done) {
			std::cerr << "Error receiving message from client" << std::endl;
			break;
		}

		std::string command;
		packet >> command;
		std::cout << "Received command: " << command << std::endl;

		if (command == "hello") {
			std::string response = helloWorld();
			sf::Packet responsePacket;
			responsePacket << response;
			client.send(responsePacket);
		}
		else if (command.find("placeTower") != std::string::npos) {
			int col = 0;
			int row = 0;
			TowerType type;

			this->parsePlaceTowerMessage(command, col, row, type);

			this->remotePlaceTower(col, row, type);
			std::string response = "placed";
			sf::Packet responsePacket;
			responsePacket << response;
			client.send(responsePacket);
		}
		else if (command == "getAvailableTiles") {
			std::string response = Grid::getAvailableTilesString();
			sf::Packet responsePacket;
			responsePacket << response;
			client.send(responsePacket);
		}
		// Add more commands and corresponding functions here

	}
}

std::string GameServer::helloWorld()
{
	return std::string();
}

void GameServer::remotePlaceTower(int col, int row, TowerType type)
{
	game.remotePlaceTower(col, row, type);
}

void GameServer::parsePlaceTowerMessage(std::string message, int& col, int& row, TowerType& type)
{
	std::stringstream ss(message);
	std::string action;
	std::string typeString;
	ss >> action;

	if (!(ss >> col >> row)) {
		std::cerr << "Error reading integers" << std::endl;
		return;
	}

	ss >> typeString;
	type = utils::stringToTowerType(typeString);
}

GameServer::GameServer(Game& game, unsigned short portNumber) : game(game), port(portNumber), listener(new sf::TcpListener)
{

}

void GameServer::run()
{
	std::thread gameThread(&Game::gameLoop, &game);

	if (listener->listen(port) != sf::Socket::Done) {
		std::cerr << "Failed to bind to port " << port << std::endl;
		return;
	}

	std::cout << "Server is listening on port " << port << std::endl;

	while (*game.isRunning) {
		sf::TcpSocket client;
		if (listener->accept(client) == sf::Socket::Done) {
			std::cout << "New connection from " << client.getRemoteAddress() << std::endl;
			handleClient(client);
		}

	}

	gameThread.join();

}
