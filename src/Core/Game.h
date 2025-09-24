#ifndef GAME_H
#define GAME_H

#include "Managers/GameManager.h"
#include "Renderer.h"

#include <string>

class Game
{
private:
	GameManager _gameManager;
	Renderer _renderer;
	Window _window;
	bool _isRunning;

	void Initialize();
	void ProcessInput();
	void Update(double deltaTime);
	void Render();

public:
	Game(const std::string& filePath);
	void Run();
};

#endif
