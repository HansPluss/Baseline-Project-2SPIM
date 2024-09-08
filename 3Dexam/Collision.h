#pragma once
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Draw; 
class Collision
{
public:
	Collision();
	~Collision();
	bool SphereCollison(Draw &objA, Draw &objB);
	bool AABBCollision(Draw &objA, Draw &objB);
	bool InvAABBCollision(Draw& objA, Draw& objB);
	
private:
	void CollisionCalculations(Draw& objA, Draw& objB);
	void AngularCollision(Draw& objA, Draw& objB);
};

