#pragma once
#include <vector>
#include "Resources/Shaders/VAO.h"
#include "Resources/Shaders/VBO.h"
#include "Resources/Shaders/EBO.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/glm.hpp"


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

	void DrawCube(glm::vec3 Color, glm::vec3 pos, glm::vec3 size);
	void DrawPlane(glm::vec3 Color, glm::vec3 pos, glm::vec3 size);
	void DrawBoundingBox(glm::vec3 Color, glm::vec3 pos, glm::vec3 size);
	void DrawSphere(glm::vec3 Color, glm::vec3 pos, glm::vec3 size);
	void Render(Shader shader, glm::mat4 viewproj);


	glm::vec3 GetPosition();
	glm::vec3 GetSize();
	void SetPosition(glm::vec3 newPos);
	float GetMass();
	void SetMass(float newMass);
	void SetVelocity(glm::vec3 newVelocity);
	glm::vec3 GetVelocity();
	void ApplyForce(glm::vec3 force);
	void Update(float deltaTime);
	void MoveXdir();
	float speed = 0;
	void Delete();
	void SetNormalVector(glm::vec3 normal);
	void SetAngularVelocity(glm::vec3 angularVelocity);
	glm::vec3 GetAngularVelocity();
	void RotateCube(float deltaTime);
	glm::vec3 GetNormal();


private:
	void Initalize();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::quat Quaternion = glm::quat(1.0, 0.0, 0.0, 0.0);
	glm::vec3 objSize = glm::vec3(1, 1, 1);
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	glm::vec3 Acceleration = glm::vec3(0, 0, 0);
	glm::vec3 AngularVelocity = glm::vec3(0, 0, 0);
	glm::vec3 AngularAcceleration = glm::vec3(0, 0, 0);
	glm::vec3 normalvector = glm::vec3(0, 0, 0);
	float mass = 1.0f;
	VAO VAO;
	VBO VBO;
	EBO EBO1;
};