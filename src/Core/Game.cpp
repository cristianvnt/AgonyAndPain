#include "Game.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "VertexBufferLayout.h"
#include "Utils/Utils.h"

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
		// pos		   // tex
		100.f, 100.f, 0.f, 0.f, // 0
		270.f, 100.f, 1.f, 0.f, // 1
		270.f, 270.f, 1.f, 1.f, // 2
		100.f, 270.f, 0.f, 1.f  // 3
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GL_CHECK(glEnable(GL_BLEND));
	GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	_vao = std::make_unique<VertexArray>();
	_vbo = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	_vao->AddBuffer(*_vbo, layout);

	_ibo = std::make_unique<IndexBuffer>(indices, 2 * 3);

	glm::mat4 proj = glm::ortho(0.f, (float)_window.GetWidth(), 0.f, (float)_window.GetHeight(), -1.f, 1.f);

	_shader = std::make_unique<Shader>(Path::Shader::VERTEX, Path::Shader::FRAGMENT);
	_shader->Bind();

	_texture = std::make_unique<Texture>(Path::Texture::TEXTURE);
	_texture2 = std::make_unique<Texture>(Path::Texture::TEXTURE1);
	_texture->Bind();
	//_texture2->Bind(1);

	_shader->SetUniform1i("u_Texture", 0);
	_shader->SetUniform1i("u_Texture2", 1);
	_shader->SetUniformMat4f("u_Proj", proj);

	_vao->Unbind();
	_vbo->Unbind();
	_ibo->Unbind();
	_shader->Unbind();

	_isRunning = true;
	std::cout << "YIPPEEEEEEEE\n";
}

void Game::ProcessInput()
{
	_window.PollEvents();

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_isRunning = false;

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_X) == GLFW_PRESS)
		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	if (glfwGetKey(_window.GetGLFWwindow(), GLFW_KEY_Z) == GLFW_PRESS)
		GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
}

void Game::Update(double deltaTime)
{

}

void Game::Render()
{
	_shader->Bind();
	float randomGreen = (glm::sin(static_cast<float>(glfwGetTime()))) + 0.1f;
	_shader->SetUniformVec4("someColor", glm::vec4{ 0.8f, 0.5f, randomGreen, 1.f });
	_renderer.Draw(*_vao, *_ibo, *_shader);
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
