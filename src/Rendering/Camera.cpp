#include "Camera.h"

Camera::Camera(const CameraSettings& settings)
	: _cameraSettings{ settings },
	_position{ settings.position }, _worldUp{ settings.up },
	_yaw{ settings.yaw }, _pitch{ settings.pitch }, _fov{ settings.fov }
{
	UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::GetProjMatrix(float aspectRatio) const
{
	return glm::perspective(glm::radians(_fov), aspectRatio, 0.1f, 100.f);
}

void Camera::Move(const glm::vec3& movement)
{
	std::cout << "Moving - Front: (" << _front.x << ", " << _front.y << ", " << _front.z << ")\n";
	std::cout << "Movement input: (" << movement.x << ", " << movement.y << ", " << movement.z << ")\n";

	_position += _right * movement.x;
	_position += _up * movement.y;
	_position += _front * movement.z;

	std::cout << "New position: (" << _position.x << ", " << _position.y << ", " << _position.z << ")\n";
}

void Camera::Rotate(const glm::vec2& rotation)
{
	_yaw += rotation.x;
	_pitch += rotation.y;

	if (_pitch > 89.f)
		_pitch = 89.f;
	if (_pitch < -89.f)
		_pitch = -89.f;

	UpdateVectors();
}

void Camera::Zoom(float offset)
{
	_fov -= offset;
	if (_fov < 1.0)
		_fov = 1.0;
	if (_fov > 60.f)
		_fov = 60.f;
}

void Camera::UpdateVectors()
{
	glm::vec3 front{};
	front.x = glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	front.y = glm::sin(glm::radians(_pitch));
	front.z = glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	
	_front = glm::normalize(front);
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
	
}
