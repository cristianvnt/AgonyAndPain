#include "Renderer.h"
#include "Window.h"

#include <thread>
#include <iostream>

Renderer::Renderer(int targetFps /*= 60*/)
	: _deltaTime(0.0), _lastFrameTime(0.0),
	_fpsCounter(0), _lastFPSTime(0.0), _currentFPS(0.0),
	_targetFPS(targetFps), _targetFrameTime(1.0 / _targetFPS),
	_startFrameTime(0.0)
{

}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	GL_CHECK(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::BeginFrame(Window& window)
{
	FPS(window);
	window.Clear(0.2f, 0.3f, 0.3f, 1.0f);

	_startFrameTime = glfwGetTime();
}

void Renderer::EndFrame(Window& window)
{
	window.SwapBuffers();

	while (true)
	{
		double elapsed = glfwGetTime() - _startFrameTime;
		double remainingTime = _targetFrameTime - elapsed;

		if (remainingTime <= 0.001)
			break;

		std::this_thread::sleep_for(std::chrono::duration<double>(0.001));
	}

	double now = glfwGetTime();
	_deltaTime = now - _lastFrameTime;
	_lastFrameTime = now;
}

double Renderer::DeltaTime() const
{
	return _deltaTime;
}

void Renderer::FPS(Window& window)
{
	double now = glfwGetTime();
	double elapsed = now - _lastFPSTime;

	_fpsCounter++;
	if (elapsed >= 0.1)
	{
		_currentFPS = _fpsCounter / elapsed;
		_fpsCounter = 0;
		_lastFPSTime = now;
		DisplayFPS(window);
	}
}

void Renderer::DisplayFPS(Window& window) const
{
	std::string title = "AGONY and PAIN - FPS: " + std::to_string(static_cast<int>(_currentFPS));
	glfwSetWindowTitle(window.GetGLFWwindow(), title.c_str());
}

