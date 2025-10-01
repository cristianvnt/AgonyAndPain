#ifndef RENDERER_H
#define RENDERER_H

#include <chrono>
#include "Window.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
private:
	double _deltaTime;
	double _lastFrameTime;
	double _startFrameTime;

	int _fpsCounter;
	double _lastFPSTime;
	double _currentFPS;

	int _targetFPS;
	double _targetFrameTime;

public:
	Renderer(int targetFps = 60);

	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;

	void BeginFrame(Window& window);
	void EndFrame(Window& window);
	double DeltaTime() const;

	void FPS(Window& window);
	void DisplayFPS(Window& window) const;
};

#endif
