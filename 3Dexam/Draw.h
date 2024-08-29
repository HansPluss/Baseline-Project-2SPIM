#pragma once
#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Resources/Shaders/VAO.h"
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/EBO.h"
struct Vertex
{
	float x, y, z;
	float r, g, b;
	float u, v;
	float normalx, normaly, normalz;


};
class Draw {
public:
	std::vector<Vertex> DrawCube(glm::vec3 Color, std::vector<unsigned int>& indices);
	std::vector<Vertex> DrawSphere(glm::vec3 Color, std::vector<unsigned int>& indices);
	void Render(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	VAO VAO;
	VBO VBO;
	EBO EBO;
};