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
	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	// generate VAO and VBO buffers
	GL_CHECK(glGenVertexArrays(1, &_VAO));
	GL_CHECK(glGenBuffers(1, &_VBO));
	// bind VAO then any binds will bind to this one
	GL_CHECK(glBindVertexArray(_VAO));
	// copy vertices array in buffer in order to be used
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _VBO));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
	// set vertex attribute pointers and enable it
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0));
	GL_CHECK(glEnableVertexAttribArray(0));

	// unbind VBO and VAO
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GL_CHECK(glBindVertexArray(0));

	_shader = std::make_unique<Shader>("resources/shader.vert", "resources/shader.frag");

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
	// VAO just one and already bound, so for things being a bit more organized
	glBindVertexArray(_VAO);

	float randomGreen = (glm::sin(glfwGetTime()) / 2.f) + 0.3f;
	_shader->SetUniformVec4("someColor", glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f });
	glDrawArrays(GL_TRIANGLES, 0, 3);
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

	// optional deallocations
	GL_CHECK(glDeleteVertexArrays(1, &_VAO));
	GL_CHECK(glDeleteBuffers(1, &_VBO));
	_shader->Unbind();
}
