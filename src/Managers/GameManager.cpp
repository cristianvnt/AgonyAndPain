#include "GameManager.h"

GameManager::GameManager(const std::string& filePath)
	: _configManager(filePath), _gameSettings{}
{
	if (filePath.empty())
		std::cout << "NOOOOO ERROR: Filepath cannot be empty.\n";
	LoadGameSettings();
}

void GameManager::LoadGameSettings()
{
	_gameSettings.SetWidth(_configManager.GetValue<int>(Settings::SECTION_GAME, Settings::WIDTH, 800))
		.SetHeight(_configManager.GetValue<int>(Settings::SECTION_GAME, Settings::HEIGHT, 600))
		.SetTargetFPS(_configManager.GetValue<int>(Settings::SECTION_GAME, Settings::TARGET_FPS, 60))
		.SetWindowMode(WindowModes::FromString(_configManager.GetValue<std::string>(Settings::SECTION_GAME, Settings::WINDOW_MODE, "windowed")));
}

GameManagerSettings& GameManagerSettings::SetWidth(int width)
{
	_width = width;
	return *this;
}

GameManagerSettings& GameManagerSettings::SetHeight(int height)
{
	_height = height;
	return *this;
}

GameManagerSettings& GameManagerSettings::SetTargetFPS(int targetFPS)
{
	_targetFps = targetFPS;
	return *this;
}

GameManagerSettings& GameManagerSettings::SetWindowMode(WindowModes::Type mode)
{
	_windowMode = mode;
	return *this;
}
