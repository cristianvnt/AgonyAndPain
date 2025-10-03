#ifndef RENDERER_SETTINGS_H
#define RENDERER_SETTINGS_H

#include "Utils/ConfigParser.h"

struct RendererSettings
{
	int targetFPS;
	bool vSync;

	static RendererSettings FromConfig(const std::string_view& configPath)
	{
		ConfigParser parse(configPath);
		
		return RendererSettings
		{
			.targetFPS = parse.GetValue<int>("GAME", "TARGET_FPS", 60),
			.vSync = parse.GetValue<bool>("GAME", "VSYNC", false)
		};
	}
};

#endif