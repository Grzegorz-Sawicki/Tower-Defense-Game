#include "Grid.h"

unsigned int Grid::m_cols = Properties::gridTileNumHorizontal;
unsigned int Grid::m_rows = Properties::gridTileNumVertical;
float Grid::m_tileSize = Properties::tileSize;

std::vector<std::vector<Tile>> Grid::m_tiles;
std::map<std::string, std::vector<Tile*>> Grid::entranceTiles;
std::map<std::string, std::vector<Tile*>> Grid::exitTiles;

void Grid::moveToCorrectPlace()
{
	for (size_t i = 0; i < m_rows; i++)
	{
		for (size_t j = 0; j < m_cols; j++)
		{
			m_tiles[i][j].setPosition(m_tiles[i][j].getPosition() + sf::Vector2f(60.f, 60.f));
		}
	}
}

Grid::Grid() {

	// Initialize tiles
	m_tiles.reserve(m_rows);

	for (unsigned int i = 0; i < m_rows; ++i) {
		std::vector<Tile> row;
		row.reserve(m_cols);
		for (unsigned int j = 0; j < m_cols; ++j) {
			if (i == 0 || i == m_rows - 1 || j == 0 || j == m_cols - 1) {
				row.emplace_back(j, i, j * m_tileSize, i * m_tileSize, sf::Color(150, 150, 150, 100), true);
			}
			else {
				row.emplace_back(j, i, j * m_tileSize, i * m_tileSize, sf::Color(0, 0, 255, 100), false);
			}
		}
		m_tiles.push_back(std::move(row));
	}

	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			m_tiles[i][j].setNeighbors(setupTileNeighbors(i, j));
		}
	}

	//TODO: COLORS ARE SET ONLY WHEN CURSOR IN WINDOW

	// set entrance tiles
	for (size_t i = 0; i < 6; i++)
	{
		Tile* tmp = &m_tiles[i + 9][0];
		tmp->setOccupied(false);
		tmp->setType(TileType::ENTRANCE);
		tmp->setBaseColor(sf::Color(0, 0, 255, 100));
		entranceTiles["HORIZONTAL"].emplace_back(tmp);

		//tmp->setArrow(RIGHT); //TEMP FOR TESTING
	}

	//set exit tiles
	for (size_t i = 0; i < 6; i++)
	{
		Tile* tmp = &m_tiles[i + 9][m_cols - 1];
		tmp->setOccupied(false);
		tmp->setType(TileType::EXIT);
		tmp->setBaseColor(sf::Color(0, 0, 255, 100));
		exitTiles["HORIZONTAL"].emplace_back(tmp);
	}

	this->moveToCorrectPlace();
}

Grid& Grid::getInstance() {
	static Grid instance;
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
	//TEMP NUMBERS 9 = tilesize/2, 60 = arbitrary offset 
	int col = static_cast<int>((9 - 60 + mousePos.x - m_tileSize / 2) / m_tileSize);
	int row = static_cast<int>((9 - 60 + mousePos.y - m_tileSize / 2) / m_tileSize);

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
				if (m_tiles[i][j].isOccupied() || m_tiles[i][j].getType() == TileType::ENTRANCE || m_tiles[i][j].getType() == TileType::EXIT) valid = false;
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

std::map<std::string, std::vector<Tile*>> Grid::getEntranceTiles()
{
	return entranceTiles;
}

std::map<std::string, std::vector<Tile*>> Grid::getExitTiles()
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
	if (row != 0 && col != 0)
		neighbors[Arrow::UPLEFT] = &m_tiles[row - 1][col - 1];
	if (row != 0 && col != m_cols - 1)
		neighbors[Arrow::UPRIGHT] = &m_tiles[row - 1][col + 1];
	if (row != m_rows - 1 && col != 0)
		neighbors[Arrow::DOWNLEFT] = &m_tiles[row + 1][col - 1];
	if (row != m_rows - 1 && col != m_cols - 1)
		neighbors[Arrow::DOWNRIGHT] = &m_tiles[row + 1][col + 1];
	if (row != 0)
		neighbors[Arrow::UP] = &m_tiles[row - 1][col];
	if (row != m_rows-1)
		neighbors[Arrow::DOWN] = &m_tiles[row + 1][col];
	if (col != 0)
		neighbors[Arrow::LEFT] = &m_tiles[row][col-1];
	if (col != m_cols-1)
		neighbors[Arrow::RIGHT] = &m_tiles[row][col + 1];

	return neighbors;
}

