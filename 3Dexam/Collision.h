#pragma once
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class Collision
{
public:
	Collision();
	~Collision();
	glm::vec3 position;
	float sphere_radius = 1.0f;
	float size = 1.0f;
	bool SphereCollison(Collision otherObject);
	bool AABBCollision(Collision otherObject);
private:

};

