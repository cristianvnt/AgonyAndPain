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
	
	void SetVelocity(const glm::vec3& velocity);
	void SetPosition(const glm::vec3& pos) { _position = pos; }
	const glm::vec3 GetPosition() const { return _position; }
};

#endif MOVEMENT_H