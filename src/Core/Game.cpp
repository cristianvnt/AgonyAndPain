#include "Game.h"

#include <GLFW/glfw3.h>
#include <iostream>

Game::Game(const std::string& filePath)
	: _gameManager(filePath),
	_window{ _gameManager.GetSettings().GetWidth(),
			_gameManager.GetSettings().GetHeight(),
			"AGONY and PAIN",
			_gameManager.GetSettings().GetWindowMode() },
	_renderer(_gameManager.GetSettings().GetTargetFPS()),
	_isRunning(false)
{
	Initialize();
}

void Game::Initialize()
{
	const auto& settings = _gameManager.GetSettings();

	std::cout << "Initializing game...\n";
	std::cout << "Resolution: " << settings.GetWidth() << "x" << settings.GetHeight() << "\n";
	std::cout << "Target FPS: " << settings.GetTargetFPS() << "\n";
	std::cout << "Window Mode: " << WindowModes::ToString(settings.GetWindowMode()) << "\n";

	if (!_window.Initialize())
	{
		std::cout << "NOOOOO ERROR: Failed to init window\n";
		return;
	}
	
	// temporary init
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	GL_CHECK(glGenVertexArrays(1, &_VAO));
	GL_CHECK(glBindVertexArray(_VAO));

	_buffer = std::make_unique<VertexBuffer>(vertices, 4 * 3 * sizeof(float));

	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0));

	_EBO = std::make_unique<IndexBuffer>(indices, 2 * 3);

	_shader = std::make_unique<Shader>("resources/shader.vert", "resources/shader.frag");

	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	_isRunning = true;
	std::cout << "YIPPEEEEEEEE\n";
}

void Game::ProcessInput()
{
	_window.PollEvents();

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_isRunning = false;
}

void Game::Update(double deltaTime)
{

}

void Game::Render()
{
	_shader->Bind();
	GL_CHECK(glBindVertexArray(_VAO));
	_EBO->Bind();
	float randomGreen = (glm::sin(static_cast<float>(glfwGetTime())) / 2.f) + 0.3f;
	_shader->SetUniformVec4("someColor", glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f });
	GL_CHECK(glDrawElements(GL_TRIANGLES, _EBO->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Game::Run()
{
	while (_isRunning && !_window.ShouldClose())
	{
		ProcessInput();
		Update(_renderer.DeltaTime());

		_renderer.BeginFrame(_window);
		Render();
		_renderer.EndFrame(_window);
	}
}
