#ifndef RENDERER_H
#define RENDERER_H

#include <chrono>
#include "Window.h"

class Renderer
{
private:
	int _targetFPS;
	int _frameCounter;
	double _currentFPS;
	std::chrono::high_resolution_clock::time_point _lastFrameTime;
	std::chrono::high_resolution_clock::time_point _lastFPSTime;

public:
	Renderer(int targetFps = 60);

	void BeginFrame(Window& window);
	void EndFrame(Window& window);
	double DeltaTime();
	void SetTargetFps(int fps) { _targetFPS = fps; }
	int GetTargetFps() const { return _targetFPS; }
	double GetCurrentFPS() const { return _currentFPS; }

	void FPS(Window& window);
	void DisplayFPS(Window& window) const;
};

#endif
