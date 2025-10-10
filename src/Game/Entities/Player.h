#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Rendering/Renderer.h"
#include "Engine/Components/Body.h"
#include "Engine/Components/Movement.h"
#include "Engine/Rendering/Camera.h"

class Player
{
private:
	Body* _body;
	Movement* _movement;

	float _speed;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;

public:
	Player(Body* body);
	~Player();

	void ProcessInput(const Window* window);
	void Update(double deltaTime);
	void Render(Renderer& renderer, const glm::mat4& view, const glm::mat4& proj);
	
	void Rotate(float yawOffset, float pitchOffset);

	const glm::vec3 GetPosition() { return _movement->GetPosition(); }
	void SetPosition(const glm::vec3& pos) { _movement->SetPosition(pos); }
	const glm::vec3 GetVelocity() const { return _movement->GetVelocity(); }
	void SetVelocity(const glm::vec3& velocity) { _movement->SetVelocity(velocity); }
	void SetSpeed(float speed);
	const glm::vec3& GetFront() const { return _front; }
	const glm::vec3& GetUp() const { return _up; }

private:
	void UpdateVectors();
};

#endif
