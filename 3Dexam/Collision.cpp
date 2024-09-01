#include "Collision.h"
#include "Draw.h"


Collision::Collision()
{

}

Collision::~Collision()
{
	// not needed right now
}

bool Collision::SphereCollison(Draw objA, Draw objB)
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

bool Collision::AABBCollision(Draw objA, Draw objB)
{
	if (abs(objA.GetPosition().x - objB.GetPosition().x) > (objA.GetSize().x + objB.GetPosition().x)) return false;
	if (abs(objA.GetPosition().y - objB.GetPosition().y) > (objA.GetSize().y + objB.GetPosition().y)) return false;
	if (abs(objA.GetPosition().z - objB.GetPosition().z) > (objA.GetSize().z + objB.GetPosition().z)) return false;
	return true;
}
