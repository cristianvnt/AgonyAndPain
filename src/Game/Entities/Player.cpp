#include "Player.h"
#include <glm/ext/matrix_transform.hpp>

Player::Player(Body* body)
	: _body{ body }, _movement{ new Movement{ glm::vec3{0.f} } },
	_up{ glm::vec3{0.f, 1.f, 0.f} },
	_worldUp{ _up }, _front{ glm::vec3{0.f, 0.f, -1.f} }, _right{ glm::vec3{1.f, 0.f, 0.f} },
	_yaw{ -90.f }, _pitch{ 0.f },
	_speed{ 1.f }
{
	UpdateVectors();
}

Player::~Player()
{
	delete _movement;
	delete _body;
}

void Player::ProcessInput(const Window* window)
{
	glm::vec3 velocity{};
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
		velocity += _front;
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
		velocity -= _front;
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
		velocity -= _right;
	if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
		velocity += _right;

	if (velocity != glm::vec3{ 0.f })
		velocity = glm::normalize(velocity) * _speed;
	SetVelocity(velocity);
}

void Player::Update(double deltaTime)
{
	_movement->Update(deltaTime);
}

void Player::Render(Renderer& renderer, const glm::mat4& view, const glm::mat4& proj)
{
	_body->GetShader()->Bind();
	_body->GetTexture()->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), GetPosition());
	model = glm::rotate(model, glm::radians(-_yaw), glm::vec3{ 0.f, 1.f, 0.f });
	model = glm::rotate(model, glm::radians(_pitch), glm::vec3{ 0.f, 0.f, 1.f });

	_body->GetShader()->SetUniformVec4("someColor", glm::vec4{1.f, 0.5f, 0.f, 1.f});
	_body->GetShader()->SetUniformMat4f("u_Model", model);
	_body->GetShader()->SetUniformMat4f("u_View", view);
	_body->GetShader()->SetUniformMat4f("u_Proj", proj);

	renderer.Draw(*_body->GetVAO(), *_body->GetIBO(), *_body->GetShader());
}

void Player::Rotate(float yawOffset, float pitchOffset)
{
	_yaw += yawOffset;
	_pitch += pitchOffset;
	_pitch = glm::clamp(_pitch, -89.f, 89.f);

	UpdateVectors();
}

void Player::SetSpeed(float speed)
{
	_speed = speed;
}

void Player::UpdateVectors()
{
	glm::vec3 front{};
	front.x = glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	front.y = glm::sin(glm::radians(_pitch));
	front.z = glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));

	_front = glm::normalize(front);
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
}