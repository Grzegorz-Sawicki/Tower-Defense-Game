#include "GameServer.h"

void GameServer::handleClient()
{
	while (true) {
		sf::Packet packet;
		if (client.receive(packet) != sf::Socket::Done) {
			std::cerr << "Error receiving message from client" << std::endl;
			break;
		}

		std::string command;
		if (!(packet >> command)) { //packet >> command works on SFML client
			//For python client
			command = "";
			const void* data = packet.getData();
			std::size_t size = packet.getDataSize();
			std::cout << "Raw data received (size " << size << "): ";

			for (std::size_t i = 0; i < size; ++i) {
				std::cout << static_cast<const char*>(data)[i];
				command += static_cast<const char*>(data)[i];
			}
			std::cout << std::endl;
		}

		std::cout << "Received command: " << command << std::endl;

		if (command.find("placeTower") != std::string::npos) {
			int col = 0;
			int row = 0;
			TowerType type;

			this->parsePlaceTowerMessage(command, col, row, type);

			std::string response;

			if (game.placeTower(col, row, type)) {
				response = "tower placed";
			}
			else response = "tower not placed";
			sendMessage(response);
		}
		else if (command.find("sellTower") != std::string::npos) {
			int col = 0;
			int row = 0;

			this->parseSellTowerMessage(command, col, row);

			std::string response;
			if (game.sellTower(col, row)) {
				response = "tower sold";
			}
			else response = "tower not sold";
			
			sendMessage(response);
		}
		else if (command.find("upgradeTower") != std::string::npos) {
			int col = 0;
			int row = 0;

			this->parseUpgradeTowerMessage(command, col, row);

			std::string response;

			if (game.upgradeTower(col, row)) {
				response = "tower upgraded";
			}
			else response = "tower not upgraded";
			sendMessage(response);
		}
		else if (command == "pause") {
			std::string response;
			if (game.paused) response = "Game already paused";
			else {
				response = "Game paused!";
				game.pause();
			}
			sendMessage(response);
		}
		else if (command == "resume" || command == "unpause") {
			std::string response;
			if (!game.paused) response = "Game already unpaused";
			else {
				response = "Game unpaused!";
				game.unpause();
			}
			sendMessage(response);
		}
		else if (command == "start") {
			std::string response;
			if (game.started) response = "Game already started";
			else {
				response = "Game started!";
				game.start();
			}
			sendMessage(response);
		}
		else if (command == "reset" || command == "restart") {
			game.shouldReset = true;
			std::string response = "game reset";
			sendMessage(response);
		}
		else if (command == "skip" || command == "next" || command == "nextLevel") {

			std::string response;
			if (game.skip()) {
				response = "level skipped";
			}
			else response = "level not skipped";
			sendMessage(response);
		}
		else if (command == "speedUp") {
			std::string response;
			if (game.speedUp()) {
				response = "game sped up";
			}
			else {
				response = "can't speed up, game is started";
			}
			sendMessage(response);
		}
		else if (command == "speedDown") {
			std::string response;
			if (game.speedDown()) {
				response = "game slowed down";
			}
			else {
				response = "can't slow down, game is started";
			}
			sendMessage(response);
		}
		else if (command == "getAvailableTiles") {
			std::string response = game.getAvailableTilesString();
			sendMessage(response);
		}
		else if (command == "getPlacedTowers") {
			std::string response = game.getPlacedTowersString();
			sendMessage(response);
		}
		else if (command == "getInfo") {
			std::string response = game.getInfoString();
			sendMessage(response);
		}
		else if (command == "getEnemies") {
			std::string response = game.getEnemiesString();
			sendMessage(response);
		}

	}
}

//placeTower col row type
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

//sellTower col row
void GameServer::parseSellTowerMessage(std::string message, int& col, int& row)
{
	std::stringstream ss(message);
	std::string action;
	ss >> action;

	if (!(ss >> col >> row)) {
		std::cerr << "Error reading integers" << std::endl;
		return;
	}
}

//upgradeTower col row
void GameServer::parseUpgradeTowerMessage(std::string message, int& col, int& row) {
	std::stringstream ss(message);
	std::string action;
	ss >> action;

	if (!(ss >> col >> row)) {
		std::cerr << "Error reading integers" << std::endl;
		return;
	}
}

void GameServer::sendMessage(std::string message)
{
	sf::Packet responsePacket;
	responsePacket << message;
	client.send(responsePacket);
}

GameServer::GameServer(Game& game, unsigned short portNumber) : game(game), port(portNumber), listener(new sf::TcpListener)
{
	game.gameServer = this;
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
		if (listener->accept(client) == sf::Socket::Done) {
			std::cout << "New connection from " << client.getRemoteAddress() << std::endl;
			std::thread clientThread(&GameServer::handleClient, this);
			clientThread.join();
		}

	}

	gameThread.join();

}
