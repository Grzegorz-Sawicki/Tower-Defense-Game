#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(Properties::windowWidth, Properties::windowHeight);
	this->window = new sf::RenderWindow(this->videoMode, "Tower Defense Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initSprites()
{
	this->bgTexture = TextureManager::instance().getTexture("Textures/background.png");
	this->bgSprite.setTexture(this->bgTexture);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "COULD NOT LOAD PixelLettersFull.ttf" << "\n";
	}
}

void Game::initUI()
{
	this->UIValueBox = new sf::RectangleShape();
	this->UIButtonBox = new sf::RectangleShape();
	this->UILevelBox = new sf::RectangleShape();

	this->UIBoxes.emplace_back(UIValueBox);
	this->UIBoxes.emplace_back(UIButtonBox);
	this->UIBoxes.emplace_back(UILevelBox);

	this->buttons.emplace_back(&pauseButtonSprite);
	this->buttons.emplace_back(&resumeButtonSprite);
	this->buttons.emplace_back(&resetButtonSprite);
	this->buttons.emplace_back(&levelButtonSprite);
	this->buttons.emplace_back(&gridButtonSprite);
	this->buttons.emplace_back(&muteButtonSprite);

	this->pauseButtonTexture = TextureManager::instance().getTexture("Textures/button_pause.png");
	this->pauseButtonSprite.setTexture(this->pauseButtonTexture);
	this->pauseButtonSprite.setPosition(Properties::buttonPausePosition);

	this->resumeButtonTexture = TextureManager::instance().getTexture("Textures/button_resume.png");
	this->resumeButtonSprite.setTexture(this->resumeButtonTexture);
	this->resumeButtonSprite.setPosition(Properties::buttonPausePosition);

	this->resetButtonTexture = TextureManager::instance().getTexture("Textures/button_reset.png");
	this->resetButtonSprite.setTexture(this->resetButtonTexture);
	this->resetButtonSprite.setPosition(Properties::buttonResetPosition);

	this->levelButtonTexture = TextureManager::instance().getTexture("Textures/button_level.png");
	this->levelButtonSprite.setTexture(this->levelButtonTexture);
	this->levelButtonSprite.setPosition(Properties::buttonLevelPosition);

	this->gridButtonTexture = TextureManager::instance().getTexture("Textures/button_grid.png");
	this->gridButtonSprite.setTexture(this->gridButtonTexture);
	this->gridButtonSprite.setPosition(Properties::buttonGridPosition);

	this->muteButtonTexture = TextureManager::instance().getTexture("Textures/button_mute.png");
	this->muteButtonSprite.setTexture(this->muteButtonTexture);
	this->muteButtonSprite.setPosition(Properties::buttonMutePosition);


	for (auto* box : this->UIBoxes) {
		box->setFillColor(Properties::colorUIBox);
	}

	this->UIValueBox->setSize(sf::Vector2f(Properties::windowWidth, Properties::UIValueBoxHeight));
	this->UIValueBox->setPosition(0, 0);

	this->UIButtonBox->setSize(sf::Vector2f(Properties::UIButtonBoxWidth, Properties::windowHeight));
	this->UIButtonBox->setPosition(sf::Vector2f(Properties::windowWidth - Properties::UIButtonBoxWidth, 0));

	this->UILevelBox->setSize(sf::Vector2f(Properties::windowWidth, Properties::UILevelBoxHeight));
	this->UILevelBox->setPosition(sf::Vector2f(0, Properties::windowHeight - Properties::UILevelBoxHeight));

	this->textTime = new sf::Text(Properties::textTime + "0", this->font);
	this->textLevel = new sf::Text(Properties::textLevel + "0", this->font);
	this->textLives = new sf::Text(Properties::textLives + "0", this->font);
	this->textGold = new sf::Text(Properties::textGold + "0", this->font);
	this->textScore = new sf::Text(Properties::textScore + "0", this->font);

	this->texts.emplace_back(textTime);
	this->texts.emplace_back(textLevel);
	this->texts.emplace_back(textLives);
	this->texts.emplace_back(textGold);
	this->texts.emplace_back(textScore);

	for (auto* text : this->texts) {
		text->setCharacterSize(25);
	}

	this->textTime->setPosition(17.f, -4.f);
	this->textLevel->setPosition(125.f, -4.f);
	this->textLives->setPosition(239.f, -4.f);
	this->textGold->setPosition(335.f, -4.f);
	this->textScore->setPosition(441.f, -4.f);

	this->textTime->setFillColor(sf::Color::White);
	this->textLevel->setFillColor(sf::Color::Blue);
	this->textLives->setFillColor(sf::Color::Green);
	this->textGold->setFillColor(sf::Color::Yellow);
	this->textScore->setFillColor(sf::Color::Red);

	this->UIPauseBox = new sf::RectangleShape(sf::Vector2f(Properties::windowWidth, Properties::windowHeight));
	this->UIPauseBox->setFillColor(Properties::colorUIBox);
	this->textPause = new sf::Text(Properties::textPause, this->font, 50);
	this->textPause->setFillColor(sf::Color(255, 127, 39));
	this->textPause->setPosition(Properties::textPausePosition);
};

