#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Settings/CameraSettings.h"

class Camera
{
private:
	CameraSettings _cameraSettings;

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;
	float _fov;
public:
	Camera(const CameraSettings& settings);

	const CameraSettings& GetSettings() const { return _cameraSettings; }

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix(float aspectRatio) const;

	void Move(const glm::vec3& movement);
	void Rotate(const glm::vec2& rotation);
	void Zoom(float offset);

private:
	void UpdateVectors();
};

#endif
