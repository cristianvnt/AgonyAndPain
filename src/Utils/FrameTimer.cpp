#include "FrameTimer.h"

#include "GLFW/glfw3.h"

FrameTimer::FrameTimer()
	: _deltaTime{ 0.f },
	_lastFrameTime{ std::chrono::high_resolution_clock::now() },
	_fpsCounter{ 0 },
	_lastFPSTime{ std::chrono::high_resolution_clock::now() },
	_currentFPS{ 0.f }
{
}

void FrameTimer::Update()
{
	auto now = std::chrono::high_resolution_clock::now();
	_deltaTime = std::chrono::duration<float>(now - _lastFrameTime).count();
	_lastFrameTime = now;
}

double FrameTimer::GetDeltaTime() const
{
	return _deltaTime;
}

void FrameTimer::UpdateFPS()
{
	auto now = std::chrono::high_resolution_clock::now();
	float elapsed = std::chrono::duration<float>(now - _lastFPSTime).count();

	_fpsCounter++;
	if (elapsed >= 0.2f)
	{
		_currentFPS = _fpsCounter / elapsed;
		_fpsCounter = 0;
		_lastFPSTime = now;
	}
}

int FrameTimer::GetFPS() const
{
	return static_cast<int>(_currentFPS);
}