void Game::initVariables()
{
	this->paused = false;
	this->lives = 30;
}

void Game::initGrid()
{
	Grid::getInstance();
	Grid::createPaths();
	Grid::visualizePaths();
}

//Constructors and Destructors

Game::Game()
{
	this->initWindow();
	this->initSprites();
	this->initVariables();
	this->initFonts();
	this->initUI();
	this->initGrid();
	this->levelManager = new LevelManager(this->enemies);
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

	for (auto* box : this->UIBoxes)
	{
		delete box;
	}

	for (auto* text : this->texts)
	{
		delete text;
	}
}

//Functions

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (!this->paused) {
			switch (e.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::MouseMoved:
				Grid::handleMouseMove(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
				//!!! HAS TO WORK WHEN PAUSED TOO, ALSO ON CLICK EVENT AS WELL
				for (auto* button : this->buttons) {
					if (button->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)))) {
						SetCursor(LoadCursor(NULL, IDC_HAND));
						break;
					}
					SetCursor(LoadCursor(NULL, IDC_ARROW));
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (Grid::canPlaceTower(sf::Mouse::getPosition(*this->window))) {
					this->towers.push_back(Grid::placeTower(sf::Mouse::getPosition(*this->window)));
					Grid::resetPaths();
					Grid::createPaths();
					Grid::visualizePaths();
				}
				if (this->pauseButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)))) {
					this->paused = true;
					this->levelManager->pause();
				}
				if (this->levelButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))) && this->levelManager->canSpawnEnemies()) {
					this->levelManager->nextLevel();
				}
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Space) {
					this->levelManager->setSpawn(true);
				}
				if (e.key.code == sf::Keyboard::S && this->levelManager->canSpawnEnemies()) {
					this->levelManager->nextLevel();
				}
				if (e.key.code == sf::Keyboard::P) {
					this->paused = true;
					this->levelManager->pause();
					//system("pause");
				}
			default:
				break;
			}
		}
		else {
			switch (e.type) {
			case sf::Event::MouseButtonPressed:
				if (this->resumeButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)))) {
					this->paused = false;
					this->levelManager->resume();
				}
				break;
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::P) {
					this->paused = false;
					this->levelManager->resume();
				}
			default:
				break;
			}
		}

	}
}

void Game::update()
{
	this->updatePollEvents();
	if (!this->paused) {
		this->levelManager->update();

		this->timer = this->levelManager->getRemainingTime().asSeconds();
		this->textTime->setString(Properties::textTime + std::to_string(this->timer));

		this->level = this->levelManager->getLevel();
		this->textLevel->setString(Properties::textLevel + std::to_string(this->level));

		for (auto* enemy : this->enemies)
		{
			enemy->update();
			if (enemy->isDead()) {
				this->score++;
				this->gold++;
				//DOESN'T ALWAYS WORK, BEWARE
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());

				//THINK OF BETTER WAY
				//delete enemy;
				continue;
			}
			if (enemy->getPosition().x > Properties::enemyBarrierX || enemy->getPosition().y > Properties::enemyBarrierY) {
				this->lives--;
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
				//delete enemy;
			}
		}

		this->textGold->setString(Properties::textGold + std::to_string(this->gold));
		this->textScore->setString(Properties::textScore + std::to_string(this->score));
		this->textLives->setString(Properties::textLives + std::to_string(this->lives));

		for (auto* tower : this->towers)
		{
			tower->update(enemies);
		}
	}
}

void Game::render()
{
	this->window->clear();

	this->window->draw(this->bgSprite);

	for (auto* box : this->UIBoxes) {
		this->window->draw(*box);
		//std::cout << static_cast<int>(box.getFillColor().r) << std::endl;
	}

	for (auto* text : this->texts) {
		this->window->draw(*text);
	}

	Grid::draw(*this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* tower : this->towers)
	{
		tower->render(this->window);
	}

	if (this->paused) {
		this->window->draw(*this->UIPauseBox);
		this->window->draw(*this->textPause);
		this->window->draw(this->resumeButtonSprite);
	}
	else this->window->draw(this->pauseButtonSprite);

	this->window->draw(this->resetButtonSprite);
	this->window->draw(this->levelButtonSprite);
	this->window->draw(this->gridButtonSprite);
	this->window->draw(this->muteButtonSprite);

	this->window->display();
}