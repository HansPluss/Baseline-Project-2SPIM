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
	void UpdateCollision(Grid* grid, float dt); 
	bool SphereCollison(Draw &objA, Draw &objB, float DeltaTime);
	bool AABBCollision(Draw &objA, Draw &objB, float DeltaTime);
	bool InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime);
	void UpdateQTCollision(QuadTree& tree, std::vector<Draw>& ballObjects, Draw& singleObject, float dt);
	void QTCheckCollision(QuadTree& tree, std::vector<Draw>& ballObjects, Draw& singleObject, float dt);
	
private:
	void CollisionCalculations(Draw& objA, Draw& objB, float DeltaTime);
	void BallCollisionResponse(Draw& objA, Draw& objB);
	void CheckCollision(Draw* ball, std::vector<Draw*>& BallToCheck, int startingIndex, float dt);
	
};

