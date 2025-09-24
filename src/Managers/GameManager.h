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
};

class GameManagerSettings
{
private:
	int _width{};
	int _height{};
	int _fps{};

public:
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
	int GetFPS() const { return _fps; }

	GameManagerSettings& SetWidth(int width);
	GameManagerSettings& SetHeight(int height);
	GameManagerSettings& SetFPS(int fps);
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