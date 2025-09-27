#ifndef GAME_H
#define GAME_H

#include "Managers/GameManager.h"
#include "Renderer.h"
#include "Shader.h"

#include <string>

class Game
{
private:
	GameManager _gameManager;
	Renderer _renderer;
	Window _window;
	bool _isRunning;

	// temporary
	unsigned int _VAO;
	unsigned int _VBO;
	std::unique_ptr<Shader> _shader;

	void Initialize();
	void ProcessInput();
	void Update(double deltaTime);
	void Render();

public:
	Game(const std::string& filePath);
	void Run();
};

#endif
