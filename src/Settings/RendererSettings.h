#ifndef RENDERER_SETTINGS_H
#define RENDERER_SETTINGS_H

#include "Utils/ConfigParser.h"

struct RendererSettings
{
	int targetFPS;
	int vSync;

	static RendererSettings FromParser(ConfigParser& parser)
	{
		return RendererSettings
		{
			.targetFPS = parser.GetValue<int>("GAME", "TARGET_FPS", 60),
			.vSync = parser.GetValue<int>("GAME", "VSYNC", 0)
		};
	}
};

#endif