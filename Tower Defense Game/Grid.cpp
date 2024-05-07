#include "Grid.h"

unsigned int Grid::m_cols = Properties::gridTileNumHorizontal;
unsigned int Grid::m_rows = Properties::gridTileNumVertical;
float Grid::m_tileSize = Properties::tileSize;

std::vector<std::vector<Tile>> Grid::m_tiles;
std::map<Path, std::vector<Tile*>> Grid::entranceTiles;
std::map<Path, std::vector<Tile*>> Grid::exitTiles;

void Grid::moveToCorrectPlace()
{
	for (size_t i = 0; i < m_rows; i++)
	{
		for (size_t j = 0; j < m_cols; j++)
		{
			m_tiles[i][j].setPosition(m_tiles[i][j].getPosition() + sf::Vector2f(Properties::gridLeftOffset, Properties::gridTopOffset));
		}
	}
}

Grid::Grid(std::vector<Enemy*>& enemies) : enemies(enemies) {
	Grid::resetTiles();
}

Grid& Grid::getInstance(std::vector<Enemy*>& enemies) {
	static Grid instance(enemies);
	return instance;
}

void Grid::draw(sf::RenderWindow& window) {
	for (auto& row : m_tiles) {
		for (auto& tile : row) {
			tile.draw(window);
		}
	}
}

void Grid::handleMouseMove(const sf::Vector2f& mousePos)
{
	// Calculate the index of the tile that the mouse is currently over
	int col = static_cast<int>((-Properties::gridLeftOffset + mousePos.x) / m_tileSize);
	int row = static_cast<int>((-Properties::gridTopOffset + mousePos.y) / m_tileSize);

	// Reset the color of all tiles
	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			m_tiles[i][j].resetColor();
		}
	}

	bool valid = true;

	if (row >= 0 && row < m_rows - 1 && col >= 0 && col < m_cols - 1) {
		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				if (m_tiles[i][j].getType() != TileType::DEFAULT || m_tiles[i][j].getOccupyNumber() != 0) valid = false;
			}
		}
	}

	// Highlight the 2x2 area of tiles if the mouse is within bounds
	if (row >= 0 && row < m_rows - 1 && col >= 0 && col < m_cols - 1) {
		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				m_tiles[i][j].highlight(valid);
			}
		}
	}
}

std::map<Path, std::vector<Tile*>> Grid::getEntranceTiles()
{
	return entranceTiles;
}

std::map<Path, std::vector<Tile*>> Grid::getExitTiles()
{
	return exitTiles;
}

Tile* Grid::getNearestTile(sf::Vector2f position) {
	float shortestDistance = std::numeric_limits<float>::max();
	Tile* nearestTile = nullptr;

	for (const auto& row : m_tiles) {
		for (const auto& tile : row) {
			float distance = std::sqrt(std::pow(tile.getPosition().x - position.x, 2) +
				std::pow(tile.getPosition().y - position.y, 2));
			if (distance < shortestDistance) {
				shortestDistance = distance;
				nearestTile = const_cast<Tile*>(&tile); // You might need to cast away constness
			}
		}
	}

	return nearestTile;
}

std::map<Arrow, Tile*> Grid::setupTileNeighbors(int row, int col) {
	std::map<Arrow, Tile*> neighbors;
	if (col != m_cols - 1)
		neighbors[Arrow::RIGHT] = &m_tiles[row][col + 1];
	if (row != 0)
		neighbors[Arrow::UP] = &m_tiles[row - 1][col];
	if (col != 0)
		neighbors[Arrow::LEFT] = &m_tiles[row][col - 1];
	if (row != m_rows - 1)
		neighbors[Arrow::DOWN] = &m_tiles[row + 1][col];
	if (row != 0 && col != m_cols - 1)
		neighbors[Arrow::UPRIGHT] = &m_tiles[row - 1][col + 1];
	if (row != m_rows - 1 && col != m_cols - 1)
		neighbors[Arrow::DOWNRIGHT] = &m_tiles[row + 1][col + 1];
	if (row != 0 && col != 0)
		neighbors[Arrow::UPLEFT] = &m_tiles[row - 1][col - 1];
	if (row != m_rows - 1 && col != 0)
		neighbors[Arrow::DOWNLEFT] = &m_tiles[row + 1][col - 1];


	return neighbors;
}