void Grid::resetPath() {
	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			m_tiles[i][j].setArrow(Arrow::DEFAULT);
		}
	}
}

void Grid::createPath() {
	std::queue<Tile*> fifoStack;
	std::set<Tile*> uniqueElems;

	auto enqueueUnique = [&](Tile* element) {
		if (uniqueElems.find(element) == uniqueElems.end()) {
			fifoStack.push(element);
			uniqueElems.insert(element);
		}
	};

	std::vector<Tile*> tmp = exitTiles["HORIZONTAL"];

	for (auto* tile : tmp) {
		tile->setArrow(Arrow::RIGHT);

		std::map<Arrow, Tile*> neighbors = tile->getNeighbors();
		Tile* left = neighbors[Arrow::LEFT];

		if (!left->isOccupied() && left->getArrow() == Arrow::DEFAULT) {
			enqueueUnique(neighbors[Arrow::LEFT]);
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

		if (right != nullptr && up != nullptr) {
			if (!arrowSet && !upright->isOccupied() && !up->isOccupied() && !right->isOccupied() && (right->getArrow() == Arrow::UPRIGHT || up->getArrow() == Arrow::UPRIGHT) || (right->getArrow() == Arrow::UP && up->getArrow() == Arrow::RIGHT)) {
				tile->setArrow(Arrow::UPRIGHT);
				arrowSet = true;
			}
		}

		if (right != nullptr && down != nullptr) {
			if (!arrowSet && !downright->isOccupied() && !down->isOccupied() && !right->isOccupied() && (right->getArrow() == Arrow::DOWNRIGHT || down->getArrow() == Arrow::DOWNRIGHT) || (right->getArrow() == Arrow::DOWN && down->getArrow() == Arrow::RIGHT)) {
				tile->setArrow(Arrow::DOWNRIGHT);
				arrowSet = true;
			}
		}

		if (left != nullptr && up != nullptr) {
			if (!arrowSet && !upleft->isOccupied() && !up->isOccupied() && !left->isOccupied() && (left->getArrow() == Arrow::UPLEFT || up->getArrow() == Arrow::UPLEFT) || (left->getArrow() == Arrow::UP && up->getArrow() == Arrow::LEFT)) {
				tile->setArrow(Arrow::UPLEFT);
				arrowSet = true;
			}
		}

		if (left != nullptr && down != nullptr) {
			if (!arrowSet && !downleft->isOccupied() && !down->isOccupied() && !left->isOccupied() && (left->getArrow() == Arrow::DOWNLEFT || down->getArrow() == Arrow::DOWNLEFT) || (left->getArrow() == Arrow::DOWN && down->getArrow() == Arrow::LEFT)) {
				tile->setArrow(Arrow::DOWNLEFT);
				arrowSet = true;
			}
		}

		if (right != nullptr) {
			if (!arrowSet && right->getArrow() != Arrow::DEFAULT) {
				tile->setArrow(Arrow::RIGHT);
				arrowSet = true;
			}
			else if (!right->isOccupied() && right->getArrow() == Arrow::DEFAULT) {
				enqueueUnique(neighbors[Arrow::RIGHT]);
			}
		}

		if (up != nullptr) {
			if (!arrowSet && up->getArrow() != Arrow::DEFAULT) {
				tile->setArrow(Arrow::UP);
				arrowSet = true;
			}
			else if (!up->isOccupied() && up->getArrow() == Arrow::DEFAULT) {
				enqueueUnique(neighbors[Arrow::UP]);
			}
		}

		if (down != nullptr) {
			if (!arrowSet && down->getArrow() != Arrow::DEFAULT) {
				tile->setArrow(Arrow::DOWN);
				arrowSet = true;
			}
			else if (!down->isOccupied() && down->getArrow() == Arrow::DEFAULT) {
				enqueueUnique(neighbors[Arrow::DOWN]);
			}
		}

		if (left != nullptr) {
			if (!arrowSet && left->getArrow() != Arrow::DEFAULT) {
				tile->setArrow(Arrow::LEFT);
				arrowSet = true;
			}
			else if (!left->isOccupied() && left->getArrow() == Arrow::DEFAULT) {
				enqueueUnique(neighbors[Arrow::LEFT]);
			}
		}
		
		fifoStack.pop();
	}

}

void Grid::visualizePath() {
	for (unsigned int i = 0; i < m_rows; ++i) {
		for (unsigned int j = 0; j < m_cols; ++j) {
			char symbol;
			switch (m_tiles[i][j].getArrow()) {
			case Arrow::UP:
				symbol = '^';
				break;
			case Arrow::RIGHT:
				symbol = '>';
				break;
			case Arrow::LEFT:
				symbol = '<';
				break;
			case Arrow::DOWN:
				symbol = 'v';
				break;
			case Arrow::UPRIGHT:
				symbol = 'n';
				break;
			case Arrow::DOWNRIGHT:
				symbol = 'u';
				break;
			case Arrow::UPLEFT:
				symbol = '3';
				break;
			case Arrow::DOWNLEFT:
				symbol = 'e';
				break;
			default:
				symbol = ' ';
			} 
			std::cout << symbol;
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

bool Grid::canPlaceTower(const sf::Vector2i& mousePos)
{

	// Calculate the index of the tile that the mouse is currently over
	int col = static_cast<int>((9 - 60 + mousePos.x - m_tileSize / 2) / m_tileSize);

	// Check if mousePos outside grid
	if (col >= m_cols - 1)
		return false;

	// Calculate the index of the tile that the mouse is currently over
	int row = static_cast<int>((9 - 60 + mousePos.y - m_tileSize / 2) / m_tileSize);

	// Check if mousePos outside grid
	if (row >= m_rows - 1)
		return false;

	// Check if all tiles that the tower is supposed to be placed at are unoccupied
	if (row >= 0 && row < m_rows - 1 && col >= 0 && col < m_cols - 1) {
		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				if (m_tiles[i][j].isOccupied() || m_tiles[i][j].getType() == TileType::ENTRANCE || m_tiles[i][j].getType() == TileType::EXIT) return false;
			}
		}

		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				m_tiles[i][j].setOccupied(true);
			}
		}

		resetPath();
		createPath();
		
		for (auto* tile : entranceTiles["HORIZONTAL"]) {
			if (tile->getArrow() == Arrow::DEFAULT) {
				for (int i = row; i <= row + 1; ++i) {
					for (int j = col; j <= col + 1; ++j) {
						m_tiles[i][j].setOccupied(false);
					}
				}
				resetPath();
				createPath();
				return false;
			}
		}
	}

	return true;
}

Tower* Grid::placeTower(const sf::Vector2i& mousePos)
{
	// Calculate the index of the tile that the mouse is currently over
	int col = static_cast<int>((9 - 60 + mousePos.x - m_tileSize / 2) / m_tileSize);
	int row = static_cast<int>((9 - 60 + mousePos.y - m_tileSize / 2) / m_tileSize);

	int posX = m_tiles[row][col].getBounds().left + m_tiles[row][col].getBounds().width;
	int posY = m_tiles[row][col].getBounds().top + m_tiles[row][col].getBounds().height;

	if (row >= 0 && row < m_rows - 1 && col >= 0 && col < m_cols - 1) {
		for (int i = row; i <= row + 1; ++i) {
			for (int j = col; j <= col + 1; ++j) {
				m_tiles[i][j].setOccupied(true);
			}
		}
	}

	return new Tower(posX, posY);
}
