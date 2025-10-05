#ifndef RENDERER_H
#define RENDERER_H

#include "Engine/Utils/FrameTimer.h"
#include "Engine/Settings/RendererSettings.h"
#include "Engine/System/Window.h"

#include "Engine/Rendering/Buffers/VertexArray.h"
#include "Engine/Rendering/Buffers/IndexBuffer.h"
#include "Engine/Rendering/Shaders/Shader.h"

class Renderer
{
private:
	FrameTimer _frameTimer;
	RendererSettings _rendererSettings;

	// frame cap
	double _targetFrameTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime;

public:
	Renderer(const RendererSettings& settings);

	void Initialize();
	void BeginFrame(Window* window);
	void Clear(float r, float g, float b, float a) const;
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void EndFrame(Window* window);

	const RendererSettings& GetSettings() const { return _rendererSettings; }

	void CapFPS();
	const FrameTimer& GetFrameTimer() const { return _frameTimer; }
	double DeltaTime() const { return _frameTimer.GetDeltaTime(); }
	int GetFPS() const { return _frameTimer.GetFPS(); }
};

#endif