void Grid::resetTiles()
{
	m_tiles.clear();
	entranceTiles.clear();
	exitTiles.clear();

	m_tiles.reserve(m_rows);
	for (unsigned int i = 0; i < m_rows; ++i) {
		std::vector<Tile> row;
		row.reserve(m_cols);
		for (unsigned int j = 0; j < m_cols; ++j) {
			if (i == 0 || i == m_rows - 1 || j == 0 || j == m_cols - 1) {
				row.emplace_back(j, i, j * m_tileSize, i * m_tileSize, Properties::colorGridWall, TileType::WALL);
			}
			else {
				row.emplace_back(j, i, j * m_tileSize, i * m_tileSize, Properties::colorGridTile, TileType::DEFAULT);
			}
		}
		m_tiles.push_back(std::move(row));
	}

	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			m_tiles[i][j].setNeighbors(setupTileNeighbors(i, j));
		}
	}

	for (size_t i = 0; i < 6; i++)
	{
		Tile* tmp = &m_tiles[i + 9][0];
		tmp->setType(TileType::ENTRANCE);
		tmp->setBaseColor(Properties::colorGridTile);
		tmp->resetColor();
		entranceTiles[Path::HORIZONTAL].emplace_back(tmp);
	}

	for (size_t i = 0; i < 3; i++)
	{
		Tile* tmp = &m_tiles[11 - i][m_cols - 1];
		tmp->setType(TileType::EXIT);
		tmp->setBaseColor(Properties::colorGridTile);
		tmp->resetColor();
		exitTiles[Path::HORIZONTAL].emplace_back(tmp);

		tmp = &m_tiles[12 + i][m_cols - 1];
		tmp->setType(TileType::EXIT);
		tmp->setBaseColor(Properties::colorGridTile);
		tmp->resetColor();
		exitTiles[Path::HORIZONTAL].emplace_back(tmp);
	}

	//VERTICAL

//for (size_t i = 0; i < 8; i++)
//{
//	Tile* tmp = &m_tiles[0][i + 10];
//	tmp->setType(TileType::ENTRANCE);
//	tmp->setBaseColor(sf::Color(0, 0, 255, 100));
//	entranceTiles[Path::VERTICAL].emplace_back(tmp);
//}

//for (size_t i = 0; i < 4; i++)
//{
//	Tile* tmp = &m_tiles[m_rows - 1][13-i];
//	tmp->setType(TileType::EXIT);
//	tmp->setBaseColor(sf::Color(0, 0, 255, 100));
//	exitTiles[Path::VERTICAL].emplace_back(tmp);

//	tmp = &m_tiles[m_rows - 1][14+i];
//	tmp->setType(TileType::EXIT);
//	tmp->setBaseColor(sf::Color(0, 0, 255, 100));
//	exitTiles[Path::VERTICAL].emplace_back(tmp);
//}

	Grid::moveToCorrectPlace();
}

void Grid::resetPath(Path path) {
	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			m_tiles[i][j].setArrow(Arrow::DEFAULT, path);
		}
	}
}

void Grid::resetPaths() {
	resetPath(Path::HORIZONTAL);
	//resetPath(Path::VERTICAL);
}

