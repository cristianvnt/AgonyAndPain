#include "Camera.h"

Camera::Camera(const CameraSettings& settings)
	: _cameraSettings{ settings },
	_position{ settings.position }, _fov{ settings.fov },
	_thirdPersonOffset{ settings.thirdPersonOffset },
	_up{ settings.up }, _front{ glm::vec3{0.f, 0.f, -1.f} }
{
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

void Camera::FollowTarget(const glm::vec3& playerPos, const glm::vec3& playerFront, const glm::vec3& playerUp)
{
	glm::vec3 forward = glm::normalize(playerFront);
	glm::vec3 right = glm::normalize(glm::cross(forward, playerUp));
	glm::vec3 up = glm::cross(right, forward);

	glm::mat3 rotation(right, up, -forward);
	glm::vec3 rotatedOffset = rotation * _thirdPersonOffset;

	_position = playerPos + rotatedOffset;
	_front = glm::normalize(playerPos - _position);
	_up = up;
}
