#ifndef GAME_H
#define GAME_H

#include <string>

#include "Managers/GameManager.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class Game
{
private:
	GameManager _gameManager;
	Renderer _renderer;
	Window _window;
	bool _isRunning;

	// temporary
	std::unique_ptr<VertexArray> _vao;
	std::unique_ptr<VertexBuffer> _vbo;
	std::unique_ptr<IndexBuffer> _ibo;
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
