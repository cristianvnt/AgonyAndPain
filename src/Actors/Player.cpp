#include "Player.h"
#include "glm/ext/matrix_transform.hpp"

#include "Utils/Settings.h"

#include <iostream>

using namespace SETTINGS;

Player::Player(Body* body, Movement* movement)
	: _body{ body }, _movement{ movement }, _speed{ 1.f }, _isCollision{ false }
{
	_up = glm::vec3{ 0.f, 1.f, 0.f };
	_worldUp = _up;
	_front = glm::vec3{ 0.f, 0.f, -1.f };
	_right = glm::vec3{ 1.f, 0.f, 0.f };
	_yaw = -90.f;
	_pitch = 0.f;

	UpdateVectors();
}

Player::~Player()
{
	delete _movement;
	delete _body;
}

void Player::ProcessInput(InputState& input)
{
	glm::vec3 velocity{0.f};
	_movement->SetVelocity(velocity);

	glm::vec3 front = _front;
	glm::vec3 right = _right;

	if (_isCollision && (_front.y < 0.f && input.moveForward || _front.y > 0 && input.moveBackward))
	{
		std::cout << "COLLISIOOOOOOON\n";
		front.y = 0.f;
	}

	if (input.moveForward)
		velocity += front;
	if (input.moveBackward)
		velocity -= front;
	if (input.moveLeft)
		velocity -= right;
	if (input.moveRight)
		velocity += right;

	if (velocity == glm::vec3{ 0.f })
		return;

	std::cout << "x:" << _movement->GetPosition().x << " y:" << _movement->GetPosition().y << " z:" << _movement->GetPosition().z << "\n";
	_movement->SetVelocity(glm::normalize(velocity) * _speed);
}

void Player::Update(double deltaTime)
{
	if (!_isCollision)
		AddGravity(GAME::GRAVITY);

	_movement->Update(static_cast<float>(deltaTime));
	UpdateRenderData();
}

RenderData& Player::GetRenderData()
{
	return _renderData;
}

void Player::Rotate(float yawOffset, float pitchOffset)
{
	_yaw += yawOffset;
	_pitch += pitchOffset;
	_pitch = glm::clamp(_pitch, -89.f, 89.f);

	UpdateVectors();
}

void Player::AddGravity(float g)
{
	_movement->GetVelocity().y += (-1 * g);
	std::cout << "Gravity Added\n";
}

void Player::SetCollision(bool isCollision /*= false*/)
{
	_isCollision = isCollision;
}

void Player::UpdateRenderData()
{
	glm::mat4 m = glm::translate(glm::mat4(1.0f), _movement->GetPosition());
	m = glm::rotate(m, glm::radians(-_yaw), glm::vec3{ 0.f, 1.f, 0.f });
	m = glm::rotate(m, glm::radians(_pitch), glm::vec3{ 0.f, 0.f, 1.f });

	_renderData.model = m;
	_renderData.vao = _body->GetVAO();
	_renderData.ibo = _body->GetIBO();
	_renderData.shader = _body->GetShader();
	_renderData.texture = _body->GetTexture();
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