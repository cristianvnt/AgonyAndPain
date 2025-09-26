#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "ConfigManager.h"

class Settings
{
public:
	static constexpr const char* SECTION_GAME = "GAME";
	static constexpr const char* WIDTH = "SCREEN_WIDTH";
	static constexpr const char* HEIGHT = "SCREEN_HEIGHT";
	static constexpr const char* FPS = "FPS";
	static constexpr const char* WINDOW_MODE = "WINDOW_MODE";
};

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

class GameManagerSettings
{
private:
	int _width{};
	int _height{};
	int _fps{};
	WindowModes::Type _windowMode{};

public:
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
	int GetFPS() const { return _fps; }
	WindowModes::Type GetWindowMode() const { return _windowMode; }

	GameManagerSettings& SetWidth(int width);
	GameManagerSettings& SetHeight(int height);
	GameManagerSettings& SetFPS(int fps);
	GameManagerSettings& SetWindowMode(WindowModes::Type mode);
};

class GameManager
{
private:
	ConfigManager _configManager;
	GameManagerSettings _gameSettings;

	void LoadGameSettings();
public:
	GameManager(const std::string& filePath);
	~GameManager() = default;

	const GameManagerSettings& GetSettings() const { return _gameSettings; }
};

#endif