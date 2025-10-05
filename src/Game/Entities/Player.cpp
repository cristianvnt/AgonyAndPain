#include "Player.h"
#include <glm/ext/matrix_transform.hpp>

Player::Player(Body* body)
	: _body{ body }, _movement{ new Movement{ glm::vec3{0.f} } }
{
}

Player::~Player()
{
	delete _body;
}

void Player::Update(float deltaTime)
{
	_movement->Update(deltaTime);
}

void Player::Render(Renderer& renderer, const glm::mat4& view, const glm::mat4& proj)
{
	_body->GetShader()->Bind();
	_body->GetTexture()->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));

	_body->GetShader()->SetUniformVec4("someColor", glm::vec4{1.f, 0.5f, 0.f, 1.f});
	_body->GetShader()->SetUniformMat4f("u_Model", model);
	_body->GetShader()->SetUniformMat4f("u_View", view);
	_body->GetShader()->SetUniformMat4f("u_Proj", proj);

	renderer.Draw(*_body->GetVAO(), *_body->GetIBO(), *_body->GetShader());
}
