#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine/Settings/CameraSettings.h"

class Camera
{
private:
	CameraSettings _cameraSettings;

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	float _fov;

	glm::vec3 _thirdPersonOffset;
public:
	Camera(const CameraSettings& settings);

	const CameraSettings& GetSettings() const { return _cameraSettings; }

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix(float aspectRatio) const;

	void Zoom(float offset);

	void FollowTarget(const glm::vec3& playerPos, const glm::vec3& playerFront, const glm::vec3& playerUp);

	const glm::vec3& GetPosition() const { return _position; }
	void SetPosition(const glm::vec3& pos) { _position = pos; }
	const glm::vec3& GetFront() const { return _front; }
	const glm::vec3& GetUp() const { return _up; }
};

#endif
