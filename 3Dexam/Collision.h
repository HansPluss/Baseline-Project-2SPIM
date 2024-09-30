#pragma once
#include "vector"
class Draw; 
class Grid; 
class QuadTree;
class Collision

{
public:

	Collision();
	~Collision();
	//|-----------------------------------------------------------------------------|
	//|									Public Functions							|
	//|-----------------------------------------------------------------------------|
	void UpdateCollision(Grid* grid, float dt); 
	bool AABBCollision(Draw &objA, Draw &objB, float DeltaTime);
	bool InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime);
	void UpdateQTCollision(QuadTree& tree, std::vector<Draw>& ballObjects, Draw& singleObject, float dt);
	void QTCheckCollision(QuadTree& tree, std::vector<Draw>& ballObjects, Draw& singleObject, float dt);
	void calculateBarycentricCoordinates(Draw& ball, Draw& drawObject);
private:
	//|-----------------------------------------------------------------------------|
	//|									Private Functions							|
	//|-----------------------------------------------------------------------------|
	bool SphereCollison(Draw& objA, Draw& objB, float DeltaTime);
	void CollisionCalculations(Draw& objA, Draw& objB, float DeltaTime);
	void BallCollisionResponse(Draw& objA, Draw& objB);
	void CheckCollision(Draw* ball, std::vector<Draw*>& BallToCheck, int startingIndex, float dt);
	
};

