#include "Collision.h"
#include "Draw.h"
#include <glm/glm.hpp>
#include "glm/mat4x3.hpp"
#include "iostream"
#include <glm/gtc/type_ptr.hpp>



Collision::Collision()
{

}

Collision::~Collision()
{
	// not needed right now
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
