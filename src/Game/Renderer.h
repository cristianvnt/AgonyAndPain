#ifndef RENDERER_H
#define RENDERER_H

#include "Utils/FrameTimer.h"
#include "Window.h"

#include "Components/Buffers/VertexArray.h"
#include "Components/Buffers/IndexBuffer.h"
#include "Components/Shaders/Shader.h"

namespace RendererSettings
{
	constexpr int TARGET_FPS = 60;
	constexpr int VSYNC = 0;
}

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
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void EndFrame();

	void CapFPS();
	const FrameTimer& GetFrameTimer() const { return _frameTimer; }
	double DeltaTime() const { return _frameTimer.GetDeltaTime(); }
	int GetFPS() const { return _frameTimer.GetFPS(); }
};

#endif
