#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u, v;
	float normalx, normaly, normalz;


};
class Draw {
public:
	std::vector<Vertex> DrawCube(glm::vec3 Color);

};