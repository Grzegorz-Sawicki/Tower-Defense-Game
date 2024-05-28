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
	this->font = FontManager::instance().getFont("Fonts/PixellettersFull.ttf");
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
	this->buttons.emplace_back(&startButtonSprite);
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

	this->startButtonTexture = TextureManager::instance().getTexture("Textures/button_start.png");
	this->startButtonSprite.setTexture(this->startButtonTexture);
	this->startButtonSprite.setPosition(Properties::buttonPausePosition);

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

	for (int i = 0; i < static_cast<int>(TowerType::ELEM_COUNT); i++) {
		TowerType type = static_cast<TowerType>(i);

		Tower* dummyTower = new Tower(enemies, 0, 0, type);

		sf::Sprite* tmpTower = &dummyTower->getSpriteBarrel();
		tmpTower->setOrigin(sf::Vector2f(0, 0));
		sf::Sprite* tmpBase = &dummyTower->getSpriteBase();
		tmpBase->setOrigin(sf::Vector2f(0, 0));

		this->buttons.emplace_back(tmpTower);

		dummyTowers[type] = dummyTower;
		towerButtons[type] = tmpTower;
		towerBases[type] = tmpBase;
		towerButtons[type]->setPosition(Properties::buttonTowerPosition + static_cast<float>(i) * (Properties::towerSizeX + Properties::buttonTowerOffset));
		towerBases[type]->setPosition(Properties::buttonTowerPosition + static_cast<float>(i) * (Properties::towerSizeX + Properties::buttonTowerOffset));
	}


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

	this->textGameOver = new sf::Text("GAME OVER", this->font, 50);
	this->textGameOver->setFillColor(sf::Color::Red);
	this->textGameOver->setPosition(Properties::textPausePosition);
	
	this->textGameOverScore.setFont(this->font);
	this->textGameOverScore.setCharacterSize(50);
	this->textGameOverScore.setFillColor(sf::Color::Red);
	this->textGameOverScore.setPosition(Properties::textEndGameScorePosition);

	this->scrollBlockBox.setFillColor(Properties::darkGray);
	this->scrollBlockBox.setPosition(Properties::windowWidth - Properties::UIButtonBoxWidth, Properties::windowHeight - Properties::UILevelBoxHeight);
	this->scrollBlockBox.setSize(sf::Vector2f(
		Properties::windowWidth - this->scrollBlockBox.getPosition().x,
		Properties::windowHeight - this->scrollBlockBox.getPosition().y)
	);

};

void Game::initVariables()
{
	this->gameOver = false;
	this->started = false;
	this->paused = false;
	this->lives = 20;
	this->gold = 80;
	this->score = 0;
	this->scoreSkip = 0;
}

void Game::initGrid()
{
	Grid::getInstance(this->enemiesSorted);
	Grid::createPaths();
	Grid::visualizePaths();
}

void Game::doGameOver()
{
	this->gameServer->sendMessage("GAME OVER. SCORE = " + std::to_string(this->score) + "+" + std::to_string(this->scoreSkip));
	this->gameOver = true;
	this->paused = true;
}

bool Game::mouseOnSprite(sf::Sprite sprite)
{
	return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)));
}

bool Game::mouseOnShape(sf::RectangleShape shape)
{
	return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)));
}

void Game::reset()
{
	this->initVariables();

	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
	this->enemies.clear();
	this->enemiesSorted.clear();

	for (auto* tower : towers)
	{
		delete tower;
	}
	this->towers.clear();

	delete this->levelManager;
	this->levelManager = new LevelManager(this->enemies);
	Grid::resetTiles();

}

void Game::start()
{
	this->started = true;
	this->levelManager->setSpawn(true);
}

void Game::setTimeScale(float scale)
{
	this->timeScale = scale;
	this->timeScale = this->timeScale;
	PausableClock::globalTimeScale = this->timeScale;
	this->window->setFramerateLimit(60 * this->timeScale);
}

void Game::sellTower()
{
	int sellValue = this->selectedTower->getSellPrice();
	this->selectedTower->sell();
	towers.erase(std::remove(towers.begin(), towers.end(), this->selectedTower), towers.end());
	delete this->selectedTower;
	this->gold += sellValue;
	Grid::resetPaths();
	Grid::createPaths();
}

