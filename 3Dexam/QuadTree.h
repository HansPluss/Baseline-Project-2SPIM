#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Draw.h"
class Draw;
class QuadTree {
public:
	int maxObjects = 4;
	int maxDepth = 4;
	std::vector<Draw*> balls;
	int depth;
	glm::vec4 bounds;

	QuadTree* nodes[4];
	QuadTree(int depth, glm::vec4 bounds);
	void ClearTree();
	void SplitTree();
	void Insert(Draw *obj);
	int GetIndex(Draw* obj);
	
	std::vector<Draw*> Retrieve(std::vector<Draw*>& returnObjects, Draw* obj);
};