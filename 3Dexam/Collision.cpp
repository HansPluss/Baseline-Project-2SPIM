#include "Collision.h"
#include "Draw.h"


Collision::Collision()
{

}

Collision::~Collision()
{
	// not needed right now
}

bool Collision::SphereCollison(Draw &objA, Draw &objB)
{
	float distance_centers = glm::length(objA.GetPosition() - objB.GetPosition());
		
	if (distance_centers <= (objA.GetSize().x + objB.GetSize().x)) {

		std::cout << "collition" << std::endl;
		float minimuntranslation = objA.GetSize().x + objB.GetSize().x - distance_centers;
		auto dirvec = glm::normalize(objA.GetPosition() - objB.GetPosition());

		glm::vec3 newPos; 
	newPos = objA.GetPosition() + dirvec * minimuntranslation;
	objA.SetPosition(newPos);
		
		return true; 


	}
	else {
; std::cout << "collition failed" << std::endl;
		//otherCube.move = true;
	}


	// No collision detected
	return false;
}

bool Collision::AABBCollision(Draw &objA, Draw &objB)
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
	//CollisionCalculations(objA, objB);

	AngularCollision(objB, objA);
	return true;
}


void Collision::CollisionCalculations(Draw &objA, Draw &objB)
{
	//    1/2mv0^2 = 1/2mv^2

	//mB = 0.5,   mA = 0.6
	float massA = objA.GetMass();
	float massB = objB.GetMass();
	float speedA = objA.GetVelocity().x;
	float speedB = objB.GetVelocity().x;

	
	// Calculate new speeds after collision
	float newSpeedA = ((massA - massB) * speedA + 2 * massB * speedB) / (massA + massB);
	float newSpeedB = ((massB - massA) * speedB + 2 * massA * speedA) / (massA + massB);

	

	// Update the velocities
	objA.speed = newSpeedA;
	objB.speed = newSpeedB;
	objA.SetVelocity(glm::vec3(newSpeedA, 0,0));
	objB.SetVelocity(glm::vec3(newSpeedB, 0, 0));
}

void Collision::AngularCollision(Draw& objA, Draw& objB)
{
	// Work in progress by yours truly
	float massA = objA.GetMass();
	float massB = objB.GetMass();
	glm::vec3 velocityA = objA.GetVelocity();
	glm::vec3 velocityB = objB.GetVelocity();

	glm::vec3 positionA = objA.GetPosition();
	glm::vec3 positionB = objB.GetPosition();

	glm::vec3 normalB = objB.GetNormal();
	glm::vec3 normalA = objA.GetNormal();
	glm::vec3 normal = glm::normalize(positionA - positionB);

	glm::vec3 nA = normalB;
	glm::vec3 nB = normalA;

	float dotA = glm::dot(velocityA, nA);
	glm::vec3 scaledNA = (2 * dotA) * nA ;

	float dotB = glm::dot(velocityB, nB);
	glm::vec3 scaledNB = (2 * dotB) * nB;


	glm::vec3 newVelocityA = velocityA - scaledNA;
	glm::vec3 newVelocityB = velocityB - scaledNB;


	
	
	float scalingFactor = 1.0f;  // This can be adjusted to control "bounciness" yeah yeah smh

	glm::vec3 finalVelocityB = newVelocityB * scalingFactor;
	glm::vec3 finalVelocityA = newVelocityA * scalingFactor;


	std::cout << "Old velocity" << velocityA.x << ", " << velocityA.z << std::endl;

	//glm::vec3 normal = objA.GetPosition() - objB.GetPosition();
	std::cout << "New velocity" << newVelocityA.x << ", " << newVelocityA.z << std::endl;

	//objA.SetVelocity(newSpeed);
	//objB.SetVelocity(newVelocity);
	objA.SetVelocity(finalVelocityA);
	objB.SetVelocity(finalVelocityB);

	
}
