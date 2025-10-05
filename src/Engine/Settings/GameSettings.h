#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include "Engine/Utils/ConfigParser.h"
#include "WindowSettings.h"
#include "RendererSettings.h"
#include "CameraSettings.h"

struct GameSettings
{
	WindowSettings window;
	RendererSettings renderer;
	CameraSettings camera;

	static GameSettings FromConfig(const std::string_view& configPath)
	{
		ConfigParser parser(configPath);

		return GameSettings
		{
			.window = WindowSettings::FromParser(parser),
			.renderer = RendererSettings::FromParser(parser),
			.camera = CameraSettings::FromParser(parser)
		};
	}
};

#endif