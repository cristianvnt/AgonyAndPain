#include "Movement.h"

Movement::Movement(const glm::vec3& startPos)
	: _position{ startPos }, _velocity{ 0.f }
{
}

void Movement::Update(float deltaTime)
{
	_position += _velocity * deltaTime;
}

void Movement::SetVelocity(const glm::vec3& velocity)
{
	_velocity = velocity;
}