void Grid::createPath(Path path) {
	std::queue<Tile*> fifoStack;
	std::set<Tile*> uniqueElems;

	auto enqueueUnique = [&](Tile* element, int distance) {
		if (uniqueElems.find(element) == uniqueElems.end()) {
			fifoStack.push(element);
			uniqueElems.insert(element);
			element->setDistanceFromExit(distance + 1, path);
		}
		};

	Arrow exitArrow;
	if (path == Path::HORIZONTAL) exitArrow = Arrow::RIGHT;
	else if (path == Path::VERTICAL) exitArrow = Arrow::DOWN;

	std::vector<Tile*> tmp = exitTiles[path];

	for (auto* tile : tmp) {
		tile->setArrow(exitArrow, path);
		tile->setDistanceFromExit(0, path);

		Tile* exitNeighbor;

		if (path == Path::HORIZONTAL) exitNeighbor = tile->getNeighbors()[Arrow::LEFT];
		else exitNeighbor = tile->getNeighbors()[Arrow::UP];

		if (exitNeighbor->getType() != TileType::TOWER && exitNeighbor->getArrow(path) == Arrow::DEFAULT) {
			enqueueUnique(exitNeighbor, tile->getDistanceFromExit(path));
		}
	}


	while (!fifoStack.empty()) {
		Tile* tile = fifoStack.front();
		bool arrowSet = false;

		std::map<Arrow, Tile*> neighbors = tile->getNeighbors();
		Tile* up = neighbors[Arrow::UP];
		Tile* down = neighbors[Arrow::DOWN];
		Tile* right = neighbors[Arrow::RIGHT];
		Tile* left = neighbors[Arrow::LEFT];
		Tile* upright = neighbors[Arrow::UPRIGHT];
		Tile* downright = neighbors[Arrow::DOWNRIGHT];
		Tile* upleft = neighbors[Arrow::UPLEFT];
		Tile* downleft = neighbors[Arrow::DOWNLEFT];


		if (!arrowSet && right != nullptr && up != nullptr) {
			if ((upright->getType() == TileType::DEFAULT || upright->getType() == TileType::ENTRANCE) && up->getType() == TileType::DEFAULT && right->getType() == TileType::DEFAULT && (right->getArrow(path) == Arrow::UPRIGHT || up->getArrow(path) == Arrow::UPRIGHT) || (right->getArrow(path) == Arrow::UP && up->getArrow(path) == Arrow::RIGHT)) {
				tile->setArrow(Arrow::UPRIGHT, path);
				arrowSet = true;
			}
		}

		if (!arrowSet && right != nullptr && down != nullptr) {
			if ((downright->getType() == TileType::DEFAULT || downright->getType() == TileType::ENTRANCE) && down->getType() == TileType::DEFAULT && right->getType() == TileType::DEFAULT && (right->getArrow(path) == Arrow::DOWNRIGHT || down->getArrow(path) == Arrow::DOWNRIGHT) || (right->getArrow(path) == Arrow::DOWN && down->getArrow(path) == Arrow::RIGHT)) {
				tile->setArrow(Arrow::DOWNRIGHT, path);
				arrowSet = true;
			}
		}

		if (!arrowSet && left != nullptr && up != nullptr) {
			if ((upleft->getType() == TileType::DEFAULT || upleft->getType() == TileType::ENTRANCE) && up->getType() == TileType::DEFAULT && left->getType() == TileType::DEFAULT && (left->getArrow(path) == Arrow::UPLEFT || up->getArrow(path) == Arrow::UPLEFT) || (left->getArrow(path) == Arrow::UP && up->getArrow(path) == Arrow::LEFT)) {
				tile->setArrow(Arrow::UPLEFT, path);
				arrowSet = true;
			}
		}

		if (!arrowSet && left != nullptr && down != nullptr) {
			if ((downleft->getType() == TileType::DEFAULT || downleft->getType() == TileType::ENTRANCE) && down->getType() == TileType::DEFAULT && left->getType() == TileType::DEFAULT && (left->getArrow(path) == Arrow::DOWNLEFT || down->getArrow(path) == Arrow::DOWNLEFT) || (left->getArrow(path) == Arrow::DOWN && down->getArrow(path) == Arrow::LEFT)) {
				tile->setArrow(Arrow::DOWNLEFT, path);
				arrowSet = true;
			}
		}


		//std::map<Arrow, Tile*>::iterator it;

		//for (it = neighbors.begin(); it != neighbors.end(); ++it) {
		//	if (it->second != nullptr) {
		//		if (!arrowSet && it->second->getArrow(path) != Arrow::DEFAULT) {
		//			tile->setArrow(it->first);
		//			arrowSet = true;
		//		}
		//		else if (!it->second->isOccupied() && it->second->getArrow(path) == Arrow::DEFAULT) {
		//			enqueueUnique(it->second, tile->getDistanceFromExit());
		//		}
		//	}
		//}

		if (path == Path::HORIZONTAL) {
			if (right != nullptr) {
				if (!arrowSet && right->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::RIGHT, path);
					arrowSet = true;
				}
				else if ((right->getType() == TileType::DEFAULT || right->getType() == TileType::ENTRANCE) && right->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(right, tile->getDistanceFromExit(path));
				}
			}

			if (up != nullptr) {
				if (!arrowSet && up->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::UP, path);
					arrowSet = true;
				}
				else if ((up->getType() == TileType::DEFAULT || up->getType() == TileType::ENTRANCE) && up->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(up, tile->getDistanceFromExit(path));
				}
			}

			if (down != nullptr) {
				if (!arrowSet && down->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::DOWN, path);
					arrowSet = true;
				}
				else if ((down->getType() == TileType::DEFAULT || down->getType() == TileType::ENTRANCE) && down->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(down, tile->getDistanceFromExit(path));
				}
			}

			if (left != nullptr) {
				if (!arrowSet && left->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::LEFT, path);
					arrowSet = true;
				}
				else if ((left->getType() == TileType::DEFAULT || left->getType() == TileType::ENTRANCE) && left->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(left, tile->getDistanceFromExit(path));
				}
			}
		}

		else {
			if (down != nullptr) {
				if (!arrowSet && down->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::DOWN, path);
					arrowSet = true;
				}
				else if ((down->getType() == TileType::DEFAULT || down->getType() == TileType::ENTRANCE) && down->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(down, tile->getDistanceFromExit(path));
				}
			}

			if (right != nullptr) {
				if (!arrowSet && right->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::RIGHT, path);
					arrowSet = true;
				}
				else if ((right->getType() == TileType::DEFAULT || right->getType() == TileType::ENTRANCE) && right->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(right, tile->getDistanceFromExit(path));
				}
			}

			if (left != nullptr) {
				if (!arrowSet && left->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::LEFT, path);
					arrowSet = true;
				}
				else if ((left->getType() == TileType::DEFAULT || left->getType() == TileType::ENTRANCE) && left->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(left, tile->getDistanceFromExit(path));
				}
			}


			if (up != nullptr) {
				if (!arrowSet && up->getArrow(path) != Arrow::DEFAULT) {
					tile->setArrow(Arrow::UP, path);
					arrowSet = true;
				}
				else if ((up->getType() == TileType::DEFAULT || up->getType() == TileType::ENTRANCE) && up->getArrow(path) == Arrow::DEFAULT) {
					enqueueUnique(up, tile->getDistanceFromExit(path));
				}
			}
		}

		if (tile->getArrow(path) == Arrow::UPRIGHT || tile->getArrow(path) == Arrow::UPLEFT || tile->getArrow(path) == Arrow::DOWNLEFT || tile->getArrow(path) == Arrow::DOWNRIGHT) {
			tile->setDistanceFromExit(tile->getDistanceFromExit(path) - 1, path);
		}

		fifoStack.pop();
		//visualizePath();
	}
}

