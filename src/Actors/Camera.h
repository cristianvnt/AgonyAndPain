#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float FOV = 60.f;
constexpr float SENSITIVITY = 0.05f;

class Camera
{
private:
	glm::vec3 _position{};
	glm::vec3 _front{};
	glm::vec3 _up{};
	glm::vec3 _thirdPersonOffset{};
	float _fov{};

public:
	Camera();

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix(float aspectRatio) const;

	void Zoom(float offset);

	void FollowTarget(const glm::vec3& targetPos, const glm::vec3& targetFront, const glm::vec3& targetUp);

	const glm::vec3& GetPosition() const { return _position; }
	const glm::vec3& GetFront() const { return _front; }
	const glm::vec3& GetUp() const { return _up; }
	void SetPosition(const glm::vec3& pos) { _position = pos; }
};

#endif
