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

void Game::initGrid()
{
	Grid::getInstance();
	Grid::createPaths();
	Grid::visualizePaths();
}

void Game::spawnEnemy()
{
	Path path = static_cast<Path>(rand() % 2);

	if (path == Path::HORIZONTAL) {
		int randSpawn = rand() % 6;
		Tile* spawnTile = Grid::getEntranceTiles()[Path::HORIZONTAL][randSpawn];
		sf::Vector2f spawnOffset = sf::Vector2f(-Properties::windowWidth / 10, 0);
		Enemy* tmp = new Enemy(spawnTile, spawnOffset, Path::HORIZONTAL);
		tmp->setPositionOffset(sf::Vector2f(0.f, -5 + rand() % 11));
		enemies.emplace_back(tmp);
	}
	else if (path == Path::VERTICAL) {
		int randSpawn = rand() % 8;
		Tile* spawnTile = Grid::getEntranceTiles()[Path::VERTICAL][randSpawn];
		sf::Vector2f spawnOffset = sf::Vector2f(0, -Properties::windowHeight / 10);
		Enemy* tmp = new Enemy(spawnTile, spawnOffset, Path::VERTICAL);
		tmp->setPositionOffset(sf::Vector2f(-5 + rand() % 11, 0.f));
		enemies.emplace_back(tmp);
	}

}


//Constructors and Destructors

Game::Game()
{
	this->initWindow();
	this->initBackground();
	this->initVariables();
	this->initGrid();
	this->canSpawn = false;
}

Game::~Game()
{
	delete this->window;

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
			if(this->canSpawn)
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
			Grid::handleMouseMove(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
			break;
		case sf::Event::MouseButtonPressed:
			if (Grid::canPlaceTower(sf::Mouse::getPosition(*this->window))) {
				this->towers.push_back(Grid::placeTower(sf::Mouse::getPosition(*this->window)));
				Grid::resetPaths();
				Grid::createPaths();
				Grid::visualizePaths();
			}
			break;
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Space) {
				this->canSpawn = true;
				system("pause");
			}
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

	Grid::draw(*this->window);

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