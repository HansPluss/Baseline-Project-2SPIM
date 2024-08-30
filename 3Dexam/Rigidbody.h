#pragma once
#include <glm/glm.hpp>
class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();

	glm::vec3 GetPosition();
	glm::vec3 GetVelocity();
	glm::vec3 GetAcceleration();
	glm::vec3 GetAngularVelocity();
	glm::vec3 GetAngularAcceleration();
	float GetMass();
	float GetFriction();

	void SetPosition(const glm::vec3& position);
	void SetVelocity(const glm::vec3& velocity);
	void SetAcceleration(const glm::vec3& acceleration);
	void SetMass(float mass);
	void SetFriction(float friction);
	void ApplyForce(glm::vec3 force);
	void ApplyTorque();
	void Update(float deltaTime);
	void ElasticCollision(Rigidbody rb1, Rigidbody rb2, const glm::vec3& collisionNormal);
private:
	glm::vec3 Position;
	glm::vec3 Velocity;
	glm::vec3 Acceleration;
	glm::vec3 AngularVelocity;
	glm::vec3 AngularAcceleration;
	float Mass;
	float Friction;
};
