#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

#include "Utils/ConfigParser.h"

namespace WindowModes
{
	enum class Type
	{
		WINDOWED,
		FULLSCREEN,
		BORDERLESS
	};

	constexpr const char* ToString(const Type mode)
	{
		switch (mode)
		{
		case Type::WINDOWED:
			return "windowed";
			break;
		case Type::FULLSCREEN:
			return "fullscreen";
			break;
		case Type::BORDERLESS:
			return "borderless";
			break;
		default:
			return "windowed";
			break;
		}
	}

	inline Type FromString(const std::string& str) {
		if (str == "fullscreen")
			return Type::FULLSCREEN;
		if (str == "borderless")
			return Type::BORDERLESS;
		return Type::WINDOWED;
	}
}

struct WindowSettings
{
	std::string title;
	int width;
	int height;
	WindowModes::Type windowMode;

	static WindowSettings FromParser(ConfigParser& parser)
	{
		return WindowSettings
		{
			.title = parser.GetValue<std::string>("GAME", "TITLE", "Agony and Pain"),
			.width = parser.GetValue<int>("GAME", "SCREEN_WIDTH", 800),
			.height = parser.GetValue<int>("GAME", "SCREEN_HEIGHT", 600),
			.windowMode = WindowModes::FromString(
				parser.GetValue<std::string>("GAME", "WINDOW_MODE", "windowed")
			)
		};
	}
};

#endif