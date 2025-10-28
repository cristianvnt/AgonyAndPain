#ifndef SETTINGS_H
#define SETTINGS_H

#include "glm/glm.hpp"

namespace SETTINGS
{
	namespace GAME
	{
		constexpr const char* TITLE = "Agony and Pain";
		constexpr int SCREEN_WIDTH = 1920;
		constexpr int SCREEN_HEIGHT = 1080;
		constexpr float GRAVITY = 5.f;
	}

	namespace TERRAIN
	{
		constexpr glm::vec3 POSITION = glm::vec3{ 0.f, -5.f, 0.f };
		constexpr float ANGLE = -90.f;
		constexpr float SCALE = 50.f;
	}

	namespace RENDERER
	{
		constexpr int TARGET_FPS = 60;
		constexpr int VSYNC = 0;
	}
}

#endif