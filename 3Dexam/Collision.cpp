#include "Collision.h"
#include "Draw.h"
#include "glm/mat4x3.hpp"
#include <glm/glm.hpp>
#include "iostream"
#include <glm/gtc/type_ptr.hpp>
#include "Grid.h"
#include "QuadTree.h"


Collision::Collision()
{

}

Collision::~Collision()
{
	// not needed right now
}

void Collision::UpdateCollision(Grid* grid, float dt)
{
	for (int i = 0; i < grid->m_cells.size(); ++i)
	{
		int x = i % grid->m_numXCells;
		int y = i / grid->m_numXCells; 

		Cell& cell = grid->m_cells[i];

		for (int j = 0; j < cell.balls.size(); ++j)
		{
			Draw* ball = cell.balls[j];
			CheckCollision(ball, cell.balls, j + 1, dt); 
			if (x > 0)
			{
				CheckCollision(ball, grid->getCell(x - 1, y)->balls, 0, dt);
				if (y > 0)
				{
					CheckCollision(ball, grid->getCell(x-1,y-1)->balls, 0, dt); 
				}
				if (y < grid->m_numYCells - 1)
				{
					CheckCollision(ball, grid->getCell(x - 1, y + 1)->balls, 0, dt);
				}
			}
			if (y > 0)
			{
				CheckCollision(ball, grid->getCell(x, y - 1)->balls, 0, dt);
			}
		}
	}
}

bool Collision::SphereCollison(Draw& objA, Draw& objB, float DeltaTime)
{
	//float VelocityScale = 0.05f;
	glm::vec3 posA = objA.GetPosition() + objA.GetVelocity() * DeltaTime;
	glm::vec3 posB = objB.GetPosition() + objB.GetVelocity() * DeltaTime;
	float distance_centers = glm::length(posA - posB);

	if (distance_centers <= (objA.GetSize().x + objB.GetSize().x)) {
		float minimuntranslation = objA.GetSize().x + objB.GetSize().x - distance_centers;
		auto dirvec = glm::normalize(objA.GetPosition() - objB.GetPosition());
		objA.SetPosition(objA.GetPosition() + dirvec * minimuntranslation);
		BallCollisionResponse(objA, objB);

		return true;


	}

	// No collision detected
	return false;
}

bool Collision::AABBCollision(Draw &objA, Draw &objB, float DeltaTime)
{
	if (abs(objA.GetPosition().x - objB.GetPosition().x) > (objA.GetSize().x + objB.GetSize().x))
	{
		return false;
	}
	if (abs(objA.GetPosition().y - objB.GetPosition().y) > (objA.GetSize().y + objB.GetSize().y))
	{
		return false;
	}
	if (abs(objA.GetPosition().z - objB.GetPosition().z) > (objA.GetSize().z + objB.GetSize().z))
	{
		return false;
	}
	std::cout << "collition" << std::endl;
	CollisionCalculations(objA, objB, DeltaTime);

	//AngularCollision(objB, objA);
	return true;
}

bool Collision::InvAABBCollision(Draw& objA, Draw& objB, float DeltaTime)
{
	glm::vec3 MainVelB = objB.GetVelocity();
	float speedBx = MainVelB.x;
	float speedBz = MainVelB.z;

	if (abs((objB.GetPosition().x + MainVelB.x * DeltaTime) - objA.GetPosition().x) > (objA.GetSize().x - objB.GetSize().x))
	{
		// Update velocities only along the X axis
		objB.SetVelocity(glm::vec3(speedBx*-1, 0, speedBz)); // X velocity changes, Z remains same
	}
	if (abs((objB.GetPosition().z + MainVelB.z * DeltaTime) - objA.GetPosition().z) > (objA.GetSize().z - objB.GetSize().z))
	{
		// Update velocities only along the Z axis
		objB.SetVelocity(glm::vec3(speedBx, 0, speedBz * -1)); // Z velocity changes, X remains same
	}
	objB.SetAngularVelocity(objB.GetVelocity());

	return false;
}

void Collision::UpdateQTCollision(QuadTree& tree, std::vector<Draw>& ballObjects, Draw& singleObject, float dt)
{
	tree.ClearTree();

	// Insert all objects into the QuadTree
	for (Draw& obj : ballObjects) {
		tree.Insert(&obj);
	}

	// Insert the single object into the QuadTree
	tree.Insert(&singleObject);

	// Now check for collisions using the QuadTree
	QTCheckCollision(tree, ballObjects, singleObject, dt);

}


