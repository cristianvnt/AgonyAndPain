#ifndef PLAYER_H
#define PLAYER_H

#include "Components/Body.h"
#include "Components/Movement.h"
#include "Components/RenderData.h"
#include "Game/Window.h"

struct InputState
{
	bool moveForward = false;
	bool moveBackward = false;
	bool moveLeft = false;
	bool moveRight = false;

	void ResetStates()
	{
		moveForward = false;
		moveBackward = false;
		moveLeft = false;
		moveRight = false;
	}
};

class Player
{
private:
	Body* _body{};
	Movement* _movement{};
	RenderData _renderData{};
	float _speed{};
	bool _isCollision{};

	glm::vec3 _front{};
	glm::vec3 _up{};
	glm::vec3 _right{};
	glm::vec3 _worldUp{};

	float _yaw{};
	float _pitch{};

public:
	Player(Body* body, Movement* movement);
	~Player();

	void ProcessInput(InputState& input);
	void Update(double deltaTime);
	RenderData& GetRenderData();
	
	void Rotate(float yawOffset, float pitchOffset);
	void AddGravity(float g);

	Body* GetBody() { return _body; }
	Movement* GetMovement() { return _movement; }
	const glm::vec3& GetFront() const { return _front; }
	const glm::vec3& GetUp() const { return _up; }

	const glm::vec3& GetPosition() const { return _movement->GetPosition(); }
	const glm::vec3& GetVelocity() const { return _movement->GetVelocity(); }
	glm::vec3& GetPosition() { return _movement->GetPosition(); }
	glm::vec3& GetVelocity() { return _movement->GetVelocity(); }

	Player& SetSpeed(float speed) { _speed = speed; return *this; }

	void SetCollision(bool isCollision = false);
	bool IsCollision() const { return _isCollision; }

private:
	void UpdateRenderData();
	void UpdateVectors();
};

#endif
