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

	static CameraSettings FromParser(ConfigParser& parser)
	{
		return CameraSettings
		{
			.position = glm::vec3(0.0f, 0.0f, 5.0f),
			.up = glm::vec3(0.0f, 1.0f, 0.0f),
			.fov = parser.GetValue<float>("CAMERA", "FOV", 60.f),
			.yaw = parser.GetValue<float>("CAMERA", "YAW", -90.f),
			.pitch = parser.GetValue<float>("CAMERA", "PITCH", 0.f),
			.speed = parser.GetValue<float>("CAMERA", "SPEED", 2.5f),
			.sensitivity = parser.GetValue<float>("CAMERA", "SENSITIVITY", 0.05f)
		};
	}
};

#endif