void Collision::CollisionCalculations(Draw &objA, Draw &objB, float DeltaTime)
{
	//    1/2mv0^2 = 1/2mv^2

   // mB = 0.5, mA = 0.6
	float massA = objA.GetMass();
	float massB = objB.GetMass();
	float speedAx = objA.GetVelocity().x;
	float speedAz = objA.GetVelocity().z;
	float speedBx = objB.GetVelocity().x;
	float speedBz = objB.GetVelocity().z;

	// Calculate relative velocity in both directions
	float relativeSpeedX = abs(speedAx - speedBx);
	float relativeSpeedZ = abs(speedAz - speedBz);

	glm::vec3 normalA = objA.GetNormal();
	glm::vec3 normalB = objB.GetNormal();
	
	glm::vec3 angularVelocityChangeA(0.0f);
	glm::vec3 angularVelocityChangeB(0.0f);
	// Determine primary axis of collision
	if (normalA.b != 0)
	{
		// Primary collision is along the X axis
		float newSpeedAx = ((massA - massB) * speedAx + 2 * massB * speedBx) / (massA + massB);
		float newSpeedBx = ((massB - massA) * speedBx + 2 * massA * speedAx) / (massA + massB);

		// Update velocities only along the X axis
		objA.SetVelocity(glm::vec3(newSpeedAx, 0, speedAz)); // X velocity changes, Z remains same
		objB.SetVelocity(glm::vec3(newSpeedBx, 0, speedBz)); // X velocity changes, Z remains same

		angularVelocityChangeA.x = (speedAx - speedBx) / massA;
		angularVelocityChangeB.x = (speedBx - speedAx) / massB;
	}
	else
	{
		// Primary collision is along the Z axis
		float newSpeedAz = ((massA - massB) * speedAz + 2 * massB * speedBz) / (massA + massB);
		float newSpeedBz = ((massB - massA) * speedBz + 2 * massA * speedAz) / (massA + massB);

		// Update velocities only along the Z axis
		objA.SetVelocity(glm::vec3(speedAx, 0, newSpeedAz)); // Z velocity changes, X remains same
		objB.SetVelocity(glm::vec3(speedBx, 0, newSpeedBz)); // Z velocity changes, X remains same
		angularVelocityChangeA.z = (speedAz - speedBz) / massA;  // Use speed difference with sign
		angularVelocityChangeB.z = (speedBz - speedAz) / massB;
	}
	objA.SetAngularVelocity(objA.GetAngularVelocity() + angularVelocityChangeA * 0.01f);
	objB.SetAngularVelocity(objB.GetAngularVelocity() + angularVelocityChangeB * 0.01f);
}


void Collision::BallCollisionResponse(Draw& objA, Draw& objB) 
{
	
	float massA = objA.GetMass();
	float massB = objB.GetMass();
	glm::vec3 posA = objA.GetPosition();
	glm::vec3 posB = objB.GetPosition();
	glm::vec3 velocityA = objA.GetVelocity();
	glm::vec3 velocityB = objB.GetVelocity();

	// Calculate the normal vector of the collision
	glm::vec3 normal = glm::normalize(posB - posA);

	// Calculate the relative velocity
	glm::vec3 relativeVelocity = velocityA - velocityB;

	// Calculate the velocity component along the normal
	float velocityAlongNormal = glm::dot(relativeVelocity, normal);


	// Calculate the new velocities along the normal direction
	float restitution = 1.0f; // Coefficient of restitution (1 = perfectly elastic collision)
	float impulse = (-(1 + restitution) * velocityAlongNormal) / (1 / massA + 1 / massB);

	glm::vec3 impulseVector = impulse * normal;

	// Update velocities along the normal
	glm::vec3 newVelocityA = velocityA + (impulseVector / massA);
	glm::vec3 newVelocityB = velocityB - (impulseVector / massB);

	// Set the new velocities
	objA.SetVelocity(newVelocityA);
	objB.SetVelocity(newVelocityB);

	// Calculate and set angular velocity (optional, if needed)
	objA.SetAngularVelocity(glm::cross(impulseVector, normal));
	objB.SetAngularVelocity(glm::cross(-impulseVector, normal));
}

void Collision::CheckCollision(Draw* ball, std::vector<Draw*>& BallToCheck, int startingIndex, float dt)
{
	for (int i = startingIndex; i < BallToCheck.size(); ++i)
	{
		SphereCollison(*ball, *BallToCheck[i], dt);
	}
}

