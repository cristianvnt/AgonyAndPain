#ifndef PLAYER_H
#define PLAYER_H

#include "Engine/Rendering/Renderer.h"
#include "Engine/Components/Body.h"
#include "Engine/Components/Movement.h"

class Player
{
private:
	Body* _body;
	Movement* _movement;

public:
	Player(Body* body);
	~Player();

	void Update(float deltaTime);
	void Render(Renderer& renderer, const glm::mat4& view, const glm::mat4& proj);

	void SetPosition(const glm::vec3& pos) { _movement->SetPosition(pos); }
	const glm::vec3 GetPosition() const { return _movement->GetPosition(); }
};

#endif
