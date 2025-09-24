#include "Renderer.h"
#include "Window.h"

Renderer::Renderer(int targetFps)
	: _targetFPS{ targetFps }, _frameCounter{ 0 }, _currentFPS{ 0.0 },
	_lastFrameTime{ std::chrono::high_resolution_clock::now() },
	_lastFPSTime{ std::chrono::high_resolution_clock::now()}
{

}

void Renderer::BeginFrame(Window& window)
{
	FPS(window);
	window.Clear(0.2f, 0.3f, 0.3f, 1.0f);
}

void Renderer::EndFrame(Window& window)
{
	window.SwapBuffers();
}

double Renderer::DeltaTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	double deltaTime = std::chrono::duration<double>(currentTime - _lastFrameTime).count();
	_lastFrameTime = currentTime;
	return deltaTime;
}

void Renderer::FPS(Window& window)
{
	_frameCounter++;
	auto currentTime = std::chrono::high_resolution_clock::now();
	double elapsed = std::chrono::duration<double>(currentTime - _lastFPSTime).count();

	if (elapsed >= 0.1)
	{
		_currentFPS = _frameCounter / elapsed;
		_frameCounter = 0;
		_lastFPSTime = currentTime;

		DisplayFPS(window);
	}
}

void Renderer::DisplayFPS(Window& window) const
{
	std::string title = "AGONYandPAIN - FPS: " + std::to_string((int)_currentFPS);
	glfwSetWindowTitle(window.GetGLFWwindow(), title.c_str());
}