void Game::printEnemies() {
	for (const auto& enemy : enemiesSorted) {
		std::cout << ";" << enemy->getDistanceFromExit() << " " << enemy->getLevel() << " " << utils::enemyTypeToString(enemy->getType()) << ";";
	}
	std::cout << std::endl;
}

void Game::sortEnemies() {
	this->enemiesSorted = enemies;

	std::sort(enemiesSorted.begin(), enemiesSorted.end(), [](Enemy* a, Enemy* b) {
		return a->getDistanceFromExit() < b->getDistanceFromExit();
		});
}

void Game::endGame()
{
	this->window->close();
	this->isRunning->store(false);
	this->gameServer->client.disconnect();
	this->gameServer->listener->close();
}

void Game::pause() {
	this->paused = true;
	this->levelManager->pause();
	for (auto* tower : this->towers) {
		tower->pauseClocks();
	}
}

void Game::unpause() {
	this->paused = false;
	this->levelManager->resume();
	for (auto* tower : this->towers) {
		tower->resumeClocks();
	}
}

bool Game::skip() {
	if (this->levelManager->nextLevel()) {
		this->scoreSkip += this->timer * 2;
		return true;
	}
	return false;
}

bool Game::speedUp() {
	if (!this->started && this->timeScale <= 10.0) {
		this->setTimeScale(this->timeScale + 1.0);
		return true;
	}
	return false;
}

bool Game::speedDown() {
	if (!this->started && this->timeScale >= 2.0) {
		this->setTimeScale(this->timeScale - 1.0);
		return true;
	}
	return false;
}

//Constructors and Destructors

Game::Game() : isRunning(new std::atomic<bool>(true))
{

}

