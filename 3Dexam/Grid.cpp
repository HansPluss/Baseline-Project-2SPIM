#include "Grid.h"


Grid::Grid(int width, int height, int cellSize) : m_width(width), m_height(height), m_cellSize(cellSize)
{
	m_numXCells = ceil((float)m_width / cellSize);
	m_numYCells = ceil((float)m_height / cellSize);
	m_cells.resize(m_numYCells * m_numXCells);
}

Grid::~Grid()
{
}

Cell& Grid::getCell(int x, int y)
{
	if (x < 0)
		x = 0; 
	if (x >= m_numXCells)
		x = m_numXCells;
	if (y < 0)
		y = 0;

	if (y >= m_numYCells)
		y = m_numYCells;

	return m_cells[y * m_numXCells + m_numXCells]; 
}