void Collision::QTCheckCollision(QuadTree& tree, std::vector<Draw>& ballObjects, Draw& singleObject, float dt)
{
	std::vector<Draw*> possibleCollisions;

	// Iterate through all objects in the scene (balls)
	for (Draw& objA : ballObjects) {
		// Retrieve potential collision candidates for objA
		possibleCollisions.clear();
		tree.Retrieve(possibleCollisions, &objA);

		// Compare objA with all potential collisions
		for (Draw* objB : possibleCollisions) {
			if (&objA != objB) {
				// Perform sphere-based collision detection
				if (SphereCollison(objA, *objB, dt)) {
					//std::cout << "Collision detected between objects!" << std::endl;

					//add collision response
				}
			}
		}
	}

	// Handle the single object (e.g., Cube0) collisions with others
	possibleCollisions.clear();
	tree.Retrieve(possibleCollisions, &singleObject);

	// Compare the single object with all potential collisions
	for (Draw* objB : possibleCollisions) {
		if (&singleObject != objB) {
			// Perform sphere-based collision detection
			if (SphereCollison(singleObject, *objB, dt)) {
				//std::cout << "Collision detected between single object and others!" << std::endl;

				//add collision response
			}
		}
	}
}

void Collision::calculateBarycentricCoordinates(Draw& ball, Draw& drawObject)
{
	float u, v, w;
	glm::vec3 point = ball.GetPosition();

	// how close the object should be before it starts being affecting the ground
	float groundThreshold = ball.GetSize().y;  
	

	for (int i = 0; i < drawObject.GetVertices().size() -2; ++i) // increment by 3 for triangle vertices
	{
		glm::vec3 v0 = glm::vec3((drawObject.GetVertices()[i].x * drawObject.GetSize().x) + drawObject.GetPosition().x,
			(drawObject.GetVertices()[i].y * drawObject.GetSize().y) + drawObject.GetPosition().y,
			(drawObject.GetVertices()[i].z * drawObject.GetSize().z) + drawObject.GetPosition().z);

		glm::vec3 v1 = glm::vec3((drawObject.GetVertices()[i + 1].x * drawObject.GetSize().x) + drawObject.GetPosition().x,
			(drawObject.GetVertices()[i + 1].y * drawObject.GetSize().y) + drawObject.GetPosition().y,
			(drawObject.GetVertices()[i + 1].z * drawObject.GetSize().z) + drawObject.GetPosition().z);

		glm::vec3 v2 = glm::vec3((drawObject.GetVertices()[i + 2].x * drawObject.GetSize().x) + drawObject.GetPosition().x,
			(drawObject.GetVertices()[i + 2].y * drawObject.GetSize().y) + drawObject.GetPosition().y,
			(drawObject.GetVertices()[i + 2].z * drawObject.GetSize().z) + drawObject.GetPosition().z);

		glm::vec3 v0v1 = v1 - v0;
		glm::vec3 v0v2 = v2 - v0;
		glm::vec3 v0p = point - v0;

		// Compute dot products
		float dot00 = glm::dot(v0v1, v0v1); // v0v1^2
		float dot01 = glm::dot(v0v1, v0v2);
		float dot02 = glm::dot(v0v1, v0p);
		float dot11 = glm::dot(v0v2, v0v2); // v0v2^2
		float dot12 = glm::dot(v0v2, v0p);

		// Compute barycentric coordinates
		float invDenom = 1 / (dot00 * dot11 - dot01 * dot01); // inverse denominator
		v = (dot11 * dot02 - dot01 * dot12) * invDenom;
		w = (dot00 * dot12 - dot01 * dot02) * invDenom;
		u = 1 - w - v;
		float height = v0.y * u + v1.y * v + v2.y * w; // interpolate height using barycentric coordinates
		// Only if the point is inside the triangle (u, v, w > 0)
		if (u >= 0 && v >= 0 && w >= 0) {

			// Check if the ball is sufficiently close to the ground
			if (ball.GetPosition().y < height + groundThreshold) {

				// The ball is at or below the ground, so correct its position
				glm::vec3 newpos = glm::vec3(ball.GetPosition().x, height + groundThreshold, ball.GetPosition().z);
				ball.SetPosition(newpos);
				
				glm::vec3 nextPosition = ball.GetPosition() + ball.GetVelocity();
				glm::vec3 directionalVector = nextPosition - ball.GetPosition();
				auto magnitude = glm::length(directionalVector);

				auto y_AxisAngle = acos(directionalVector.y / magnitude);
				auto slopeDirection = atan2(directionalVector.z, directionalVector.x);
				ball.CalculateGravity(y_AxisAngle, slopeDirection);

				ball.ApplyForce(glm::vec3(0, (ball.GetGravity() * -1), 0));

			}
			
		}
		if (!ball.GetPosition().y < height + groundThreshold)
		ball.SetGravity(-3.81);
	}
}

