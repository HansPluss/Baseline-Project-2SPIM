#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{
}

bool Collision::SphereCollison()
{
//	float distance_centers = glm::length(position - otherCube.position);
//		
//	if (distance_centers <= (sphere_radius + otherCube.sphere_radius)) {
//
//		float minimuntranslation = sphere_radius +otherCube.sphere_radius - distance_centers;
//		auto dirvec = glm::normalize(position - otherCube.position);
//		position += dirvec * minimuntranslation;
//		//otherCube.position += dirvec * minimuntranslation;
//
//		otherCube.move = false;
//		return true; 
//
//	}
//	else {
//;
//		otherCube.move = true;
//	}
//
//
//	// No collision detected
//	return false;
	return false;
}

bool Collision::AABBCollision()
{
	return false;
}
