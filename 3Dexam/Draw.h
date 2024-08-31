#pragma once
#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "Resources/Shaders/shaderClass.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Resources/Shaders/VAO.h"
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/EBO.h"

class Shader; 
struct Vertex
{

	float x, y, z;
	float r, g, b;
	float u, v;
	float normalx, normaly, normalz;


};
class Draw {
public:
	Draw();

	void DrawCube(glm::vec3 Color, glm::vec3 pos, glm::vec3 size)  ;
	std::vector<Vertex> DrawSphere(glm::vec3 Color, glm::vec3 pos, glm::vec3 size);
	void Render(Shader shader, glm::mat4 viewproj);

	void Delete();

private:
	void Initalize();


	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 position = glm::vec3(0,0,0); 
	glm::vec3 objSize = glm::vec3(1,1,1);
	VAO VAO;
	VBO VBO;
	EBO EBO1;
};