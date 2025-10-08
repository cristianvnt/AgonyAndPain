#ifndef CAMERA_SETTINGS_H
#define CAMERA_SETTINGS_H

#include "Engine/Utils/ConfigParser.h"

struct CameraSettings
{
	glm::vec3 position;
	glm::vec3 up;
	float fov;
	float yaw;
	float pitch;
	float speed;
	float sensitivity;

	glm::vec3 thirdPersonOffset;

	static CameraSettings FromParser(ConfigParser& parser)
	{
		return CameraSettings
		{
			.position = glm::vec3(0.f, 0.f, 5.f),
			.up = glm::vec3(0.f, 1.f, 0.f),
			.fov = parser.GetValue<float>("CAMERA", "FOV", 60.f),
			.yaw = parser.GetValue<float>("CAMERA", "YAW", -90.f),
			.pitch = parser.GetValue<float>("CAMERA", "PITCH", 0.f),
			.speed = parser.GetValue<float>("CAMERA", "SPEED", 2.5f),
			.sensitivity = parser.GetValue<float>("CAMERA", "SENSITIVITY", 0.05f),
			.thirdPersonOffset = glm::vec3{ 0.f, 2.f, 5.f }
		};
	}
};

#endif