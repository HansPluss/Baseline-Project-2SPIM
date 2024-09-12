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
	bool SphereCollison(Draw &objA, Draw &objB, float DeltaTime);
	bool AABBCollision(Draw &objA, Draw &objB, float DeltaTime);
	bool InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime);
	
private:
	void CollisionCalculations(Draw& objA, Draw& objB, float DeltaTime);
	void AngularCollision(Draw& objA, Draw& objB);
};

