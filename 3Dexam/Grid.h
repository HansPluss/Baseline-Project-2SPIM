#pragma once
#include "vector"
#include "Draw.h"

struct Cell {
	std::vector<Draw*> balls;
};
class Grid
{
	friend class Collision;
public: 
	Grid(int width, int height, int cellSize); 
	~Grid(); 

	void AddBaLL(Draw* ball);
	void AddBaLL(Draw* ball, Cell* cell);

	Cell* getCell(int x, int y);
	Cell* getCell(const glm::vec3& pos);


	void RemoveBallFromCell(Draw* ball); 

private: 
	std::vector<Cell> m_cells; 
	int m_cellSize;
	int m_width;
	int m_height;
	int m_numXCells;
	int m_numYCells; 
};

