#include "Camera.h"

Camera::Camera()
{
	_position = glm::vec3{ 0.f, 0.f, 5.f };
	_front = glm::vec3{ 0.f, 0.f, -1.f };
	_up = glm::vec3{ 0.f, 1.f, 0.f };
	_thirdPersonOffset = glm::vec3{ 0.f, 0.f, 5.f };
	_fov = FOV;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::GetProjMatrix(float aspectRatio) const
{
	return glm::perspective(glm::radians(_fov), aspectRatio, 0.1f, 100.f);
}

void Camera::Zoom(float offset)
{
	_fov -= offset;
	_fov = glm::clamp(_fov, 1.f, 60.f);
}

void Camera::FollowTarget(const glm::vec3& targetPos, const glm::vec3& targetFront, const glm::vec3& targetUp)
{
	glm::vec3 forward = glm::normalize(targetFront);
	glm::vec3 right = glm::normalize(glm::cross(forward, targetUp));
	glm::vec3 up = glm::cross(right, forward);

	glm::mat3 rotation(right, up, -forward);
	glm::vec3 rotatedOffset = rotation * _thirdPersonOffset;

	_position = targetPos + rotatedOffset;
	_front = glm::normalize(targetPos - _position);
	_up = up;
}