Game::~Game()
{
	delete this->window;

	for (auto* enemy : this->enemies)
	{
		enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	}

	for (auto* tower : this->towers)
	{
		towers.erase(std::remove(towers.begin(), towers.end(), tower), towers.end());
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

void Game::gameLoop() {
	this->initWindow();
	this->initSprites();
	this->initVariables();
	this->initFonts();
	this->initUI();
	this->initGrid();
	this->setTimeScale(1.0);
	this->levelManager = new LevelManager(this->enemies);

	this->placeMode = false;
	this->paused = false;

	while (window->isOpen()) {
		this->update();
		this->render();
	}
}

bool Game::isGameWon()
{
	bool cond1 = this->levelManager->getLevel() == this->levelManager->getMaxLevel();
	bool cond2 = this->enemies.size() <= 1;
	bool cond3 = this->levelManager->getLevelObject()->getEnemyCount() == 0;
	return cond1 && cond2 && cond3;
}

std::string Game::getAvailableTilesString()
{
	return Grid::getAvailableTilesString();
}

std::string Game::getPlacedTowersString()
{
	std::string output = ";";

	for (auto* tower : this->towers) {
		Tile* mainTile = tower->getTiles()[0];
		int col = mainTile->getCol();
		int row = mainTile->getRow();
		std::string typeStr = utils::towerToString(tower->getType());
		int level = tower->getLevel();

		output += std::to_string(col) + " "
			+ std::to_string(row) + " "
			+ typeStr + " "
			+ std::to_string(level) + ";";
	}

	return output;
}

std::string Game::getInfoString()
{
	std::string timeString = std::to_string(this->timer);
	std::string levelString = std::to_string(this->level);
	std::string livesString = std::to_string(this->lives);
	std::string goldString = std::to_string(this->gold);
	std::string scoreString = std::to_string(this->score) + "+" + std::to_string(this->scoreSkip);

	std::string output = timeString + " " + levelString + " " + livesString + " " + goldString + " " + scoreString;

	return output;

}

std::string Game::getEnemiesString()
{
	std::string output = ";";

	for (auto* enemy : this->enemiesSorted) {
		Tile* tile = enemy->getCurrentTile();

		int distFromExit = enemy->getDistanceFromExit();
		int col = tile->getCol();
		int row = tile->getRow();
		std::string typeStr = utils::enemyTypeToString(enemy->getType());
		int level = enemy->getLevel();
		int health = enemy->getHp();

		output += std::to_string(distFromExit) + " "
			+ std::to_string(col) + " "
			+ std::to_string(row) + " "
			+ typeStr + " "
			+ std::to_string(level) + " "
			+ std::to_string(health) + ";";
	}

	return output;
}

bool Game::placeTower(int col, int row, TowerType type)
{
	unsigned int cost = this->dummyTowers[type]->getCost();
	if (Grid::canPlaceTower(col, row) && cost <= this->gold && !this->paused) {
		this->gold -= cost;
		Tower* t = Grid::getInstance(this->enemiesSorted).placeTower(col, row, type);
		this->towers.push_back(t);
		Grid::resetPaths();
		Grid::createPaths();
		Grid::visualizePaths();
		return true;
	}
	return false;
}

Tower* Game::getTowerByTile(Tile& tile) {
	for (auto* tower : this->towers)
	{
		for (auto* towerTile : tower->getTiles()) {
			if (towerTile == &tile) return tower;
		}
	}
	return nullptr;
}

bool Game::sellTower(int col, int row)
{
	Tile& tile = Grid::getInstance(this->enemiesSorted).getTile(col, row);
	Tower* tower = this->getTowerByTile(tile);

	if (tower != nullptr && !this->paused) {
		int sellValue = tower->getSellPrice();
		tower->sell();
		towers.erase(std::remove(towers.begin(), towers.end(), tower), towers.end());
		delete tower;
		this->gold += sellValue;
		Grid::resetPaths();
		Grid::createPaths();
		return true;
	}
	else return false;
}

bool Game::upgradeTower(int col, int row) {
	Tile& tile = Grid::getInstance(this->enemiesSorted).getTile(col, row);
	Tower* tower = this->getTowerByTile(tile);

	if (tower != nullptr && !this->paused) {
		if (tower->canUpgrade(this->gold)) {
			bool instant = false;
			if (!this->started) instant = true;
			tower->upgrade(this->gold, instant);
			return true;
		}
	}
	return false;
}

std::vector<Enemy*>& Game::getEnemies()
{
	return this->enemies;
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (!this->paused) {
			switch (e.type) {
			case sf::Event::Closed:
				this->endGame();
				break;
			case sf::Event::MouseMoved:
				if (this->placeMode) {
					Grid::handleMouseMove(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
				}
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
				if (e.mouseButton.button == sf::Mouse::Left) {
					//TOWER BUTTON SELECTION
					for (int i = 0; i < static_cast<int>(TowerType::ELEM_COUNT); i++) {
						TowerType type = static_cast<TowerType>(i);

						if (mouseOnSprite(*towerButtons[type])) {
							this->placingTower = type;
							this->placeMode = true;
						}
					}

					//TOWER SELLING
					if (this->showInfoTowerSell) {
						if (mouseOnShape(this->infoWindowTower->getSellButtonShape())) {
							this->sellTower();
						}
					}

					//TOWER UPGRADING
					if (this->showInfoUpgrade) {
						if (mouseOnShape(this->infoWindowUpgrade->getUpgradeButtonShape())) {
							if (this->selectedTower->canUpgrade(this->gold)) {
								bool instant = false;
								if (!this->started) instant = true;
								this->selectedTower->upgrade(this->gold, instant);
							}
						}
					}

					//TOWER SELECT FOR INFO
					for (const auto& pair : this->dummyTowers) {
						TowerType key = pair.first;
						Tower* tower = pair.second;

						if (mouseOnSprite(tower->getSpriteBase())) {
							delete this->infoWindowTower;
							if (this->infoWindowUpgrade != nullptr) {
								delete this->infoWindowUpgrade;
								this->infoWindowUpgrade = nullptr;
							}
							this->infoWindowTower = new InfoWindowTower(*tower, 0);
							this->showInfoWindow = true;
							this->showInfoTower = true;
							break;
						}
						this->showInfoTower = false;
						this->showInfoTowerSell = false;
						this->showInfoUpgrade = false;
					}
					if (!this->showInfoTower) {
						//RESET RADIUS CIRCLES
						for (auto* tower : this->towers)
						{
							tower->setShowRadiusCircle(false);
						}

						for (auto* tower : this->towers)
						{
							if (mouseOnSprite(tower->getSpriteBase())) {
								this->selectedTower = tower;

								delete this->infoWindowTower;
								if (this->infoWindowUpgrade != nullptr) {
									delete this->infoWindowUpgrade;
									this->infoWindowUpgrade = nullptr;
								}
								this->infoWindowTower = new InfoWindowTower(*tower, 0);

								if (tower->hasNextUpgrade()) {
									this->infoWindowUpgrade = new InfoWindowTower(*tower, 1);
									this->infoWindowUpgrade->setPosition(Properties::upgradeInfoBoxPosition);
									this->showInfoUpgrade = true;
								}

								this->showInfoWindow = true;
								this->showInfoTowerSell = true;
								this->showInfoTower = true;
								this->selectedTower->setShowRadiusCircle(true);
								break;
							}
							this->showInfoTower = false;
							this->showInfoTowerSell = false;
							this->showInfoUpgrade = false;
							tower->setShowRadiusCircle(false);
						}
					}



					//TOWER PLACING
					if (this->placeMode) {
						const sf::Vector2i& mousePos = sf::Mouse::getPosition(*this->window);
						int col = Grid::mousePosToCol(mousePos);
						int row = Grid::mousePosToRow(mousePos);
						if (this->placeTower(col, row, placingTower)) this->placeMode = false;
					}

					//ENEMY SELECT
					if (this->enemies.size() == 0) this->showInfoEnemy = false;
					else {
						for (auto* enemy : this->enemies)
						{
							if (mouseOnSprite(enemy->getSprite())) {
								delete this->infoWindowEnemy;
								this->infoWindowEnemy = new InfoWindowEnemy(*enemy);
								this->showInfoWindow = true;
								this->showInfoEnemy = true;
								break;
							}
							this->showInfoEnemy = false;
						}
					}

					//BUTTONS 
					if (!this->started && mouseOnSprite(startButtonSprite)) {
						this->start();
						break;
					}
					if (mouseOnSprite(pauseButtonSprite)) {
						this->pause();
						break;
					}
					if (mouseOnSprite(levelButtonSprite) && this->levelManager->canSpawnEnemies()) {
						this->skip();
						break;
					}
					if (mouseOnSprite(resetButtonSprite)) {
						this->shouldReset = true;
						break;
					}
				}
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::Escape) {
					this->showInfoWindow = false;
					this->showInfoTower = false;
					this->showInfoTowerSell = false;
					this->showInfoUpgrade = false;
					this->showInfoEnemy = false;
					this->placeMode = false;
					Grid::handleMouseMove(sf::Vector2f(e.mouseMove.x, e.mouseMove.y));
				}
				if (e.key.code == sf::Keyboard::Space) {
					this->start();
				}
				if (e.key.code == sf::Keyboard::S && this->levelManager->canSpawnEnemies()) {
					this->skip();
				}
				if (e.key.code == sf::Keyboard::P) {
					this->pause();
					//system("pause");
				}
				if (e.key.code == sf::Keyboard::Num1) {
					this->placeMode = true;
					this->placingTower = static_cast<TowerType>(0);
				}
				if (e.key.code == sf::Keyboard::Num2) {
					this->placeMode = true;
					this->placingTower = static_cast<TowerType>(1);
				}
				if (e.key.code == sf::Keyboard::Num3) {
					this->placeMode = true;
					this->placingTower = static_cast<TowerType>(2);
				}
				if (e.key.code == sf::Keyboard::Num4) {
					this->placeMode = true;
					this->placingTower = static_cast<TowerType>(3);
				}
				if (e.key.code == sf::Keyboard::Num5) {
					this->placeMode = true;
					this->placingTower = static_cast<TowerType>(4);
				}
				if (e.key.code == sf::Keyboard::Num6) {
					this->placeMode = true;
					this->placingTower = static_cast<TowerType>(5);
				}
				if (e.key.code == sf::Keyboard::G) {
					//this->gold += 10;
				}
				if (e.key.code == sf::Keyboard::Equal) {
					this->speedUp();
				}
				else if (e.key.code == sf::Keyboard::Hyphen) {
					this->speedDown();
				}
				if (e.key.code == sf::Keyboard::N) {
					//this->printEnemies();
				}

			default:
				break;
			}
		}
		else if (!this->gameOver) {
			switch (e.type) {
			case sf::Event::MouseButtonPressed:
				if (mouseOnSprite(resumeButtonSprite)) {
					this->unpause();
				}
				break;
			case sf::Event::Closed:
				this->endGame();
				break;
			case sf::Event::KeyPressed:
				if (e.key.code == sf::Keyboard::P) {
					this->unpause();
				}
				break;
			default:
				break;
			}
		}
		else {
			switch (e.type) {
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Left) {
					if (mouseOnSprite(resetButtonSprite)) {
						this->shouldReset = true;
						break;
					}
				}
				break;
			case sf::Event::Closed:
				this->endGame();
				break;
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
		this->sortEnemies();

		this->timer = this->levelManager->getRemainingTime().asSeconds();
		this->textTime->setString(Properties::textTime + std::to_string(this->timer));

		this->level = this->levelManager->getLevel();
		this->textLevel->setString(Properties::textLevel + std::to_string(this->level));

		std::vector<Enemy*> deadSpawns;

		for (auto* enemy : this->enemies)
		{
			enemy->update();
			if (enemy->isDead()) {
				this->score += enemy->getGold();
				this->gold += enemy->getGold();

				if (enemy->getType() == EnemyType::SPAWN) {
					deadSpawns.emplace_back(enemy);
				}

				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());

				continue;
			}
			if (enemy->getPosition().x > Properties::enemyBarrierX || enemy->getPosition().y > Properties::enemyBarrierY) {
				this->lives--;
				gameServer->sendMessage("Lives: " + std::to_string(this->lives));
				if (this->lives <= 0 || this->isGameWon()) {
					this->doGameOver();
					break;
				}
				enemy->getCurrentTile()->occupyDec();
				enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
				enemy->die();
				delete enemy;
			}
		}

		for (auto* ds : deadSpawns)
		{
			Enemy* tmp = new Enemy(*ds, sf::Vector2f(0, 2));
			enemies.emplace_back(tmp);
			Enemy* tmp2 = new Enemy(*ds, sf::Vector2f(0, -2));
			enemies.emplace_back(tmp2);
		}

		this->textGold->setString(Properties::textGold + std::to_string(this->gold));
		this->textScore->setString(Properties::textScore + std::to_string(this->score) + "+" + std::to_string(this->scoreSkip));
		this->textLives->setString(Properties::textLives + std::to_string(this->lives));

		for (auto* tower : this->towers)
		{
			tower->update();
		}
	}
	if (shouldReset) {
		this->reset();
		shouldReset = false;
	}
}

void Game::render()
{
	this->window->clear();

	this->window->draw(this->bgSprite);

	for (auto* box : this->UIBoxes) {
		this->window->draw(*box);
	}

	for (auto* text : this->texts) {
		this->window->draw(*text);
	}

	Grid::draw(*this->window);

	for (auto* tower : this->towers)
	{
		tower->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* tower : this->towers)
	{
		tower->renderRadiusCircle(this->window);
	}

	for (auto* tower : this->towers)
	{
		tower->renderProjectiles(this->window);
	}


	//PAUSE/RESUME BUTTONS
	if (this->paused) {
		this->window->draw(*this->UIPauseBox);
		if (this->gameOver) {
			this->window->draw(*this->textGameOver);
			this->textGameOverScore.setString("Score = " + std::to_string(this->score) + "+" + std::to_string(this->scoreSkip));
			this->window->draw(textGameOverScore);
		}
		else {
			this->window->draw(*this->textPause);
			this->window->draw(this->resumeButtonSprite);
		}

	}
	else if (!this->started) this->window->draw(this->startButtonSprite);
	else this->window->draw(this->pauseButtonSprite);

	//LEVEL SCROLL BOX
	for (LevelScrollBox* lvlBox : this->levelManager->getLevelScrollBoxes()) {
		lvlBox->draw(*this->window);
	}
	this->levelManager->getLevelScrollOutline().draw(*this->window);
	this->window->draw(this->scrollBlockBox);

	//BUTTONS
	this->window->draw(this->resetButtonSprite);
	this->window->draw(this->levelButtonSprite);
	this->window->draw(this->gridButtonSprite);
	this->window->draw(this->muteButtonSprite);



	for (const auto& pair : this->towerBases) {
		TowerType key = pair.first;
		sf::Sprite* value = pair.second;

		this->window->draw(*value);
	}

	for (const auto& pair : this->towerButtons) {
		TowerType key = pair.first;
		sf::Sprite* value = pair.second;

		this->window->draw(*value);
	}

	if (this->showInfoWindow) {
		if (this->showInfoEnemy) this->infoWindowEnemy->render(this->window);
		else if (this->showInfoTower) {
			this->infoWindowTower->render(this->window);
			if (this->showInfoTowerSell) this->infoWindowTower->renderSellButton(this->window);
			if (this->showInfoUpgrade) {
				this->infoWindowUpgrade->render(this->window);
				this->infoWindowUpgrade->renderUpgradeButton(this->window);
			}
		}
	}



	this->window->display();
}


