#pragma once
#include "vector"
class Draw; 
class Grid; 
class Collision

{
public:
	Collision();
	~Collision();
	void UpdateCollision(Grid* grid, float dt); 
	bool SphereCollison(Draw &objA, Draw &objB, float DeltaTime);
	bool AABBCollision(Draw &objA, Draw &objB, float DeltaTime);
	bool InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime);
	
private:
	void CollisionCalculations(Draw& objA, Draw& objB, float DeltaTime);
	void BallCollisionResponse(Draw& objA, Draw& objB);
	void CheckCollision(Draw* ball, std::vector<Draw*>& BallToCheck, int startingIndex, float dt);
};

