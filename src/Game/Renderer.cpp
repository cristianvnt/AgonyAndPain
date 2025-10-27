#include "Renderer.h"
#include "Window.h"

#include <thread>

using namespace RendererSettings;

Renderer::Renderer()
{
	_targetFrameTime = 1.0 / TARGET_FPS;
	_lastFrameTime = std::chrono::high_resolution_clock::now();
}

void Renderer::Initialize()
{
	GL_CHECK(glfwSwapInterval(VSYNC));
	GL_CHECK(glEnable(GL_DEPTH_TEST));

	GL_CHECK(glEnable(GL_BLEND));
	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::BeginFrame()
{
	Clear({ 0.2f, 0.3f, 0.3f, 1.0f });
}

void Renderer::Clear(const glm::vec4& color) const
{
	GL_CHECK(glClearColor(color.r, color.g, color.b, color.a));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	ibo.Bind();
	GL_CHECK(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::EndFrame()
{
	CapFPS();
	_frameTimer.Update();
	_frameTimer.UpdateFPS();
}

void Renderer::CapFPS()
{
	while (true)
	{
		auto now = std::chrono::high_resolution_clock::now();
		double elapsed = std::chrono::duration<double>(now - _lastFrameTime).count();
		double remainingTime = _targetFrameTime - elapsed;

		if (remainingTime <= 0.001)
			break;

		std::this_thread::sleep_for(std::chrono::duration<double>(0.001));
	}

	_lastFrameTime = std::chrono::high_resolution_clock::now();
}
