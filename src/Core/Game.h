#ifndef GAME_H
#define GAME_H

#include <string>

#include "Managers/GameManager.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Game
{
private:
	GameManager _gameManager;
	Renderer _renderer;
	Window _window;
	bool _isRunning;

	// temporary
	unsigned int _VAO;
	std::unique_ptr<VertexBuffer> _buffer;
	std::unique_ptr<IndexBuffer> _EBO;
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
