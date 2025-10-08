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

	float _rotationY;

public:
	Player(Body* body);
	~Player();

	void ProcessInput(const Window* window, const Camera* camera);
	void Update(float deltaTime);
	void Render(Renderer& renderer, const glm::mat4& view, const glm::mat4& proj);
	
	void Rotate(float yaw);

	const glm::vec3 GetPosition() { return _movement->GetPosition(); }
	void SetPosition(const glm::vec3& pos) { _movement->SetPosition(pos); }
	const glm::vec3 GetVelocity() const { return _movement->GetVelocity(); }
	void SetVelocity(const glm::vec3& velocity) { _movement->SetVelocity(velocity); }
	float GetRotationY() const { return _rotationY; }
};

#endif
