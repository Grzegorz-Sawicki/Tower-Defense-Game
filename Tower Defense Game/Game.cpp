#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
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
	this->enemySpawnTimer = sf::seconds(3);
}

void Game::initGrid(int rowNum, int colNum, float tileSize)
{
	this->grid = new Grid(rowNum, colNum, tileSize);
}

void Game::spawnEnemy()
{
	enemies.emplace_back(new Enemy());
}


//Constructors and Destructors

Game::Game()
{
	this->initWindow();
	this->initBackground();
	this->initVariables();
	this->initGrid(26, 28, 18.f);

	this->enemies.push_back(new Enemy());
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