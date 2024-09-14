#pragma once
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
	void BallCollisionResponse(Draw& objA, Draw& objB);
};

