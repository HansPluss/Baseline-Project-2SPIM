#pragma once
#include "vector"
#include "Draw.h"

struct Cell {
	std::vector<Draw*> balls;
};
class Grid
{

public: 
	Grid(int width, int height, int cellSize); 
	~Grid(); 

	Cell& getCell(int x, int y);

private: 
	std::vector<Cell> m_cells; 
	int m_cellSize;
	int m_width;
	int m_height;
	int m_numXCells;
	int m_numYCells; 
};

