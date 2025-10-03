#ifndef RENDERER_H
#define RENDERER_H

#include "Utils/FrameTimer.h"
#include "Settings/RendererSettings.h"
#include "System/Window.h"

#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Shaders/Shader.h"

class Renderer
{
private:
	FrameTimer _frameTimer;
	RendererSettings _rendererSettings;

	// frame cap
	double _targetFrameTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime;

public:
	Renderer(const std::string_view& configPath);

	void Initialize();
	void BeginFrame(Window& window);
	void Clear(float r, float g, float b, float a) const;
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void EndFrame(Window& window);

	void CapFPS();
	const FrameTimer& GetFrameTimer() const { return _frameTimer; }
	const RendererSettings& GetSettings() const { return _rendererSettings; }

	double DeltaTime() const { return _frameTimer.GetDeltaTime(); }
	int GetFPS() const { return _frameTimer.GetFPS(); }
};

#endif
