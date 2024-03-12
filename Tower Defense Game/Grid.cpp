#include "Grid.h"

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

Grid::Grid(unsigned int rows, unsigned int cols, float tileSize) : m_rows(rows), m_cols(cols), m_tileSize(tileSize) {

	// Initialize tiles
	m_tiles.reserve(m_rows);

	for (unsigned int i = 0; i < m_rows; ++i) {
		std::vector<Tile> row;
		row.reserve(m_cols);
		for (unsigned int j = 0; j < m_cols; ++j) {
			if (i == 0 || i == m_rows - 1 || j == 0 || j == m_cols - 1) {
				row.emplace_back(j * m_tileSize, i * m_tileSize, m_tileSize, sf::Color(150, 150, 150, 100), true);
			}
			else {
				row.emplace_back(j * m_tileSize, i * m_tileSize, m_tileSize, sf::Color(0, 0, 255, 100), false);
			}
		}
		m_tiles.push_back(std::move(row));
	}

	//TODO: COLORS ARE SET ONLY WHEN CURSOR IN WINDOW

	// set entrance tiles
	for (size_t i = 0; i < 6; i++)
	{
		Tile* tmp = &m_tiles[i + 9][0];
		tmp->setBaseColor(sf::Color(0, 0, 255, 100));
		entranceTiles["HORIZONTAL"].emplace_back(tmp);
	}

	//set exit tiles
	for (size_t i = 0; i < 6; i++)
	{
		Tile* tmp = &m_tiles[i + 9][m_cols-1];
		tmp->setBaseColor(sf::Color(0, 0, 255, 100));
		exitTiles["HORIZONTAL"].emplace_back(tmp);
	}

	this->moveToCorrectPlace();
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
				if (m_tiles[i][j].isOccupied()) valid = false;
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
	return this->entranceTiles;
}

std::map<std::string, std::vector<Tile*>> Grid::getExitTiles()
{
	return this->exitTiles;
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
				if (m_tiles[i][j].isOccupied()) return false;
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
