#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(Properties::windowWidth, Properties::windowHeight);
	this->window = new sf::RenderWindow(this->videoMode, "Tower Defense Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initBackground()
{
	this->bgTexture = TextureManager::instance().getTexture("Textures/background.png");
	this->bgSprite.setTexture(this->bgTexture);
}

void Game::initVariables()
{
	this->enemySpawnTimer = sf::seconds(1);
}

void Game::initGrid(int rowNum, int colNum, float tileSize)
{
	this->grid = new Grid(rowNum, colNum, tileSize);
}

void Game::spawnEnemy()
{
	int randSpawn = rand() % 6;
	float randSpawnOffset = -5 + rand() % 11;
	sf::Vector2f spawnPos = this->grid->getEntranceTiles()["HORIZONTAL"][randSpawn]->getPosition();
	spawnPos.y += randSpawnOffset;
	spawnPos.x -= this->window->getSize().x / 10;
	enemies.emplace_back(new Enemy(spawnPos));
}


//Constructors and Destructors

Game::Game()
{
	this->initWindow();
	this->initBackground();
	this->initVariables();
	this->initGrid(24, 28, 18.f);
}

Game::~Game()
{
	delete this->window;

	delete this->grid;

	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}

	for (auto* tower : this->towers)
	{
		delete tower;
	}
}

//Functions

void Game::run()
{
	sf::Clock clock;

	while (this->window->isOpen())
	{
		if (clock.getElapsedTime() >= enemySpawnTimer) {
			clock.restart();
			spawnEnemy();
		}

		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		switch (e.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::MouseMoved:
			this->grid->handleMouseMove(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
			break;
		case sf::Event::MouseButtonPressed:
			if(this->grid->canPlaceTower(sf::Mouse::getPosition(*this->window)))
				this->towers.push_back(this->grid->placeTower(sf::Mouse::getPosition(*this->window)));
			break;
		default:
			break;
		}

	}
}

void Game::update()
{
	this->updatePollEvents();

	for (auto* enemy : this->enemies)
	{
		enemy->update();
		if (enemy->isDead()) {
			//DOESN'T ALWAYS WORK, BEWARE
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
			delete enemy;
		}
	}

	for (auto* tower : this->towers)
	{
		tower->update(enemies);
	}
}

void Game::render()
{
	this->window->clear();

	this->window->draw(this->bgSprite);

	this->grid->draw(*this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* tower : this->towers)
	{
		tower->render(this->window);
	}

	this->window->display();
}