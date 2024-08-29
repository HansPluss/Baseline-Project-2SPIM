#include "Rigidbody.h"

Rigidbody::Rigidbody() : Mass(1.0f), Position(0.0f,0.0f,0.0f), Velocity(0.0f,0.0f,0.0f), Acceleration(1.0f,1.0f,1.0f)
{

}

Rigidbody::~Rigidbody()
{
}

glm::vec3 Rigidbody::GetPosition()
{
	return glm::vec3();
}


glm::vec3 Rigidbody::GetVelocity()
{
	return Velocity;
}

glm::vec3 Rigidbody::GetAcceleration()
{
	return Acceleration;
}

float Rigidbody::GetMass()
{
	return Mass;
}

float Rigidbody::GetFriction()
{
	return Friction;
}

void Rigidbody::SetPosition(const glm::vec3& position)
{
	Position = position;
}

void Rigidbody::SetVelocity(const glm::vec3& velocity)
{
	Velocity = velocity;
}

void Rigidbody::SetAcceleration(const glm::vec3& acceleration)
{
	Acceleration = acceleration;
}

void Rigidbody::SetMass(float mass)
{
	Mass = mass;
}

void Rigidbody::SetFriction(float friction)
{
	Friction = friction;
}

void Rigidbody::ApplyForce(glm::vec3 force)
{
	// F = M*A
	Acceleration += force / Mass;
}

void Rigidbody::Update(float deltaTime)
{
	Velocity += Acceleration * deltaTime;
	Position += Velocity * deltaTime;
}

void Rigidbody::ElasticCollision(Rigidbody rb1, Rigidbody rb2, const glm::vec3& collisionNormal)
{
	glm::vec3 relativeVelocity = rb1.GetVelocity() - rb2.GetVelocity();
	float relativeVelocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);

	float elasticity = 1.0f;
	float impusleMagnitude = -(1 + elasticity) * relativeVelocityAlongNormal / (1 / rb1.GetMass() + 1 / rb2.GetMass());

	glm::vec3 impulse = impusleMagnitude * collisionNormal;
	rb1.SetVelocity(rb1.GetVelocity() + impulse / rb1.GetMass());
	rb2.SetVelocity(rb2.GetVelocity() - impulse / rb2.GetMass());
}
