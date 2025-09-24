#include "Game.h"

#include <GLFW/glfw3.h>
#include <iostream>

Game::Game(const std::string& filePath)
	: _gameManager(filePath),
	_window(_gameManager.GetSettings().GetWidth(),
			_gameManager.GetSettings().GetHeight(),
			"AGONY and PAIN"),
	_renderer(_gameManager.GetSettings().GetFPS()),
	_isRunning(false)
{
	Initialize();
}

void Game::Initialize()
{
	const auto& settings = _gameManager.GetSettings();

	std::cout << "Initializing game...\n";
	std::cout << "Resolution: " << settings.GetWidth() << "x" << settings.GetHeight() << "\n";
	std::cout << "Target FPS: " << settings.GetFPS() << "\n";

	if (!_window.Initialize())
	{
		std::cout << "NOOOOO ERROR: Failed to init window\n";
		return;
	}

	_isRunning = true;
	std::cout << "YIPPEEEEEEEE\n";
}

void Game::ProcessInput()
{
	_window.PollEvents();

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_isRunning = false;
}

void Game::Update(double deltaTime)
{

}

void Game::Render()
{

}

void Game::Run()
{
	while (_isRunning && !_window.ShouldClose())
	{
		double deltaTime = _renderer.DeltaTime();

		ProcessInput();
		Update(deltaTime);

		_renderer.BeginFrame(_window);
		Render();
		_renderer.EndFrame(_window);
	}
}
