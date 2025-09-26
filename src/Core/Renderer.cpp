#include "Renderer.h"
#include "Window.h"

#include <thread>
#include <iostream>

Renderer::Renderer(int targetFps /*= 60*/)
	: _deltaTime(0.0), _lastFrameTime(0.0),
	_fpsCounter(0), _lastFPSTime(0.0), _currentFPS(0.0),
	_targetFPS(targetFps), _targetFrameTime(1.0 / _targetFPS)
{

}

void Renderer::BeginFrame(Window& window)
{
	FPS(window);
	window.Clear(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::EndFrame(Window& window)
{
	double currentTime = glfwGetTime();
	double frameDuration = currentTime - _lastFrameTime;

	// frame limit
	if (frameDuration < _targetFrameTime)
	{
		std::this_thread::sleep_for(std::chrono::duration<double>(_targetFrameTime - frameDuration));
		currentTime = glfwGetTime();
		frameDuration = currentTime - _lastFrameTime;
	}

	_deltaTime = frameDuration;
	_lastFrameTime = currentTime;

	window.SwapBuffers();
}

double Renderer::DeltaTime() const
{
	return _deltaTime;
}

void Renderer::FPS(Window& window)
{
	double currentTime = glfwGetTime();
	double elapsed = currentTime - _lastFPSTime;

	_fpsCounter++;
	if (elapsed >= 0.1)
	{
		_currentFPS = _fpsCounter / elapsed;
		_fpsCounter = 0;
		_lastFPSTime = currentTime;
		std::cout << _currentFPS << '\n';
		DisplayFPS(window);
	}
}

void Renderer::DisplayFPS(Window& window) const
{
	std::string title = "AGONY and PAIN - FPS: " + std::to_string(static_cast<int>(_currentFPS));
	glfwSetWindowTitle(window.GetGLFWwindow(), title.c_str());
}

