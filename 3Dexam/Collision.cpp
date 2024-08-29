#include "Collision.h"


Collision::Collision() : position(0.0f,0.0f,0.0f), sphere_radius(1.0f), size(1.0f)
{

}

Collision::~Collision()
{
	// not needed right now
}

bool Collision::SphereCollison(Collision otherObject)
{
	float distance_centers = glm::length(position - otherObject.position);
		
	if (distance_centers <= (sphere_radius + otherObject.sphere_radius)) {

		float minimuntranslation = sphere_radius + otherObject.sphere_radius - distance_centers;
		auto dirvec = glm::normalize(position - otherObject.position);
		position += dirvec * minimuntranslation;
		//otherCube.position += dirvec * minimuntranslation;

		//otherObject.move = false;
		return true; 

	}
	else {
;
		//otherCube.move = true;
	}


	// No collision detected
	return false;
}

bool Collision::AABBCollision(Collision otherObject)
{
	bool collisionX = position.x + size >= otherObject.position.x &&
		otherObject.position.x + otherObject.size >= position.x;
	bool collisionY = position.y + size >= otherObject.position.y &&
		otherObject.position.y + otherObject.size >= position.y;
	bool collisionZ = position.z + size >= otherObject.position.z &&
		otherObject.position.z + otherObject.size >= position.z;
	return collisionX && collisionY && collisionZ;
}