void Grid::createPaths() {
	createPath(Path::HORIZONTAL);
	//createPath(Path::VERTICAL);
}


void Grid::visualizePath(Path path) {
	//for (unsigned int i = 0; i < m_rows; ++i) {
	//	for (unsigned int j = 0; j < m_cols; ++j) {
	//		char symbol;
	//		switch (m_tiles[i][j].getArrow(path)) {
	//		case Arrow::UP:
	//			symbol = '^';
	//			break;
	//		case Arrow::RIGHT:
	//			symbol = '>';
	//			break;
	//		case Arrow::LEFT:
	//			symbol = '<';
	//			break;
	//		case Arrow::DOWN:
	//			symbol = 'v';
	//			break;
	//		case Arrow::UPRIGHT:
	//			symbol = 'n';
	//			break;
	//		case Arrow::DOWNRIGHT:
	//			symbol = 'u';
	//			break;
	//		case Arrow::UPLEFT:
	//			symbol = '3';
	//			break;
	//		case Arrow::DOWNLEFT:
	//			symbol = 'e';
	//			break;
	//		default:
	//			symbol = ' ';
	//		}
	//		std::cout << symbol;
	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "\n\n";

	//for (unsigned int i = 0; i < m_rows; ++i) {
	//	for (unsigned int j = 0; j < m_cols; ++j) {
	//		std::cout << static_cast<int>(m_tiles[i][j].getType());
	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "\n\n";

	//for (unsigned int i = 0; i < m_rows; ++i) {
	//	for (unsigned int j = 0; j < m_cols; ++j) {
	//		std::cout << std::setw(2) << std::setfill('0') << m_tiles[i][j].getDistanceFromExit();
	//	}
	//	std::cout << "\n";
	//}
	//std::cout << "\n\n";
}

