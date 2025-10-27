#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "glm/glm.hpp"

class Movement
{
private:
	glm::vec3 _position{};
	glm::vec3 _velocity{};

public:
	Movement(const glm::vec3& pos = glm::vec3{0.f}, const glm::vec3& velocity = glm::vec3{0.f})
		: _position{ pos }, _velocity{ velocity } { }

	void Update(float deltaTime) { _position += _velocity * deltaTime; }
	
	const glm::vec3& GetPosition() const { return _position; }
	const glm::vec3& GetVelocity() const { return _velocity; }

	Movement& SetPosition(const glm::vec3& pos) { _position = pos; return *this; }
	Movement& SetVelocity(const glm::vec3& velocity) { _velocity = velocity; return *this; }
};

#endif MOVEMENT_H