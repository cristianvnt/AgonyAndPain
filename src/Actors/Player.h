#ifndef PLAYER_H
#define PLAYER_H

#include "Components/Body.h"
#include "Components/Movement.h"
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
	float _speed{};

	glm::vec3 _front{};
	glm::vec3 _up{};
	glm::vec3 _right{};
	glm::vec3 _worldUp{};

	float _yaw{};
	float _pitch{};

	void UpdateVectors();
public:
	Player(Body* body, Movement* movement);
	~Player();

	void ProcessInput(InputState& input);
	void Update(double deltaTime);
	void Render(const glm::mat4& view, const glm::mat4& proj);
	
	void Rotate(float yawOffset, float pitchOffset);

	Body* GetBody() { return _body; }
	Movement* GetMovement() { return _movement; }
	const glm::vec3& GetFront() const { return _front; }
	const glm::vec3& GetUp() const { return _up; }

	Player& SetSpeed(float speed) { _speed = speed; return *this; }
};

#endif