void Grid::visualizePaths() {
	visualizeOccupy();
	visualizePath(Path::HORIZONTAL);
	//visualizePath(Path::VERTICAL);
}

void Grid::visualizeOccupy() {
	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			std::cout << m_tiles[i][j].getOccupyNumber();
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}


bool Grid::canPlaceTower(const sf::Vector2i& mousePos)
{

	// Calculate the index of the tile that the mouse is currently over
	int col = static_cast<int>((-Properties::gridLeftOffset + mousePos.x) / m_tileSize);

	// Check if mousePos outside grid
	if (col >= m_cols - 1)
		return false;

	// Calculate the index of the tile that the mouse is currently over
	int row = static_cast<int>((-Properties::gridTopOffset + mousePos.y) / m_tileSize);

	// Check if mousePos outside grid
	if (row >= m_rows - 1)
		return false;

	// Check if all tiles that the tower is supposed to be placed at are unoccupied
	if (row >= 0 && row < m_rows - 1 && col >= 0 && col < m_cols - 1) {
		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				if (m_tiles[i][j].getType() != TileType::DEFAULT || m_tiles[i][j].getOccupyNumber() != 0) return false;
			}
		}

		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				m_tiles[i][j].setType(TileType::TOWER);
			}
		}

		resetPaths();
		createPaths();

		for (auto* tile : entranceTiles[Path::HORIZONTAL]) {
			if (tile->getArrow(Path::HORIZONTAL) == Arrow::DEFAULT) {
				for (int i = row; i <= row + 1; ++i) {
					for (int j = col; j <= col + 1; ++j) {
						m_tiles[i][j].setType(TileType::DEFAULT);
					}
				}
				resetPaths();
				createPaths();
				return false;
			}
		}
		for (auto* tile : entranceTiles[Path::VERTICAL]) {
			if (tile->getArrow(Path::VERTICAL) == Arrow::DEFAULT) {
				for (int i = row; i <= row + 1; ++i) {
					for (int j = col; j <= col + 1; ++j) {
						m_tiles[i][j].setType(TileType::DEFAULT);
					}
				}
				resetPaths();
				createPaths();
				return false;
			}
		}
	}

	for (int i = row; i <= row + 1; ++i) {
		for (int j = col; j <= col + 1; ++j) {
			m_tiles[i][j].setType(TileType::DEFAULT);
		}
	}

	return true;
}

Tower* Grid::placeTower(const sf::Vector2i& mousePos, TowerType type)
{
	// Calculate the index of the tile that the mouse is currently over
	int col = static_cast<int>((-Properties::gridLeftOffset + mousePos.x) / m_tileSize);
	int row = static_cast<int>((-Properties::gridTopOffset + mousePos.y) / m_tileSize);

	int posX = m_tiles[row][col].getBounds().left + m_tiles[row][col].getBounds().width;
	int posY = m_tiles[row][col].getBounds().top + m_tiles[row][col].getBounds().height;

	std::vector<Tile*> towerTiles;

	if (row >= 0 && row < m_rows - 1 && col >= 0 && col < m_cols - 1) {
		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				towerTiles.emplace_back(&m_tiles[i][j]);
				//m_tiles[i][j].setType(TileType::TOWER);
			}
		}
	}

	return new Tower(enemies, towerTiles, type);
}
