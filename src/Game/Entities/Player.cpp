#include "Player.h"
#include <glm/ext/matrix_transform.hpp>

Player::Player(Body* body)
	: _body{ body }, _movement{ new Movement{ glm::vec3{0.f} } },
	_rotationY{ 0.f }
{
}

Player::~Player()
{
	delete _movement;
	delete _body;
}

void Player::ProcessInput(const Window* window, const Camera* camera)
{
	glm::vec3 cameraForward = camera->GetFront();
	cameraForward.y = 0;
	cameraForward = glm::normalize(cameraForward);
	glm::vec3 cameraRight = camera->GetRight();
	cameraRight.y = 0;
	cameraRight = glm::normalize(cameraRight);

	glm::vec3 velocity{};
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
		velocity += cameraForward * 1.f;
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
		velocity -= cameraForward * 1.f;
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
		velocity -= cameraRight * 1.f;
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
		velocity += cameraRight * 1.f;
	if (velocity != glm::vec3{ 0.f })
		velocity = glm::normalize(velocity);

	SetVelocity(velocity);
}

void Player::Update(float deltaTime)
{
	_movement->Update(deltaTime);
}

void Player::Render(Renderer& renderer, const glm::mat4& view, const glm::mat4& proj)
{
	_body->GetShader()->Bind();
	_body->GetTexture()->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), GetPosition());
	model = glm::rotate(model, glm::radians(_rotationY), glm::vec3{ 0.f, 1.f, 0.f });

	_body->GetShader()->SetUniformVec4("someColor", glm::vec4{1.f, 0.5f, 0.f, 1.f});
	_body->GetShader()->SetUniformMat4f("u_Model", model);
	_body->GetShader()->SetUniformMat4f("u_View", view);
	_body->GetShader()->SetUniformMat4f("u_Proj", proj);

	renderer.Draw(*_body->GetVAO(), *_body->GetIBO(), *_body->GetShader());
}

void Player::Rotate(float yaw)
{
	_rotationY += yaw;
}
