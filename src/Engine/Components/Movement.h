#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "glm/glm.hpp"

class Movement
{
private:
	glm::vec3 _position;
	glm::vec3 _velocity;

public:
	Movement(const glm::vec3& startPos);

	void Update(float deltaTime);
	
	const glm::vec3& GetVelocity() const { return _velocity; }
	void SetVelocity(const glm::vec3& velocity) { _velocity = velocity; }
	const glm::vec3& GetPosition() const { return _position; }
	void SetPosition(const glm::vec3& pos) { _position = pos; }
};

#endif MOVEMENT_H