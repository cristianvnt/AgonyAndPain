#ifndef RENDERER_H
#define RENDERER_H

#include "Utils/FrameTimer.h"
#include "Window.h"

#include "Components/Buffers/VertexArray.h"
#include "Components/Buffers/IndexBuffer.h"
#include "Components/Shaders/Shader.h"
#include "Components/RenderData.h"

class Renderer
{
private:
	FrameTimer _frameTimer{};

	// frame cap
	double _targetFrameTime{};
	std::chrono::time_point<std::chrono::high_resolution_clock> _lastFrameTime{};

public:
	Renderer();

	void Initialize();
	void BeginFrame();
	void Clear(const glm::vec4& color) const;

	// drawing
	void DrawObject(const RenderData& data, const glm::mat4& view, const glm::mat4& proj) const;

	void EndFrame();

	void CapFPS();
	const FrameTimer& GetFrameTimer() const { return _frameTimer; }
	double DeltaTime() const { return _frameTimer.GetDeltaTime(); }
	int GetFPS() const { return _frameTimer.GetFPS(); }
};

#endif
